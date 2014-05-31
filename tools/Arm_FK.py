from math import sin, cos, radians

def ang_to_pos (x):
    return (x - 30) / 0.29

def pos_to_ang_adj (x):
    # We subtract 180 to adjust the frame of reference
    return ((x * 0.29) + 30) - 180

def pos_to_ang (x):
    return ((x * 0.29) + 30)

def calc_offset (length, theta):
    return dict (X = length * sin(radians (theta)), Y = length * cos(radians (theta)))

def main ():
    j1 = calc_offset (10.25, pos_to_ang_adj (376))
    j2 = calc_offset (10.25, pos_to_ang_adj (376) + pos_to_ang_adj (1000))
    j3 = calc_offset (10.25, pos_to_ang_adj (376) + pos_to_ang_adj (1000) + pos_to_ang_adj (430))

    temp = calc_offset (0, 0)
    temp["Y"] = 13.5
    for i in (j1, j2, j3):
        #print i
        temp["X"] += i["X"]
        temp["Y"] += i["Y"]

    print
    print "Final" + str (temp)

main ()
