# Welcome to My Blockchain
***

## Task
Blockchain is a command-line tool that helps you work with a blockchain. It provides a simple interface where you can execute commands to manage your blockchain.

Feautures listed: 
* Add Node: Add a node to the blockchain.
* Remove Node: Remove nodes from the blockchain.
* Add Block: Add a block to nodes in the blockchain.
* Remove Block: Remove blocks from nodes.
* List Nodes: List all nodes in the blockchain.
* Sync Blockchain: Synchronize all nodes.
* Quit: Save and exit the blockchain.

When you run the program (it loads a backup if there is one), and then a prompt appears and allows you to use it.  
This prompt allows to execute commands. When the commands are successful they display "ok" and if not, "nok: info" is an error message.

## Description
The program starts by checking the previous backups. 
If there is a backup, it will continue by displaying a prompt that tells the number of nodes in the Blockchain and waits for user input. If there is not a backup file, it will say [s0] and wait for the input. 
In any case, the program will continue to prompt accordingly and it will be waiting for the arguments. 
After receiving arguments it will get the received data, convert them to processible types, and execute the commands as intended. 

You can see the features in the list given in the Task section.
There are different *.c files for: 
* displaying the prompt and receiving arguments, 
* executing the commands, 
* a custom implementation of the 'readline' function,
* functions to handle the nodes,
* syncing the new data, 
* backing up the data, 
* and helper functions 

All helper functions are custom and well-thought out functions made by our team member Rebecca.

## Installation
To install the program, you can access the program by gitea. There is a Makefile provided with the program. Run "make my_blockchain" in your command line. Compile the program (instructions in usage) and it should return my_blockchain if successful.

## Usage
Enter "./my_blockchain" in your command line to start the program.
Use any of the following commands to manage your blockchain:
add node nid ... add a nid identifier to the blockchain node.
rm node nid... remove nodes from the blockchain with a nid identifier. If nid is '*', then all nodes are impacted.
add block bid nid... add a bid identifier block to nodes identified by nid. If nid is '*', then all nodes are impacted.
rm block bid... remove the bid identified blocks from all nodes where these blocks are present.
ls... list all nodes by their identifiers. The option -l attaches the blocks bid's associated with each node.
sync... synchronize all of the nodes with each other. Upon issuing this command, all of the nodes are composed of the same blocks.
quit... save and leave the blockchain.

### The Core Team
Rebecca Silverstein (silverst_r), Selcuk Aksoy (aksoy_s)

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>