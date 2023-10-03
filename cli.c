#include "header.h"

// Function to display prompt
void display_prompt(blockchain_t* blockchain)
{
    if (is_synced(blockchain))
    {
        printf("[s%i]>", blockchain->size);
        fflush(stdout);
    }
    else
    {
        printf("[-%i]>", blockchain->size);
        fflush(stdout);
    }
}


// Function to parse command
char** parse_args(char* param_1)
{
    if (strlen(param_1) <= 0) {
        return NULL;
    }

    char separator = ' ';
    int i = 0; int j = 0; int k = 0;
    int len = strlen(param_1);
    char** buffer = malloc(sizeof(char*) * 4);
    buffer[0] = malloc(sizeof(char) * 10);
    buffer[1] = malloc(sizeof(char) * 10);
    buffer[2] = malloc(sizeof(char) * 10);
    buffer[3] = malloc(sizeof(char) * 10);

    while (k < 4 && i <= len) {
        while (i < len) {
            if (param_1[i] != separator) {
                break;
            }
            i++;
        }

        while (i < len && j < 10) {
            if (param_1[i] == separator) {
                break;
            }
            if (param_1[i] == '\n') {
                break;
            }
            buffer[k][j] = param_1[i];
            j++; i++;
        }
        buffer[k][j] = '\0';
        k++; j = 0;
    }
    return buffer;
}

// Function to translate args to command
int get_command(char** argv) 
{
    if (strcmp(argv[0], "add") == 0 && strcmp(argv[1], "node") == 0) {
        return 1;
    } else if (strcmp(argv[0], "rm") == 0 && strcmp(argv[1], "node") == 0) {
        if (argv[2][0] == '*') {
            return 2;
        } else {
            return 3;
        }
    } else if (strcmp(argv[0], "add") == 0 && strcmp(argv[1], "block") == 0) {
        if (argv[3][0] == '*') {
            return 4;
        } else {
            return 5;
        }
    } else if (strcmp(argv[0], "rm") == 0 && strcmp(argv[1], "block") == 0) {
        if (argv[3][0] == '*') {
            return 6;
        } else {
            return 7;
        }
    } else if (strcmp(argv[0], "ls") == 0 && strcmp(argv[1], "-l") == 0) {
        return 8;
    } else if (strcmp(argv[0], "ls") == 0) {
        return 9;
    } else if (strcmp(argv[0], "sync") == 0) {
        return 10;
    } else if (strcmp(argv[0], "quit") == 0) {
        return 11;
    } else {
        return 0;
    }
}

// Convert args into bid and nid
int convert_args(char** args, int command, char** bid)
{
    long nid = 0;

    if (command == 1 || command == 3) {
        nid = my_strtol(args[2], NULL, 10); 
    }
    if (command == 4 || command == 6) {
        *bid = malloc(sizeof(char) * 10);
        my_strcpy(*bid, args[2]);
    }
    if (command == 5 || command == 7) {
        *bid = malloc(sizeof(char) * 10);
        if (args[3][0] == '\0') {
            nid = 0;
        }
        nid = my_strtol(args[3], NULL, 10);
        my_strcpy(*bid, args[2]);
    }

    int num_id = (int)nid;

    return num_id;
}

