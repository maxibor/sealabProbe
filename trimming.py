
temp = []
x = []
y = []
z = []
time = []
hour = 12
minute = 13

def time_update (hour, minute) :
    to_return = []
    if (hour == 23 and minute == 59) :
        hour = 0
    elif (minute == 59):
        hour = hour + 1
        minute = 0
    else :
        minute = minute + 1

    time_str = str(hour)+":"+str(minute)
    to_return.append(time_str)
    to_return.append(hour)
    to_return.append(minute)
    return(to_return)

first = 0
with open("RESULT.TXT", 'r') as f :
    for line in f :
        line = line.rstrip()
        if "temperature" not in line :
            if first != 0 :
                tUp = time_update(hour, minute)
                print(tUp)
                hour = tUp[1]
                minute = tUp[2]
                time.append(tUp[0])
            else :
                time.append(str(hour)+":"+str(minute))
                first +=1
            splitted = line.split(",")
            temp.append(splitted[0])
            x.append(splitted[1])
            y.append(splitted[2])
            z.append(splitted[3])

print("x : ", x)
print("y : ", y)
print("z : ", z)
print("time : ", time)
print("temp : ", temp)

with open("res_cleaned.csv", "w") as f2 :
    f2.write("time, temp, x, y, z\n")
    for a, b, c, d, e in zip(time, temp, x, y, z) :
        f2.write(str(a) + "," + str(b) +","+ str(c) + "," +str(d)+","+str(e)+"\n")
