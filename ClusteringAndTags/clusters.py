import blocksci

chain = blocksci.Blockchain("/home/zmengaa/blocksci508241.config")
dataset_fp = "/home/zmengaa/data500k/txedges/datasets/"

def create_clusters():
    print("start to create clusters:")
    cm = blocksci.cluster.ClusterManager.create_clustering("blocksci_clusters", chain)
    print("finish creating clusters!")
    return cm


def load_clusters():
    cm = blocksci.cluster.ClusterManager(dataset_fp + dataset_fp + "blocksci_clusters", chain)
    return cm


def main():
    create_clusters()


if __name__ == "__main__":
    main()
