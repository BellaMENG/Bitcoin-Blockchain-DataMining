import blocksci
dataset_folder = "/home/zmengaa/data500k/txedges/datasets/"

def get_balances(chain, addresses, balance_file):
    balances = []
    for address in addresses:
        addr = chain.address_from_string(address)
        balances.append(addr.balance())
    
    with open(balance_file, 'w') as f:
        for balance in balances:
            f.write("%s\n" % balance)


def get_txes(chain, addresses, tx_file):
    txes = []
    for address in addresses:
        addr = chain.address_from_string(address)
        txes.append(len(addr.txes.to_list()))
        
    with open(tx_file, 'w') as f:
        for tx in txes:
            f.write("%s\n" % tx)
            
            
def get_in_out_txes(chain, addresses):
    intx_file = input("file path of output file to number of in_txes: ")
    outtx_file = input("file path of output file to number of out_txes: ")

    intx_file = dataset_folder + intx_file
    outtx_file = dataset_folder + outtx_file
    in_txes = []
    out_txes = []
    for address in addresses:
        addr = chain.address_from_string(address)
        in_txes.append(len(addr.in_txes.to_list()))
        out_txes.append(len(addr.out_txes.to_list()))
    
    with open(intx_file, 'w') as f:
        for tx in in_txes:
            f.write("%s\n" % tx)
    
    with open(outtx_file, 'w') as f:
        for tx in out_txes:
            f.write("%s\n" % tx)
            

def get_balances_n_txes(chain, addresses):
    balance_file = input("file path of balance file: ")
    tx_file = input("file path of tx number file: ")
    balance_file = dataset_folder + balance_file
    tx_file = dataset_folder + tx_file
    
    balances = []
    txes = []
    for address in addresses:
        addr = chain.address_from_string(address)
        balances.append(addr.balance())
        txes.append(len(addr.txes.to_list()))
        
    with open(balance_file, 'w') as f:
        for balance in balances:
            f.write("%s\n" % balance)

    with open(tx_file, 'w') as f:
        for tx in txes:
            f.write("%s\n" % tx)


def main():
#    blocksci_core = input("Get the path of the core data files: ")
    chain = blocksci.Blockchain("/home/zmengaa/blocksci508241.config")
    
    print("Number of addresses: ", chain.address_count(blocksci.address_type.pubkey))
    
    filename = input("file name of the addresses file:")
    filename = dataset_folder + filename
    addresses = []
    with open(filename) as f:
        addresses = [line.rstrip() for line in f]
    print("number of addresses:", len(addresses))
    
    get_in_out_txes(chain, addresses)
#    get_balances_n_txes(chain, addresses)
    
    
    
if __name__ == "__main__":
    main()
