from smbus import SMBus
import struct

addr = 0x18
bus = SMBus(1)

numb = 1

def RequisitaDadosArduino():
    global msg_recebida
    dados_recebidos_Arduino = bus.read_i2c_block_data(addr, 0,11)
    for i in range(len(dados_recebidos_Arduino)):
        msg_recebida += chr(dados_recebidos_Arduino[i])
    print(msg_recebida)
    dados_recebidos_Arduino =""
    msg_recebida = ""
msg_recebida = ""

print("Entre com a movimentacao")
while numb ==1:
    n1 = input(">>>>   ")
    n2 = input(">>>>   ")
    n3 = input(">>>>   ")
    x = [n1,n2,n3]
    bus.write_i2c_block_data(addr,0 ,x)
    RequisitaDadosArduino()
