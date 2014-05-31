from math import sin, cos, radians

def ang_to_pos (x):
    return (x - 30) / 0.29

def pos_to_ang (x):
    return (x * 0.29) + 30

def calc_offset (length, theta):
    return dict (X = length * sin(radians (theta)), Y = length * cos(radians (theta)))

def main ():
    j1 = calc_offset (10, 512)
    j2 = calc_offset (10, pos_to_ang (224))
    j3 = calc_offset (10, pos_to_ang (419))
    j4 = calc_offset (10, pos_to_ang (456))

    temp = calc_offset (0, 0)
    for i in (j1, j2, j3, j4):
        print i
        temp["X"] += i["X"]
        temp["Y"] += i["Y"]

    print "Final" + str (temp)

main ()
