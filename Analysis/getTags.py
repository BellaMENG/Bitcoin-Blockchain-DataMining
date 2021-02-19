import blocksci
import yaml
import os
import csv
from util import get_addrs

dataset_path = "/home/zmengaa/data500k/txedges/datasets/"


def get_tags(chain, addresses, tags_filename, output_filename):
    # get tags
    tags_file = open(tags_filename, "r")
    data = yaml.load(tags_file)
    
    labels = {}
    for entry in data['tags']:
        addr = entry['address']
        label = ""
        try:
            label = entry['category']
        except:
            label = entry['abuse']
        labels[addr] = label
    
    result = []
    with_label = 0
    for addr in addresses:
        if addr in labels:
            result.append([addr, labels[addr]])
            with_label += 1
        else:
            result.append([addr, ""])
    
    print("Number of addresses with label:", with_label)
    with open(output_filename, "w+") as f:
        f_writer = csv.writer(f, delimiter=' ')
        for entry in result:
            f_writer.writerow(entry)
    

def main():
    
    chain = blocksci.Blockchain("/home/zmengaa/blocksci508241.config")
    print("Number of addresses:", chain.address_count(blocksci.address_type.pubkey))
    addr_filename = input("file name of the addresses:")
    addr_filename = dataset_path + addr_filename
    addresses = get_addrs(addr_filename)
    
    tags_fn = input("file name of tags:")
    tags_fn = dataset_path + "packs/" + tags_fn
    
    output_fn = input("file name of output:")
    output_fn = dataset_path + output_fn
    
    get_tags(chain, addresses, tags_fn, output_fn)
    
if __name__ == "__main__":
    main()
