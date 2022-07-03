f = open("auto.txt","r")
p = open("result.txt","a")
line = f.read()
x = line.split("\n")
for i in x:
    y = i.split(" ")
    print("('{} {}', {}, {}),".format(y[0],y[1],y[2],y[3]))
    p.write("('{} {}', {}, {}),\n".format(y[0],y[1],y[2],y[3]))

f.close()
p.close()
