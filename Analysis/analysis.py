import blocksci


def main():
    blocksci_core = input("Get the path of the core data files")
    chain = blocksci.Blockchain(blocksci_core)
    chain = chain[500000]
    
    

if __name__ == "__main__":
    main()
