from math import sin, cos, radians

class Joint:
    def __init__(self, length, pos):
        self.length = length
        self.pos = pos

    def angle (self):
        return pos_to_ang_adj (self.pos)

def pos_to_ang_adj (x):
    # We subtract 180 to adjust the frame of reference
    return ((x * 0.29) + 30) - 180

def pos_to_ang (x):
    return ((x * 0.29) + 30)

def calc_offset (length, theta):
    return dict (X = length * sin(radians (theta)), Y = length * cos(radians (theta)))

def fk (Joints):
    num_servos = len (Joints)

    final_pos = calc_offset (0, 0) 
    cum_angle = 0
    for i in Joints:
        cum_angle += i.angle()
        offset = calc_offset (i.length, cum_angle)
        final_pos["X"] += offset["X"]
        final_pos["Y"] += offset["Y"]

    return final_pos

def main ():
    j1 = Joint (10.5, 424)
    j2 = Joint (10.5, 695)
    j3 = Joint (10.5, 720)

    joints = []
    joints.append (j1)
    joints.append (j2)
    joints.append (j3)

    final_pos = fk (joints)

    print final_pos
