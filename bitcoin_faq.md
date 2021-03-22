## Purely Bitcoin and Bitcoin Blockchain
#### What is a Satoshi?
It is equivalent to 0.00000001 BTC and is currently the smallest transaction unit of Bitcoin.

#### Bitcoin protocols and clients
One of the most original ones is Bitcoin Core. The implementation of Bitcoin Core follows the Bitcoin protocol.

#### What are the nodes in the Bitcoin P2P network?
According to my understanding, there are two kinds of roles: miners and participants who just want to make transactions. For miners, they listen to and collect broadcasts of transactions, so they can calculate (actually try out) the nonce. For people who just want to make transactions, they just listen to and collect the next computed chain. All the nodes are supposed to keep their own copy of the ledger.

**Updated: Now it makes more sense to say that, miners are actually users that own and run ASIC machines. Nodes are the users participating in the transaction of Bitcoin. According to my understanding, it is the case that a lot of miners are calculating the hashes under one certain address. They have their own external protocols to split the reward.

#### What is the order of transactions appearing in blocks? Is it by timestamp of each transaction?
Now according to my understanding, different groups of miners may be working on a set of different transactions they wish to apend to the blockchain.

#### What about the process of broadcasting? What is the delay and how do information spread in this P2P network?

#### As a decentralized system, how to make sure this whole process is synchronized?
According to a video by computerphile, there are three kinds of systems. The first kind is centralized, where users request information from a central database. Then there is decentralized system, or P2P system, where fractions of information are stored in different peers in the network. Then there is the system Bitcoin is adopting. In this system, each peer/node has a complete copy of the information.

As for this system of bitcoin, the broadcasting of transactions and blocks is always sent to the neighbors of the node. Refer to "Information Propagation in the Bitcoin Network" for more details.

#### How do miners choose transactions to include? How do they refuse to include transactions with not enough transaction fee?
Miners are free to choose which transactions to include. They usually choose transactions with higher fees to maximize the rewards. One of the posts say that Bitcoin do not relay transactions that do not have transaction fees. So these transactions will not even reach miner nodes.

#### Follow up question: what are the implementations of such process of choosing transactions?
Check this wiki page: [feerates](https://en.bitcoin.it/wiki/Miner_fees#Feerates) for more information.

#### Do mining award and transaction fees go to the same address who found the nonce first?
Yes. Both mining award, which is a fixed number given the height of the block, and all transaction fees are given to the miner or group of miners who found the valid nonce.

#### What are the underlying hash functions? Which procedures adopted which hash functions?
#### Why is quantum computing not a potential threat for Bitcoin in terms of mining and the security of ownership of bitcoins, i.e, a threat to ECDSA?
#### How does the protocol of trying nonces and broadcasting results look like? Do people implement their own versions?
#### Merkle Trees and its application in Bitcoin protocol?
#### Scripting in Bitcoin protocol?
#### What is mempool and how does it work?
#### How does Bitcoin protocol handle possible partition of the Bitcoin Network?
According to the paper "Information propagation in the Bitcoin network", the partitions are not explicitly detected. A sudden drop of the rate of finding a new block might indicate such behavior.

## External information
#### With the concept of mining pool, exactly which address does the mining award and all the transaction fees go to?

#### Mining pools:
- There are a lot of miner reward systems, such as PPS, PROP, PPLNS, PPLNT and so on.
- Now it makes more sense to say that each pool has its own address and the participants that contributed computing power will be the payees of mining pool according to the rewarding system a certain pool is following.


## Questions to answer:
#### How does the PageRank work in the graph? How is it implemented?
#### How does k-means work in the graph? How to evaluate k-means algorithm?
#### What is clustering in Bitcoin graph? Bitcoin address clustering, address linking, and address association
#### How to integrate the idea of Bitcoin pair?


### [A Fistful of Bitcoins: Characterizing Payments Among Men with No Names](https://cseweb.ucsd.edu/~smeiklejohn/files/imc13.pdf)

#### How are the two heuristics defined formally?
#### How did they detect and handle false positives?
#### Can heuristic 2 identify all of the change addresses correctly? (e.g. Is there a lot of false negatives?)
#### Can we use machine learning to learn irregular patterns in the graph? For example, if the same change address is used twice within a short time period?
#### What is the history of Bitcoin gambling and what is the current situation?
#### What's the current money laundering situation and what's the research work about it like?
#### What's the theft situation?
#### (Random/irrelevant) What would happen if Bitcoin was completely got rid of? In terms economics and etc.

#### [A First Estimation of the Proportion of Cybercriminal Entities in the Bitcoin Ecosystem using Supervised Machine Learning](https://ieeexplore.ieee.org/abstract/document/8258365)

#### Clustering methodologies:
- **Co-spend clustering**: whenever two or more input addresses are used for one transaction
- **Intelligence-based clustering**: where information and intelligence outside of the blockchain obtained when data partnership is used
- **Behavioural clustering**: where clustering is done according to known patterns that are dictated by the wallet software or systems used

![equation](http://www.sciweavers.org/tex2img.php?eq=1%2Bsin%28mc%5E2%29&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=)
#### [Evaluating User Privacy in Bitcoin](https://eprint.iacr.org/2012/596.pdf)
Financial Cryptography and Data Security 2013, Cited by 609\
- The authors evaluated user privacy in Bitcoin by first cluster the address graph using the two heuristics**. From the user entity graph obtained from the previous graph, the authors applied k-means and Hierarchical agglomerative clustering (HAC) algorithms.
<img width="674" alt="sim_dist" src="https://user-images.githubusercontent.com/30502668/111938015-07af6f80-8b04-11eb-83a9-bfdb857ec332.png">
