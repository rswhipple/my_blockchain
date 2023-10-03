#include "header.h"
// Function to create a blockchain
blockchain_t* create_blockchain(void)
{
    blockchain_t* blockchain = malloc(sizeof(blockchain_t));
    blockchain->size = 0;
    blockchain->sync_toggle = 1;
    blockchain->head = NULL;
    blockchain->tail = NULL;
    return blockchain;
}

// Function to create a node
node_t* create_node(int nid)
{
    node_t* node = malloc(sizeof(node_t));
    node->nid = nid;
    node->size = 0;
    node->block = NULL;
    node->next = NULL;
    return node;
}

// Function to add a node to a blockchain
void add_node(blockchain_t* blockchain, node_t* node)
{
    if (blockchain->head == NULL)
    {
        blockchain->head = malloc(sizeof(node_t));
        blockchain->head = node;
        blockchain->tail = node;
    }
    else
    {
        blockchain->tail->next = node;
        blockchain->tail = node;
    }
    blockchain->size += 1;
}

// Function to check if a node already exists
int is_node(blockchain_t* blockchain, int nid)
{
    node_t* temp = blockchain->head;
    while (temp != NULL)
    {
        if (temp->nid == nid)
        {
            return 1;
        }
        temp = temp->next;
    }

    return 0;
}

// Return a pointer to specific node
node_t* find_node(blockchain_t* blockchain, int nid, node_t** previous_node) 
{
    node_t* temp_node = blockchain->head;

    while (temp_node != NULL) 
    {
        if (temp_node->nid == nid) {
            return temp_node;
        }
        *previous_node = temp_node;
        temp_node = temp_node->next;
    }

    return NULL; 
}

// Function to remove a node from a blockchain 
int remove_node(blockchain_t* blockchain, int nid)
{
    node_t* node_placeholder;
    node_t* prev_node;

    // Find node to remove
    node_placeholder = find_node(blockchain, nid, &prev_node);
    
    block_t* current_block = node_placeholder->block;
    block_t* temp_block;

    // See if node has blocks
    if (current_block == NULL) {
        free(node_placeholder);
        blockchain->size -= 1;
        return 0;
    }

    while (current_block != NULL) {
        temp_block = current_block->next;
        remove_block_node(blockchain, current_block->bid, node_placeholder->nid);
        current_block = temp_block;
    }

    // If headnode or !headnode
    if (node_placeholder == blockchain->head) {
        blockchain->head = blockchain->head->next;
        if (node_placeholder->next == NULL)
        {
            blockchain->tail = NULL;
        }
    } else {
        prev_node->next = node_placeholder->next;
    }

    free(node_placeholder);
    blockchain->size -= 1;
    return 0;

}

// Function to remove a node from a blockchain
void remove_all_nodes(blockchain_t* blockchain)
{
    node_t* temp_node = blockchain->head;
    node_t* next_node = blockchain->head;

    while (temp_node != NULL) {
        next_node = temp_node->next;
        remove_node(blockchain, temp_node->nid);
        temp_node = next_node;
        if (next_node != NULL) {
            next_node = next_node->next;
        }
    }

    blockchain->sync_toggle = 1;
}


// Function to create a block
block_t* create_block(char* bid)
{
    block_t* block = malloc(sizeof(block_t));
    block->bid = malloc(sizeof(char) * strlen(bid) + 1);
    my_strcpy(block->bid, bid);
    block->next = NULL;
    return block;
}

// Check if any blocks are in the blockchain
int any_blocks(blockchain_t* blockchain) 
{
    node_t* temp = blockchain->head;

    while (temp != NULL)
    {
        if (temp->block != NULL)
        {
            return 1;
        }
        temp = temp->next;
    }

    return 0;
}

// Function to check if a block already exists in specific node
int is_block(blockchain_t* blockchain, char* bid, int nid) 
{
    node_t* temp = blockchain->head;
    while (temp != NULL)
    {
        if (temp->nid == nid)
        {
            break;
        }
        temp = temp->next;
    }

    block_t* block_temp = temp->block;
    char* bid_temp = malloc(sizeof(char) * 10);

    while (block_temp != NULL)
    {
        strcpy(bid_temp, block_temp->bid);
        if (strcmp(bid_temp, bid) == 0)
            {
                return 1;
            }
            block_temp = block_temp->next;
    }
    free(bid_temp);

    return 0;
}

