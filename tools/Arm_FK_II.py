from math import sin, cos, radians

def ang_to_pos (x):
    return (x - 30) / 0.29

def pos_to_ang (x):
    print (x * 0.29) + 30
    return (x * 0.29) + 30

def calc_offset (length, theta):
    return dict (X = length * sin(radians (theta)), Y = -length * cos(radians (theta)))
