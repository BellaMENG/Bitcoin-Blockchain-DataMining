from util import get_addrs
import matplotlib.pyplot as plt

dataset_path = "/home/zmengaa/data500k/txedges/datasets/analysis_results"

def plot_result(filename, output_fn):
    data = []
    with open(filename) as f:
        data = [int(line.rstrip()) for line in f]
    num_of_entris = len(data)
    
    fig, ax = plt.subplots()
    ax.plot(list(range(num_of_entris)), data)
    plt.savefig(output_fn)
    

def main():
    fn = input("data file name: ")
    output_fn = input("output file name: ")
    
    fn = dataset_path + fn
    output_fn = dataset_path + output_fn
    plot_result(fn, output_fn)


if __name__ == "__main__":
    main()
