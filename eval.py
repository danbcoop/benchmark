import statistics
import os
import matplotlib.pyplot as plt
import numpy as np
from numpy import array, linspace
from sklearn.neighbors import KernelDensity

index = {
    "PROCESS"   : 0,
    "TIME"      : 3,
    "DELTA"     : -2,

}

def scatter(time,deltas):
    plt.scatter(time, deltas, c='green', label='swap in')
    plt.legend()
    
    plt.title('Basic Scatter Plot')
    plt.xlabel('time')
    plt.ylabel('page fault handling time in us')
    plt.show() 

def violin(data1,data2,data3,data4):
    
    fig, axs = plt.subplots(nrows=1, ncols=1, figsize=(9, 4))

    # plot violin plot
    axs.violinplot([data1, data2, data3, data4],
                    showmeans=True,
                    showmedians=False)
    axs.set_title('Prefetcher comparisson')

    # plot box plot
    # axs[1].violinplot(data2, showmeans=True)
    # axs[1].set_title('leap')

    axs.yaxis.grid(True)
    axs.set_xticks([y+1 for y in range(4)], labels=['default','leap','leap_vma','per thread'])
    # adding horizontal grid lines
    # for ax in axs:
    #     ax.yaxis.grid(True)
    #     # ax.set_xticks([y + 1 for y in range(len(data))],
    #     #             labels=['x1'])
    #     ax.set_xlabel('Four separate samples')
    #     ax.set_ylabel('Observed values')
    axs.set_ylabel('Page fault handling time in µs')
    plt.show()

if __name__ == "__main__":
    filenames = list()
    directory = os.listdir()
    for file in directory:
        if ".txt" in file:
            if "time-delta" in file:
                filenames.append(file)

    deltas_tid = list()
    deltas_leap_vma = list()
    deltas_leap = list()
    deltas_default = list()
    time_tid = list()
    # time_leap = list()
    
    for fn in filenames:
        file = open(fn, "r")
        linecount = 0
        for line in file:
            if linecount >= 4000000:
                break
            line = line.split()
            if len(line)<7:
                continue
            if "measure-" in line[index["PROCESS"]]:
                linecount = linecount + 1
                if "tid" in fn:
                    deltas_tid.append(int(line[index["DELTA"]]))
                    time_tid.append(float(line[index["TIME"]][0:-1]))
                elif "vma" in fn:
                    deltas_leap_vma.append(int(line[index["DELTA"]]))
                    # time_leap.append(float(line[index["TIME"]][0:-1]))
                elif "leap" in fn:
                    deltas_leap.append(int(line[index["DELTA"]]))
                elif "default" in fn:
                    deltas_default.append(int(line[index["DELTA"]]))
                    
        
    cutoff_tid = np.quantile(deltas_tid,0.99)
    cutoff_leap = np.quantile(deltas_leap,0.99)
    cutoff_leap_vma = np.quantile(deltas_leap_vma,0.99)
    cutoff_default = np.quantile(deltas_default,0.99)
    deltas_tid = [d/1000 for d in deltas_tid if d <= cutoff_tid]
    deltas_leap = [d/1000 for d in deltas_leap if d <= cutoff_leap]
    deltas_leap_vma = [d/1000 for d in deltas_leap_vma if d <= cutoff_leap_vma]
    deltas_default = [d/1000 for d in deltas_default if d <= cutoff_default]
    print(f"tid mean: {statistics.mean(deltas_tid)} us, size {len(deltas_tid)}")
    print(f"leap mean: {statistics.mean(deltas_leap)} us, size {len(deltas_leap)}")
    print(f"leap_vma mean: {statistics.mean(deltas_leap_vma)} us, size {len(deltas_leap_vma)}")
    print(f"default mean: {statistics.mean(deltas_default)} us, size {len(deltas_default)}")

    # scatter(time_tid,deltas_tid)
    violin(deltas_default, deltas_leap, deltas_leap_vma, deltas_tid)

    # kde = KernelDensity(kernel='gaussian', bandwidth=3).fit(array(deltas).reshape(-1,1))
    # s = linspace(0, max(deltas)-100000)
    # e = kde.score_samples(s.reshape(-1, 1))
    # from scipy.signal import argrelextrema
    # mi, ma = argrelextrema(e, np.less)[0], argrelextrema(e, np.greater)[0]
    
    # # Get 3 clusters:
    # minima_vals = e[mi].tolist()
    # elist = e.tolist()
    
    # cluster_index = list()
    # for i in range(5):
    #     cluster_index.append(elist.index(min(minima_vals)))
    #     minima_vals.pop(minima_vals.index(min(minima_vals)))
        
    
    # cluster = s[cluster_index]
    # cluster.sort()
    # print(f"{[int(i) for i in cluster]}")

    # # print(f"{e[cluster_index]}")
    # # print(f"{e[mi]}")
    # # plt.plot(s, e)
    # # plt.show()
    
    # alloc = [d for d in deltas if d < cluster[0]]
    # swap_cache = [d for d in deltas if d >= cluster[0] and d < cluster[1]]
    # swap_in = [d for d in deltas if d >= cluster[1]]
    # plt.scatter([1 for _ in alloc], alloc, c='blue', label='pte_alloc()')
    # plt.scatter([1 for _ in swap_cache], swap_cache, c='red', label='swap cache')
    # plt.scatter([1 for _ in swap_in], swap_in, c='green', label='swap in')
    # plt.legend()
    
    # plt.title('Basic Scatter Plot')
    # plt.xlabel('X-axis')
    # plt.ylabel('Y-axis')
    # plt.show()
     