// Function to check if a block already exists in any node
int is_block_any_node(blockchain_t* blockchain, char* bid) {
    node_t* temp = blockchain->head;
    while (temp != NULL)
    {
        block_t* block_temp = temp->block;
        char* bid_temp = malloc(sizeof(char) * 10);
        while (block_temp != NULL)
        {
            strcpy(bid_temp, block_temp->bid);
            if (strcmp(bid_temp, bid) == 0)
            {
                return 1;
            }
            block_temp = block_temp->next;
        }
        free(bid_temp);
        temp = temp->next;
    }

    return 0;
}

// Function to add a block to a node
int add_block_to_node(blockchain_t* blockchain, int nid, block_t* block)
{
    node_t* temp = blockchain->head;
    node_t* node_placeholder;
    block_t* temp_block;

    int block_added = 0;

    // Iterate through nodes to find correct nid
    node_placeholder = find_node(blockchain, nid, &temp);

    // Initiate temp_block
    temp_block = node_placeholder->block;

    // If block linked list is empty, add block
    if (temp_block == NULL)
    {
        node_placeholder->block = block;
        block_added = 1;
        node_placeholder->size += 1;
        return 0;
    } 

    // Add block to node if it doesn't already exist in node
    if (!is_block(blockchain, block->bid, nid)) {
        while (temp_block->next != NULL)
        {
            temp_block = temp_block->next;
        }
        temp_block->next = block;
        block_added = 1;
        node_placeholder->size += 1;
    }

    // If other nodes have the same blocklist, increase their size
    temp = node_placeholder->next;
    while (block_added && temp != NULL) {
        if (temp->block == node_placeholder->block && is_block(blockchain, block->bid, temp->nid)) {
            temp->size += 1;
        }
        temp = temp->next;
    }

    return 0;
}

// Function to add a block to all nodes
void add_block_to_all_nodes(blockchain_t* blockchain, char* bid)
{
    block_t* block = create_block(bid);
    node_t* temp_node = blockchain->head;

    while (temp_node != NULL) {
        add_block_to_node(blockchain, temp_node->nid, block);
        temp_node = temp_node->next;
    }
}

// Function to remove a block from a specific node
int remove_block_node(blockchain_t* blockchain, char* bid, int nid)
{
    node_t* temp;
    node_t* prev_node = blockchain->head;
    block_t* temp_block;
    block_t* temp_block_prev;

    // Find node to remove
    temp = find_node(blockchain, nid, &prev_node);

    // Initiate temp_block
    temp_block = temp->block;
    temp_block_prev = prev_node->block;

    char* bid_temp = malloc(sizeof(char) * 10);

    // Corner case: if block to remove is head of linked list, and there is more than one node with list
    while (temp_block != NULL) {
        strcpy(bid_temp, temp_block->bid);
        if (strcmp(bid_temp, bid) == 0)
        {
            // If block is at the head of linked list
            if (temp_block == temp->block) {
                temp->block = temp_block->next;
                free(temp_block);
                temp->size -= 1;
                return 1;
            } else {
                temp_block_prev->next = temp_block->next;
                free(temp_block);
                temp->size -= 1;
                return 1;
            }
        }
        temp_block_prev = temp_block;
        temp_block = temp_block->next;
    }
    
    return 0;
}

// Function to remove a block from all nodes
int remove_block_all_nodes(blockchain_t* blockchain, char* bid) 
{
    node_t* temp = blockchain->head;
    while (temp != NULL) {
        remove_block_node(blockchain, bid, temp->nid);
        temp = temp->next;
    }

    return 0;
}


// Function to print blockchain
void print_blockchain(blockchain_t* blockchain, int l_flag) 
{
    node_t* temp = blockchain->head;
    while (temp != NULL) {
        printf("%i", temp->nid);
        if (l_flag) {
            printf(":");
            block_t* block_temp = temp->block;
            while (block_temp != NULL) {
                printf(" %s", block_temp->bid);
                if (block_temp->next != NULL) {
                    printf(",");
                }
                block_temp = block_temp->next;
            }
        }
        printf("\n");
        temp = temp->next;
    }
}

