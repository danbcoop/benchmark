import statistics
import os

index = {
    "PROCESS"   : 0,
    "TIME"      : -2,
}

if __name__ == "__main__":
    filenames = list()
    directory = os.listdir()
    for file in directory:
        if ".txt" in file:
            if "time-delta" in file:
                filenames.append(file)

    deltas = list()
    for fn in filenames:
        file = open(fn, "r")
        for line in file:
            line = line.split()
            # for i in line:
            #     print(i, end=", ")
            if "measure-" in line[index["PROCESS"]]:
                deltas.append(int(line[index["TIME"]]))
        
    print(f"sum: {sum(deltas)/1000/1000} s")
    print(f"mean: {statistics.mean(deltas)/1000} us")
     