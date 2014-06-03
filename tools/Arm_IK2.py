from Arm_FK import *
from math import sqrt
import sys

target = dict (X = int (sys.argv[1]), Y = int (sys.argv[2]))

def calc_distance (A, B):
    j1 = Joint (10.5, A)
    j2 = Joint (10.5, B)
    joints = []
    joints.append (j1)
    joints.append (j2)

    dist = fk (joints)

    return sqrt ((dist["X"] - target["X"]) ** 2 + (dist["Y"] - target["Y"]) ** 2)

def calc_gradient (A, B):
    # Inital Pos
    dist = calc_distance (A, B)

    while dist > 0.1:
        gradient_a = calc_distance (A + 1, B) - calc_distance (A - 1, B)
        gradient_b = calc_distance (A, B + 1) - calc_distance (A, B - 1)

        A -= 100 * gradient_a
        B -= 100 * gradient_b

        #print str (gradient_a) + " , " + str (gradient_b)
        dist = calc_distance (A, B)

    return A, B

def main ():
    A, B = calc_gradient (512, 512)

    print "Target"
    print "X:" + str (target["X"]) + " Y:" + str (target["Y"])
    print "Servo Positions"
    print A, B

main ()
