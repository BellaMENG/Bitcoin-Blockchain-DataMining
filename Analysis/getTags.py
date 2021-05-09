'''
python3 getTags.py
Number of addresses: 426868262
file name of the addresses:largest5k_addresses.dat
Number of addresses:  5000
file name of tags:walletexplorer.yaml
file name of output:5kaddr_with_label.dat
Number of addresses with label: 30
name of label distribution output file: label_dist.dat
'''

import blocksci
import yaml
import os
import csv
import json
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
    label_dist(result)
    

def label_dist(labels):
    label_count = 2{}
    for entry in labels:
        addr, label = entry
        if label in label_count:
            label_count[label] += 1
        else:
            label_count[label] = 1
    
    fn = input("name of label distribution output file: ")
    fn = dataset_path + fn
    with open(fn, "w+") as f:
        json.dump(label_count, f)
            


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
