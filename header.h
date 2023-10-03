#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

/* STRUCTS */
#ifndef _STRUCT_READ_LINE_
#define _STRUCT_READ_LINE_
struct read_line_s {
    char *storage;
    char *leftover;
}; typedef struct read_line_s read_line_t;
#endif

// Create a struct to represent a block
#ifndef STRUCT_BLOCK
#define STRUCT_BLOCK
struct block
{
    char* bid;
    struct block* next;
}; typedef struct block block_t;
#endif

// Create a struct to represent a node
#ifndef STRUCT_BLOCKCHAIN_NODE
#define STRUCT_BLOCKCHAIN_NODE
struct blockchain_node
{
    int nid;
    int size;
    block_t* block;
    struct blockchain_node* next;
}; typedef struct blockchain_node node_t;
#endif

// Create a struct to represent a blockchain
#ifndef STRUCT_BLOCKCHAIN
#define STRUCT_BLOCKCHAIN
struct blockchain
{
    int size;
    int sync_toggle; // 0 = not synced, 1 = synced
    node_t* head;
    node_t* tail;
}; typedef struct blockchain blockchain_t;
#endif

// Create a struct to represent a blockchain for storage
#ifndef STRUCT_BLOCKCHAIN_STORAGE
#define STRUCT_BLOCKCHAIN_STORAGE
struct blockchain_storage
{
    char size[10];
    char sync_toggle; 
}; typedef struct blockchain_storage blockchain_storage_t;
#endif

#ifndef STRUCT_BLOCKCHAIN_NODE_STORAGE
#define STRUCT_BLOCKCHAIN_NODE_STORAGE
struct blockchain_node_storage
{
    char nid[10];
    char size[10];
}; typedef struct blockchain_node_storage node_storage_t;
#endif

#ifndef STRUCT_BLOCK_STORAGE
#define STRUCT_BLOCK_STORAGE
struct block_storage_s
{
    char bid[10];
}; typedef struct block_storage_s block_storage_t;
#endif

/* MACROS */
#define READLINE_READ_SIZE 512

/* function prototypes cli.c */
void display_prompt(blockchain_t* blockchain);
char** parse_args(char* param_1);
int get_command(char** argv);
int convert_args(char** args, int command, char** bid);

/* function prototypes execute_command.c */
int execute_command(int command, blockchain_t* blockchain, int nid, char* bid);
void command_one(blockchain_t* blockchain, int nid);
void command_two(blockchain_t* blockchain);
void command_three(blockchain_t* blockchain, int nid);
void command_four(blockchain_t* blockchain, char* bid);
void command_five(blockchain_t* blockchain, int nid, char* bid);
void command_six(blockchain_t* blockchain, char* bid);
void command_seven(blockchain_t* blockchain, int nid, char* bid);
void command_ten(blockchain_t* blockchain);
void command_eleven(blockchain_t* blockchain);

/* function prototypes in readline.c */
char *my_readline(int fd, read_line_t **buf);
int is_echo(char* string, int bytes);
int copy_first_line(char** first_line, char** leftover, char* src, int src_len);
int convert_newline_char(char* string, int bytes);
void init_my_readline(read_line_t **buf);

/* function prototypes blockchain.c */
blockchain_t* create_blockchain(void);
node_t* create_node(int nid);
void add_node(blockchain_t* blockchain, node_t* node);
int is_node(blockchain_t* blockchain, int nid);
node_t* find_node(blockchain_t* blockchain, int nid, node_t** previous_node);
int remove_node(blockchain_t* blockchain, int nid);
void remove_all_nodes(blockchain_t* blockchain);
int decrease_node_size(blockchain_t* blockchain);
block_t* create_block(char* bid);
int any_blocks(blockchain_t* blockchain);
int is_block(blockchain_t* blockchain, char* bid, int nid);
int is_block_any_node(blockchain_t* blockchain, char* bid);
int add_block_to_node(blockchain_t* blockchain, int nid, block_t* block);
void add_block_to_all_nodes(blockchain_t* blockchain, char* bid);
int remove_block_node(blockchain_t* blockchain, char* bid, int nid);
int remove_block_all_nodes(blockchain_t* blockchain, char* bid);
void print_blockchain(blockchain_t* blockchain, int l_flag) ;

/* function prototypes sync.c */
int is_synced(blockchain_t* blockchain);
int sync_blockchain(blockchain_t* blockchain);

/* function prototypes backup.c */
void save_to_file(blockchain_t* blockchain);
int write_blockchain(blockchain_t* blockchain, int fd);
void write_blockchain_storage(blockchain_t* blockchain, int fd, int sync);
void write_node_storage(node_t* node, int fd);
void write_block_storage(block_t* block, int fd);
int is_backup(void);
void open_backup_file(blockchain_t* blockchain);
int read_blockchain_from_file(int fd, blockchain_t* blockchain);
node_t* read_node_from_file(int fd, blockchain_t** blockchain);
void read_block_from_file(int fd, blockchain_t* blockchain, int nid);

/* function prototypes helper.c */
char *my_realloc_str(char* ptr, size_t size);
char *my_strchr(char* str_1, char char_1);
int my_strchr_index(char* str_1, char char_1);
char *my_strcpy(char* dst, char* src);
char *my_strncpy(char* dst, char* src, int n);
int my_strlen(char* str);
int my_strcmp(char* str_1, char* str_2);
int zero_padded_char(char* data_field, int dst_len, char* src);
void decimal_to_char(char* data_field, int length, int num);
long my_strtol(char *str, char **endptr, int base);
int my_is_space(int c);
int my_is_digit(int c);
int my_is_alpha(int c);
int my_to_downcase(int c);
void free_array(char** array);

