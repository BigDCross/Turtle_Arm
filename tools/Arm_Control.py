import os
import sys
from time import sleep

import serial
from Arm_IK3 import *
from Arm_FK import *

ser = serial.Serial (port = "/dev/ttyUSB0", baudrate=9600)

target = dict (X = 0, Y = 30)
current_pos = dict (j1 = 512, j2 = 512, j3 = 512)

def send_controls (j1, j2, j3, j4, j5):
    j1 = int (j1)
    j2 = int (j2)
    j3 = int (j3)
    j4 = int (j4)
    j5 = int (j5)

    ser.write ("{a},{b},{c},{d},{e}".format (a=j1,b=j2,c=j3,d=j4,e=j5))
    print "{a},{b},{c},{d},{e}".format (a=j1,b=j2,c=j3,d=j4,e=j5)

def set_target (x, y):
    target["X"] = x
    target["Y"] = y

def main ():
    while True:
        pos_input = None
        pos_input = input ("Enter Desired Position {X,Y}: ")
        print pos_input

        set_target (pos_input[0], pos_input[1])

        A, B, C = calc_gradient (current_pos["j1"], current_pos["j2"], current_pos["j3"], target)

        current_pos["j1"] = A
        current_pos["j2"] = B
        current_pos["j3"] = C

        send_controls (512, A, B, C, 512)

if __name__=="__main__":
    main ()
