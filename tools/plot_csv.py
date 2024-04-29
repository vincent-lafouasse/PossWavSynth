import csv
import sys
import numpy as np

def main():
    if (len(sys.argv) != 2):
        print(f"Usage ./plot_csv foo.csv")
        exit(1)

    csv_path = sys.argv[1]
    print(f"Plotting {csv_path}")

    values = np.genfromtxt(csv_path, delimiter=',')
    print(values)

if __name__ == '__main__':
    main()
