import blocksci
import yaml
import os
import csv


def get_tags(chain, addresses, tags_filename, output_filename):
    # get tags
    tags_file = open(tags_filename, "r")
    data = yaml.load(tags_file)
    
    labels = {}
    for entry in data['tags']:
        addr = entry['address']
        label = entry['category']
        labels[addr] = label
    
    result = []
    for addr in addresses:
        if addr in labels:
            result.append([addr, labels[addr]])
        else:
            result.append([addr, ""])
    
    with open(output_filename, "r") as f:
        f_writer = csv.writer(f, delimiter=',')
        for entry in result:
            f_writer.writerow(entry)
    

def main():
    chain = blocksci.Blockchain("/home/zmengaa/blocksci508241.config")
    print("Number of addresses:", chain.address_count(blocksci.address_type.pubkey))
    
    
if __name__ == "__main__":
    main()
