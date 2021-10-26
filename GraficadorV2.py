import serial
import matplotlib.pyplot as plt
import numpy as np
from datetime import date, datetime

plt.ion()
fig=plt.figure()


x=list()
y=list()
i=0

port= serial.Serial('COM3',9600)
port.close()
port.open()

while True:
    data=port.readline()
    print(data.decode())
    x.append(i)
    y.append(data.decode())

    plt.scatter(i,float(data.decode()))
    plt.show()
    i+=1
    plt.pause(0.0001)


