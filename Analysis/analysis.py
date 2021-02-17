import blocksci


def get_balances(chain, addresses, balance_file):
    balances = []
    for address in addresses:
        addr = chain.address_from_string(address)
        balances.append(addr.balance())
    
    with open(balance_file, 'w') as f:
        for balance in balances:
            f.write("%s\n" % balance)


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
    
    balance_file = input("file path of balance file: ")
    get_balances(chain, addresses, balance_file)
    
    
if __name__ == "__main__":
    main()
