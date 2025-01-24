import random

def changescen(filename,writefile):
    f = open(filename)

    line = f.readline()
    lines = ['rotation 1\n']
    line = f.readline()
    while (line):
        temp = line.strip().replace("\n","").split("\t")
        #print(temp)
        temp.insert(6,str(1))
        temp.insert(9,str(1))
        lines.append('\t'.join(temp) + '\n')
        #print(temp)
        line = f.readline()

    f.close()

    file = open(writefile,"w")
    for item in lines:
        file.write(item)
    file.close()


#changescen("instances/random_map_temp/random-32-32-20-random-1.scen","instances/random_map/random-32-32-20-random-1.scen")

for i in range(25):
    # r_file = "instances/random_map_temp/random-32-32-20-random-"+str(i+1)+".scen"
    # w_file = "instances/random_map/random-32-32-20-random-"+str(i+1)+".scen"
    r_file = "/home/ubuntu/yue-code/CBS/instance/first_priority/den520d/scen-random/den520d-random-"+str(i+1)+".scen"
    w_file = "/home/ubuntu/yue-code/CBS/instance/first_priority/den520d/scen-random-rotation-fix/den520d-random-"+str(i+1)+".scen"
    changescen(r_file,w_file)

for i in range(25):
    # r_file = "instances/random_map_temp/random-32-32-20-random-"+str(i+1)+".scen"
    # w_file = "instances/random_map/random-32-32-20-random-"+str(i+1)+".scen"
    r_file = "/home/ubuntu/yue-code/CBS/instance/first_priority/empty-32-32/scen-random/empty-32-32-random-"+str(i+1)+".scen"
    w_file = "/home/ubuntu/yue-code/CBS/instance/first_priority/empty-32-32/scen-random-rotation-fix/empty-32-32-random-"+str(i+1)+".scen"
    changescen(r_file,w_file)

for i in range(25):
    # r_file = "instances/random_map_temp/random-32-32-20-random-"+str(i+1)+".scen"
    # w_file = "instances/random_map/random-32-32-20-random-"+str(i+1)+".scen"
    r_file = "/home/ubuntu/yue-code/CBS/instance/first_priority/paris/scen-random/Paris_1_256-random-"+str(i+1)+".scen"
    w_file = "/home/ubuntu/yue-code/CBS/instance/first_priority/paris/scen-random-rotation-fix/Paris_1_256-random-"+str(i+1)+".scen"
    changescen(r_file,w_file)

for i in range(25):
    # r_file = "instances/random_map_temp/random-32-32-20-random-"+str(i+1)+".scen"
    # w_file = "instances/random_map/random-32-32-20-random-"+str(i+1)+".scen"
    r_file = "/home/ubuntu/yue-code/CBS/instance/first_priority/random-32-32-20/scen-random/random-32-32-20-random-"+str(i+1)+".scen"
    w_file = "/home/ubuntu/yue-code/CBS/instance/first_priority/random-32-32-20/scen-random-rotation-fix/random-32-32-20-random-"+str(i+1)+".scen"
    changescen(r_file,w_file)

for i in range(25):
    # r_file = "instances/random_map_temp/random-32-32-20-random-"+str(i+1)+".scen"
    # w_file = "instances/random_map/random-32-32-20-random-"+str(i+1)+".scen"
    r_file = "/home/ubuntu/yue-code/CBS/instance/first_priority/room-64-64-8/scen-random/room-64-64-8-random-"+str(i+1)+".scen"
    w_file = "/home/ubuntu/yue-code/CBS/instance/first_priority/room-64-64-8/scen-random-rotation-fix/room-64-64-8-random-"+str(i+1)+".scen"
    changescen(r_file,w_file)

for i in range(25):
    # r_file = "instances/random_map_temp/random-32-32-20-random-"+str(i+1)+".scen"
    # w_file = "instances/random_map/random-32-32-20-random-"+str(i+1)+".scen"
    r_file = "/home/ubuntu/yue-code/CBS/instance/first_priority/warehouse-10-20-10-2-1/scen-random/warehouse-10-20-10-2-1-random-"+str(i+1)+".scen"
    w_file = "/home/ubuntu/yue-code/CBS/instance/first_priority/warehouse-10-20-10-2-1/scen-random-rotation-fix/warehouse-10-20-10-2-1-random-"+str(i+1)+".scen"
    changescen(r_file,w_file)