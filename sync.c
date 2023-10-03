#include "header.h"

// Function to check if blockchain is synced
int is_synced(blockchain_t* blockchain) 
{
    if (!blockchain->sync_toggle){
        return 0;
    } else {
        return 1;
    }
}

int sync_blockchain(blockchain_t* blockchain)
{ 
    node_t* previous_node = blockchain->head;
    node_t* temp_node = blockchain->head;
    block_t* temp_block;
    block_t* new_block;

    int headnode_increase = 0;
    int increase = 0;

    // Headnode
    temp_node = blockchain->head->next;

    while (temp_node != NULL) {
        temp_block = temp_node->block;
        while (temp_block != NULL) {
            if (!is_block(blockchain, temp_block->bid, previous_node->nid)) {
                new_block = create_block(temp_block->bid);
                add_block_to_node(blockchain, previous_node->nid, new_block);
                previous_node->size += 1;
                headnode_increase += 1;
            } 
            temp_block = temp_block->next;
        }
        temp_node = temp_node->next;
    } 

    temp_node = blockchain->head->next;

    // Iterate through nodes
    while (temp_node != NULL) 
    {
        if (temp_node->block == blockchain->head->block) {
            temp_node->size += headnode_increase;
        }
        else if (temp_node->block == previous_node->block) {
            temp_node->size += increase;
        } 
        else if (temp_node->block == NULL && previous_node->block == blockchain->head->block) {
            temp_node->block = previous_node->block;
            temp_node->size += headnode_increase;
        } 
        else if (temp_node->block == NULL) {
            temp_node->block = previous_node->block;
            temp_node->size += increase;
        } 
        else { 
            temp_block = blockchain->head->block;
            while (temp_block != NULL) {
                if (!is_block(blockchain, temp_block->bid, temp_node->nid)) {
                    new_block = create_block(temp_block->bid);
                    add_block_to_node(blockchain, temp_node->nid, new_block);
                    temp_node->size += 1;
                    increase += 1;
                }
                temp_block = temp_block->next;
            }
        }
        previous_node = temp_node;
        temp_node = temp_node->next;
    }

    blockchain->sync_toggle = 1;

    return 0;

}
