import blocksci


def main():
#    blocksci_core = input("Get the path of the core data files: ")
    chain = blocksci.Blockchain("/home/zmengaa/blocksci.config")

    print("Number of addresses: ", chain.address_count(blocksci.address_type.pubkey))
    print("Number of addresses: ", chain.address_count())

if __name__ == "__main__":
    main()
