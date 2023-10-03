#include "header.h"

// Function to check if backup exists
int is_backup(void) 
{
    struct stat sb;

    if (lstat("blockchain_storage.txt", &sb) == -1) {
        return 0;
    }

    return 1;
}


/* Functions to backup blockchain */ 
void save_to_file(blockchain_t* blockchain) {
    int fd = open("blockchain_storage.txt", O_WRONLY |O_CREAT | O_TRUNC, 0644);
    if (!fd) {
        printf("Error creating file\n");
    }
    write_blockchain(blockchain, fd);

    close(fd);
}

int write_blockchain(blockchain_t* blockchain, int fd) 
{
    write_blockchain_storage(blockchain, fd, blockchain->sync_toggle);

    if (blockchain->head == NULL) {
        free(blockchain);
        return 0;
    }

    node_t* temp = blockchain->head;
    block_t* temp_block;

    while (temp != NULL) 
    {
        write_node_storage(temp, fd);
        temp_block = temp->block;

        while (temp_block != NULL) {
            write_block_storage(temp_block, fd);
            temp_block = temp_block->next;
        }
        temp = temp->next;
    }
    
    remove_all_nodes(blockchain);
    free(blockchain);
    return 0;
}

void write_blockchain_storage(blockchain_t* blockchain, int fd, int sync) {
    blockchain_storage_t* blockchain_storage = malloc(sizeof(blockchain_storage_t));
    decimal_to_char(blockchain_storage->size, 10, blockchain->size);
    blockchain_storage->sync_toggle = sync + '0';
    write(fd, blockchain_storage->size, sizeof(blockchain_storage_t));
    free(blockchain_storage);
}

void write_node_storage(node_t* node, int fd) {
    node_storage_t* node_storage = malloc(sizeof(node_storage_t));
    decimal_to_char(node_storage->nid, 10, node->nid);
    decimal_to_char(node_storage->size, 10, node->size);
    write(fd, node_storage, sizeof(node_storage_t));
    free(node_storage);
}

void write_block_storage(block_t* block, int fd) {
    block_storage_t* block_storage = malloc(sizeof(block_storage_t));
    zero_padded_char(block_storage->bid, 10, block->bid);
    write(fd, block_storage, sizeof(block_storage_t));
    free(block_storage);
}


/* Functions to restore blockchain */
void open_backup_file(blockchain_t* blockchain) {

    int fd = open("blockchain_storage.txt", O_CREAT | O_RDWR, 0644);
    if (!fd) {
        printf("Error creating file\n");
    }

    blockchain->sync_toggle = read_blockchain_from_file(fd, blockchain);

    int i = 0;
    while (i < blockchain->size) {
        node_t* temp = read_node_from_file(fd, &blockchain);
        blockchain->size -= 1; // decrease to account for duplicate

        int j = 0;
        while (j < temp->size) {
            read_block_from_file(fd, blockchain, temp->nid);
            temp->size -= 1; // decrease to account for duplicate
            j++;
        }
        i++;
    }

    close(fd);
    
}

int read_blockchain_from_file(int fd, blockchain_t* blockchain) 
{
    blockchain_storage_t* blockchain_storage = malloc(sizeof(blockchain_storage_t));
    read(fd, blockchain_storage, sizeof(blockchain_storage_t));
    blockchain->size = strtol(blockchain_storage->size, NULL, 10);
    int sync_toggle = blockchain_storage->sync_toggle - '0';
    free(blockchain_storage);

    return sync_toggle;
}

node_t* read_node_from_file(int fd, blockchain_t** blockchain) 
{
    node_storage_t* node_storage = malloc(sizeof(node_storage_t));
    read(fd, node_storage, sizeof(node_storage_t));
    int nid = strtol(node_storage->nid, NULL, 10);
    node_t* node = create_node(nid);
    node->size = strtol(node_storage->size, NULL, 10);
    add_node(*blockchain, node);
    free(node_storage);

    return node;
}

void read_block_from_file(int fd, blockchain_t* blockchain, int nid) 
{
    block_storage_t* block_storage = malloc(sizeof(block_storage_t));
    read(fd, block_storage, sizeof(block_storage_t));
    block_t* block = create_block(block_storage->bid);
    add_block_to_node(blockchain, nid, block);
    free(block_storage);
}

