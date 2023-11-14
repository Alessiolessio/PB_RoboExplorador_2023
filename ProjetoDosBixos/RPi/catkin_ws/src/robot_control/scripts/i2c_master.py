#!/usr/bin/env python3
import rospy
import smbus
import struct
from std_msgs.msg import Int32
from sensor_msgs.msg import JointState
from robot_control.msg import encoder_data, velocity_data
from time import sleep

# Autores: Matheus Paiva Angarola e William

# Constantes
ESP32_ADDRESS = 0x08  # Endereço do dispositivo ESP32 no barramento I2C
I2C_BUS = 1  # Número do barramento I2C no Raspberry Pi
REG_ADDRESS = 10  # Endereço de registro (offset) a ser usado pelo PID da direita
WAIT_TIME_SECONDS = 2  # Tempo de espera entre leituras/escritas (em segundos)

# Classe para comunicação I2C
class I2CCommunication:
    # "Construtor" da classe, definindo seus atributos principais
    def __init__(self, i2c_bus, device_address):
        self.i2c = smbus.SMBus(i2c_bus)  # Define o barramento que será usado na comunicação
        self.device_address = device_address  # Define o endereço da ESP32 ao qual queremos nos comunicar

    def read_data(self):
        try:
            data = self.i2c.read_i2c_block_data(self.device_address, REG_ADDRESS, 8)  # Faz a leitura da ESP32
            value_right, value_left = struct.unpack('!ii', bytes(data[:3]), bytes(data[3:]))  # Desempacota as informações recebidas

            print(f'Valor lido: {value_left}, {value_right}')

            encoder_msg = encoder_data()
            encoder_msg.left_encoder_data = value_left
            encoder_msg.right_encoder_data = value_right

            return encoder_msg

        except Exception as e:
            print(f"Erro na leitura: {str(e)}")
            return None

    def write_data(self, value_right, value_left):
        try:
            data = struct.pack('!ii', value_right, value_left)  # "Empacota" o valor mandado como parâmetro da função
            self.i2c.write_i2c_block_data(self.device_address, REG_ADDRESS, list(data))  # Escreve valor para a ESP32
            print(f'Valor enviado: {value_left}, {value_right}')

        except Exception as e:
            print(f"Erro na escrita: {str(e)}")

    def joints_callback(self, msg):
        joint_msg = velocity_data()
        joint_msg = msg

        if joint_msg is not None and joint_msg.front_left_velocity != 0.0:
            left_wheel_velocity = int(joint_msg.front_left_velocity * 100)
            right_wheel_velocity = int(joint_msg.front_right_velocity * 100)

            return right_wheel_velocity, left_wheel_velocity
        else:
            return None

def main():
    i2c_communication = I2CCommunication(I2C_BUS, ESP32_ADDRESS)

    rospy.init_node('i2c_communicator')

    # Cria um objeto de publicação para enviar dados para o tópico ROS
    pub_encoder = rospy.Publisher('/encoder_data', encoder_data, queue_size=10)
    sub_joints = rospy.Subscriber('/velocity_command', velocity_data, i2c_communication.joints_callback)

    rate = rospy.Rate(10)  # 10Hz

    while not rospy.is_shutdown():
        encoder_msg = i2c_communication.read_data()
        if encoder_msg is not None:
            pub_encoder.publish(encoder_msg)

        joints_values = i2c_communication.joints_callback(sub_joints)
        if joints_values is not None:
            right_wheel_velocity, left_wheel_velocity = joints_values
            i2c_communication.write_data(right_wheel_velocity, left_wheel_velocity)

        rate.sleep()

if __name__ == "__main__":
    try:
        main()
    except rospy.ROSInterruptException:
        pass
