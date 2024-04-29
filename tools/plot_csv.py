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

    fig, ax = plt.subplots()
    ax.plot(indices, values)
    plt.show()

if __name__ == '__main__':
    main()
