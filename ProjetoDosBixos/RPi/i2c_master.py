#!/usr/bin/env python3
import rospy
import time
import smbus
import struct
from std_msgs.msg import Int32

# Autores: Matheus Paiva Angarola e William

# Constantes
ESP32_ADDRESS = 0x08 # Endereço do dispositivo ESP32 no barramento I2C
I2C_BUS = 1  # Número do barramento I2C no Raspberry Pi
REG_ADDRESS = 10  # Endereço de registro (offset) a ser usado
WAIT_TIME_SECONDS = 2  # Tempo de espera entre leituras/escritas (em segundos)

# Classe para comunicação I2C
class I2CCommunication:
    # "Construtor" da classe, definindo seus atributos principais
    def __init__(self, i2c_bus, device_address):
        self.i2c = smbus.SMBus(i2c_bus) # Define o barramento que será usado na comunicação
        self.device_address = device_address # Define o enderça da ESP32 ao qual queremos nos comunicar

    def read_data(self):

        try:
            data = self.i2c.read_i2c_block_data(self.device_address, REG_ADDRESS,4) # Faz a leitura da ESP32
           # data.reverse()
            value = struct.unpack('!i', bytes(data)) # Desempacota as informações recebidas

            # '!i' significa que o valor a ser enviado é um int (i) e é "big-endian" (MSB -> esquerda e LSB -> direita) 

            return value # Retorna valor lido da ESP32

        except Exception as e:
            print(f"Erro na leitura: {str(e)}")
            return None

    def write_data(self, value):

        try:
            # "Empacota" o valor mandado com parâmetro da função
            data = struct.pack('!i', value)
           # print(f'Valor enviado: {data}')
            print(f'Valor enviado: {value}')

            # Escreve valor para a ESP32
            self.i2c.write_i2c_block_data(self.device_address, REG_ADDRESS, list(data))

        except Exception as e:
            print(f"Erro na escrita: {str(e)}")

def main():

    i2c_communication = I2CCommunication(I2C_BUS, ESP32_ADDRESS)

    rospy.init_node('i2c_communicator')

    # Cria um objeto de publicação para enviar dados para o tópico ROS
    pub = rospy.Publisher('i2c_data', Int32, queue_size=10)
    
    rate = rospy.Rate(10) # 10Hz

    while not rospy.is_shutdown():
        const_value = i2c_communication.read_data()
	
        if const_value is not None:
            pub.publish(const_value[0])
            i2c_communication.write_data(const_value[0])
            
        rate.sleep()

if __name__ == "__main__":
    try:
    	main()
    except rospy.ROSInterruptException: pass
