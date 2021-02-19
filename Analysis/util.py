
def get_addrs(addr_filename):
    addresses = []
    with open(addr_filename) as f:
        addresses = [line.rstrip() for line in f]
    print("Number of addresses: ", len(addresses))
    
    return addresses
