from smbus import SMBus
from time import sleep
import struct

addr = 0x18
bus = SMBus(1)

numb = 1

def get_data():
    return bus.read_i2c_block_data(addr, 0);

def get_float(data, index):
    bytes = data[4*index:(index+1)*4]
    return struct.unpack('f', "".join(map(chr, bytes)))[0]

print("Entre com a movimentacao")
while numb ==1:
    n1 = input(">>>>   ")
    n2 = input(">>>>   ")
    n3 = input(">>>>   ")
    x = [n1,n2,n3]
    bus.write_i2c_block_data(addr,0 ,x)
    sleep(0.2)
    data = get_data()
    print(get_float(data, 0))
    print(get_float(data, 1))
    print(get_float(data, 2))