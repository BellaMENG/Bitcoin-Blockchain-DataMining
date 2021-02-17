import blocksci


def main():
#    blocksci_core = input("Get the path of the core data files: ")
    chain = blocksci.Blockchain("/home/zmengaa/blocksci.config")

    print("Number of addresses: ", chain.address_count(blocksci.address_type.pubkey))
#    print("Number of addresses: ", chain.address_count())
    
    filename = input("file path of the addresses file: ")
    addresses = []
    with open(filename) as f:
        addresses = [line.rstrip() for line in f]
    print("number of addresses:", len(addresses))
    
    
if __name__ == "__main__":
    main()
