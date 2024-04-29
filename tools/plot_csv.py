import csv
import sys
import numpy as np
import matplotlib.pyplot as plt


def main():
    if (len(sys.argv) != 2):
        print(f"Usage ./plot_csv foo.csv")
        exit(1)

    csv_path = sys.argv[1]
    print(f"Plotting {csv_path}")

    values = np.genfromtxt(csv_path, delimiter=',')
    indices = np.arange(0, len(values))
    time = indices / 44100
    time = time * 1000 # plot time in ms

    values = values[0:50000]
    indices = indices[0:50000]
    time = time[0:50000]

    fig, ax = plt.subplots()
    ax.plot(time, values)
    plt.show()

if __name__ == '__main__':
    main()
