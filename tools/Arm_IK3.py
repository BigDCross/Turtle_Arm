from Arm_FK import *
from math import sqrt
import sys

def calc_distance (A, B, C, target):
    # Calculate distance from current position to target
    j1 = Joint (10.5, A)
    j2 = Joint (10.5, B)
    j3 = Joint (14.0, C)
    joints = []
    joints.append (j1)
    joints.append (j2)
    joints.append (j3)

    dist = fk (joints)

    return sqrt ((dist["X"] - target["X"]) ** 2 + (dist["Y"] - target["Y"]) ** 2)

def calc_gradient (A, B, C, target):
    # Inital Pos
    dist = calc_distance (A, B, C, target)

    while dist > 0.1:
        # Calculate slope of gradient for each joint pos
        gradient_a = calc_distance (A + 1, B, C, target) - calc_distance (A - 1, B, C, target)
        gradient_b = calc_distance (A, B + 1, C, target) - calc_distance (A, B - 1, C, target)
        gradient_c = calc_distance (A, B, C + 1, target) - calc_distance (A, B, C - 1, target)

        # Go down slope
        A -= gradient_a
        B -= gradient_b
        C -= gradient_c

        #print str (gradient_a) + " , " + str (gradient_b) + " , " + str (gradient_c)

        # Update distance from target
        dist = calc_distance (A, B, C, target)

    return A, B, C
