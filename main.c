#include "header.h"


int main(void) {
    blockchain_t* blockchain = create_blockchain();

    // Check for backup
    if (is_backup()) {
        open_backup_file(blockchain);
    } 

    // Declare and initiate variables
    int running = 1;
    int fd = 0;
    int nid = 0;
    int command;

    char* bid = NULL;
    char *str = NULL;
    char** args;
    read_line_t *buf = NULL;
    
    display_prompt(blockchain);

    while ((str = my_readline(fd, &buf)) != NULL)
    {
        if (str[0] == '\0' || str[0] == '\n') {
            free(str);
            return EXIT_SUCCESS;
        }

        // Parse args
        args = parse_args(str);
        command = get_command(args);
        nid = convert_args(args, command, &bid); // Convert nid to int, convert bid to variable

        // Free buffers
        free_array(args);
        free(str);

        // Execute command
        running = execute_command(command, blockchain, nid, bid);

        if (running == 0) {
            break;
        }
        
        if (running == -1) {
            return EXIT_FAILURE;
        }

        display_prompt(blockchain);


    }

    return EXIT_SUCCESS;
}
