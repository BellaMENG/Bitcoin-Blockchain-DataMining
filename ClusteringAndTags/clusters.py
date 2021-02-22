import blocksci
import csv
from util import get_addrs

chain = blocksci.Blockchain("/home/zmengaa/blocksci508241.config")
dataset_fp = "/home/zmengaa/data500k/txedges/datasets/"
analysis_fp = dataset_fp + "analysis_results/"

def create_clusters():
    print("start to create clusters:")
    cm = blocksci.cluster.ClusterManager.create_clustering(dataset_fp + "blocksci_clusters", chain)
    print("finish creating clusters!")
    return cm


def load_clusters():
    cm = blocksci.cluster.ClusterManager(dataset_fp + "blocksci_clusters", chain)
    return cm


def getClusterIds(output_fn):
    cm = load_clusters()
    print("Number of clusters:", len(cm.clusters()))
    addr_fn = input("load the addresses, filename: ")
    addr_fn = dataset_fp + addr_fn
    addresses = get_addrs(addr_fn)
    
    unique_clusters = set()
    address_cluster = []
    for address in addresses:
        addr = chain.address_from_string(address)
        cluster_id = cm.cluster_with_address(addr).index
        unique_clusters.add(cluster_id)
        address_cluster.append([address, cluster_id])
        
    print("There are", len(unique_clusters), "clusters for", len(addresses), "addresses.")
    
    with open(output_fn, "w+") as f:
        f_writer = csv.writer(f, delimiter=' ')
        for entry in address_cluster:
            f_writer.writerow(entry)


def main():
    output_fn = input("Name of the cluster id file: ")
    output_fn = analysis_fp + output_fn
    getClusterIds(output_fn)


if __name__ == "__main__":
    main()
