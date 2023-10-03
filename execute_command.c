#include "header.h"

int execute_command(int command, blockchain_t* blockchain, int nid, char* bid) 
{
    switch (command) {
        case 1:
            command_one(blockchain, nid);           // add node
            break;
        case 2:
            command_two(blockchain);                // remove all nodes
            break;
        case 3:
            command_three(blockchain, nid);         // remove node
            break;
        case 4:     
            command_four(blockchain, bid);          // add block to all nodes
            break;
        case 5:
            command_five(blockchain, nid, bid);     // add block
            break;
        case 6:
            command_six(blockchain, bid);           // remove block from all nodes
            break;
         case 7:
            command_seven(blockchain, nid, bid);    // remove block 
            break;
        case 8:
            print_blockchain(blockchain, 1);        // ls -l
            break;
        case 9:
            print_blockchain(blockchain, 0);        // ls
            break;
        case 10:
            command_ten(blockchain);                // sync
            break;
        case 11:
            command_eleven(blockchain);             // backup blockchain + quit
            return 0;
        case 0:
            printf("nok: command not found\n");
            return -1;
    }

    return 1;
}

void command_one(blockchain_t* blockchain, int nid) {
    if (is_node(blockchain, nid)) {
        printf("NOK: this node already exists\n");
    } else {
        node_t* node = create_node(nid);
        add_node(blockchain, node);
        // function to see if there are blocks on any nodes
        if (any_blocks(blockchain)) {
            blockchain->sync_toggle = 0;
        } 
        printf("OK\n");
    }   
}

void command_two(blockchain_t* blockchain) {
    if (blockchain->size == 0) {
        printf("NOK: blockchain is empty\n");
    } else {
        remove_all_nodes(blockchain);
        printf("OK\n");
    }
}

void command_three(blockchain_t* blockchain, int nid) {
    if (!is_node(blockchain, nid)) {
        printf("NOK: node doesn't exist\n");
    } else {
        remove_node(blockchain, nid);
        printf("OK\n");
    }
}

void command_four(blockchain_t* blockchain, char* bid) {
    if (is_block_any_node(blockchain, bid)) {
        printf("NOK: this block already exists\n");
        free(bid);
    } else {
        add_block_to_all_nodes(blockchain, bid);
        printf("OK\n");
    }
}

void command_five(blockchain_t* blockchain, int nid, char* bid) {
    if (!is_node(blockchain, nid)) {
        printf("NOK: node doesn't exist\n");
        free(bid);
    } else if (is_block(blockchain, bid, nid)) {
        printf("NOK: this block already exists\n");
        free(bid);
    } else {
        block_t* block = create_block(bid);
        add_block_to_node(blockchain, nid, block);
        if (blockchain->size > 1) {
            blockchain->sync_toggle = 0;
        }
        printf("OK\n");
    }
}

void command_six(blockchain_t* blockchain, char* bid) {
    if (!is_block_any_node(blockchain, bid)) {
        printf("NOK: block doesn't exist\n");
        free(bid);
    } else {
        remove_block_all_nodes(blockchain, bid);
        printf("OK\n");
    } 
}

void command_seven(blockchain_t* blockchain, int nid, char* bid) {
    if (nid == 0) {
        if (!is_block_any_node(blockchain, bid)) {
            printf("NOK: block doesn't exist\n");
            free(bid);
        } else {
            remove_block_all_nodes(blockchain, bid);
            printf("OK\n");
        }
    } else if (!is_block(blockchain, bid, nid)) {
        printf("NOK: block doesn't exist\n");
        free(bid);
    } else {
        remove_block_node(blockchain, bid, nid);
        if (blockchain->size > 1 && any_blocks(blockchain)) {
            blockchain->sync_toggle = 0;
        }
        printf("OK\n");
    }
}

void command_ten(blockchain_t* blockchain) {
    if (is_synced(blockchain)) {
        printf("OK\n");
    } else {
        sync_blockchain(blockchain);
        printf("OK\n");
    }
}

void command_eleven(blockchain_t* blockchain) {
    printf("Backing up blockchain...\n");
    save_to_file(blockchain);
}
