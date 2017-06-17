
temp = []
x = []
y = []
z = []
time = []
hour = 17
minute = 10
second = 0

def time_update (hour, minute, second) :
    to_return = []
    if (second == 59) :
        second = 0
        minute = minute + 1
    if (minute == 59) :
        minute = 0
        hour = hour + 1
    if (hour == 23) :
        hour = 0
    else :
        minute = minute +1
    time_str = str(hour)+":"+str(minute)+":"+str(second)
    to_return.append(time_str)
    to_return.append(hour)
    to_return.append(minute)
    to_return.append(second)
    return(to_return)

with open("result.csv", 'r') as f :
    for line in f :
        line = line.rstrip()
        if "date" not in line :
            tUp = time_update(hour, minute, second)
            print(tUp)
            hour = tUp[1]
            minute = tUp[2]
            second = tUp[3]
            time.append(tUp[0])
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
