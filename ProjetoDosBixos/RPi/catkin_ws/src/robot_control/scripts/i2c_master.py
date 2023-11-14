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
        rospy.init_node('i2c_communicator')

        self.i2c = smbus.SMBus(i2c_bus)  # Define o barramento que será usado na comunicação
        self.device_address = device_address  # Define o endereço da ESP32 ao qual queremos nos comunicar

        # Cria um objeto de publicação para enviar dados para o tópico ROS
        self.pub_encoder = rospy.Publisher('/encoder_data', encoder_data, queue_size=10)
        self.sub_joints = rospy.Subscriber('/velocity_command', velocity_data, self.joints_callback)

        encoder_msg = encoder_data()

        encoder_msg.left_encoder_data = 0
        encoder_msg.right_encoder_data = 0

        self.pub_encoder.publish(encoder_msg)

        self.update()

    def read_data(self):
        try:
            data = self.i2c.read_i2c_block_data(self.device_address, REG_ADDRESS, 8)  # Faz a leitura da ESP32
            value_right, value_left = struct.unpack('!ii', bytes(data[:3]), bytes(data[3:]))  # Desempacota as informações recebidas

            print(f'Valor lido: {value_left}, {value_right}')

            self.left_encoder_data = value_left
            self.right_encoder_data = value_right

            self.pub_encoder.publish(encoder_msg)

        except Exception as e:
            print(f"Erro na leitura: {str(e)}")
            return None

    def write_data(self):
        try:
            data = struct.pack('!ii', self.right_wheel_velocity, self.left_wheel_velocity)  # "Empacota" o valor mandado como parâmetro da função
            self.i2c.write_i2c_block_data(self.device_address, REG_ADDRESS, list(data))  # Escreve valor para a ESP32
            
            print(f'Valor enviado: {self.left_wheel_velocity}, {self.right_wheel_velocity}')

        except Exception as e:
            print(f"Erro na escrita: {str(e)}")

    def joints_callback(self, msg):

        joint_msg = velocity_data()
        joint_msg = msg

        if joint_msg is not None and joint_msg.front_left_velocity != 0.0:

            self.left_wheel_velocity = int(joint_msg.front_left_velocity * 100)
            self.right_wheel_velocity = int(joint_msg.front_right_velocity * 100)

        else:
            return None

    def update(self):

        rate = rospy.Rate(10)  # 10Hz

        while not rospy.is_shutdown():
            self.read_data()
            self.write_data()

            rate.sleep()

if __name__ == "__main__":
    try:
        RobotHWInterface()
        rospy.spin()
    except rospy.ROSInterruptException:
        pass
