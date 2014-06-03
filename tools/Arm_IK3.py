from Arm_FK import *
from math import sqrt
import sys

target = dict (X = int (sys.argv[1]), Y = int (sys.argv[2]))

def calc_distance (A, B, C):
    j1 = Joint (10.5, A)
    j2 = Joint (10.5, B)
    j3 = Joint (10.5, C)
    joints = []
    joints.append (j1)
    joints.append (j2)
    joints.append (j3)

    dist = fk (joints)

    return sqrt ((dist["X"] - target["X"]) ** 2 + (dist["Y"] - target["Y"]) ** 2)

def calc_gradient (A, B, C):
    # Inital Pos
    dist = calc_distance (A, B, C)

    while dist > 0.1:
        gradient_a = calc_distance (A + 1, B, C) - calc_distance (A - 1, B, C)
        gradient_b = calc_distance (A, B + 1, C) - calc_distance (A, B - 1, C)
        gradient_c = calc_distance (A, B, C + 1) - calc_distance (A, B, C - 1)

        A -= gradient_a
        B -= gradient_b
        C -= gradient_c

        #print str (gradient_a) + " , " + str (gradient_b) + " , " + str (gradient_c)
        dist = calc_distance (A, B, C)

    return A, B, C

def main ():
    A, B, C = calc_gradient (512, 512, 512)

    print "Target"
    print "X:" + str (target["X"]) + " Y:" + str (target["Y"])
    print "Servo Positions"
    print A, B, C

main ()
