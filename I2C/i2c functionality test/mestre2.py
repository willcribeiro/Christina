#Programa: Python Raspberry Pi Comunicacao I2C
#Autor: Arduino e Cia
#!/usr/bin/python
import time
import smbus
slaveAddress = 0x18    
i2c = smbus.SMBus(1)
def RequisitaDadosArduino():
    global msg_recebida
    dados_recebidos_Arduino = i2c.read_i2c_block_data(slaveAddress, 0,11)
    for i in range(len(dados_recebidos_Arduino)):
        msg_recebida += chr(dados_recebidos_Arduino[i])

    print(msg_recebida)
    dados_recebidos_Arduino =""
    msg_recebida = ""
    msg_recebida = ""
    while 1:
        RequisitaDadosArduino() 
        time.sleep(5)