#include "header.h"


char *my_readline(int fd, read_line_t **buf) 
{
    int total_bytes = 0;

    /* If read_line_t has been initiated, check for leftover */
    if (*buf != NULL) {
        if ((*buf)->leftover != NULL) // If leftover, reallocate newline into buf->storage and return
        {
            total_bytes = my_strlen((*buf)->leftover);
            copy_first_line(&(*buf)->storage, &(*buf)->leftover, (*buf)->leftover, total_bytes);
            return (*buf)->storage;
        } else // If no leftover, return NULL
        {
            (*buf)->storage = (char*)malloc(sizeof(char) * (READLINE_READ_SIZE + 1));
        }
    }

    /* Initiate read_line_t */
    if (*buf == NULL) {
        *buf = (read_line_t*)malloc(sizeof(read_line_t) + 1);
        (*buf)->storage = (char*)malloc(sizeof(char) * (READLINE_READ_SIZE + 1));
    }

    /* If memory is not allocated, exit program */
    if ((*buf)->storage == NULL) {
        return NULL;
    }

    int bytes = 1;

    /* read READLINE_READ_SIZE into buf->storage until '\n' or end-of-file is found */
    while (bytes > 0) {
        bytes = read(fd, (*buf)->storage + total_bytes, READLINE_READ_SIZE);
        total_bytes += bytes;

        // Error reading stream
        if (bytes == -1) {
            return NULL;
        }

        // End of file
        if (bytes == 0) {
            break;
        }

        // Null-terminate
        (*buf)->storage[total_bytes] = '\0';

        // Check for echo
        int echo_toggle = is_echo((*buf)->storage, bytes);
        if (echo_toggle) {
            if ((*buf)->storage[total_bytes - 1] == '\n') {
                (*buf)->storage[total_bytes - 1] = '\0';
            }
            convert_newline_char((*buf)->storage, bytes);
        }

        // Copy first line onlu into buf->storage + return
        copy_first_line(&(*buf)->storage, &(*buf)->leftover, (*buf)->storage, total_bytes);
        return (*buf)->storage;
    }

    /* If end of file AND all bytes have been returned */
    if (bytes == 0 && total_bytes == 0) {
        init_my_readline(buf);
        return NULL;
    }

    /* Required for the first conditional in function */
    (*buf)->leftover = NULL;

    return (*buf)->storage;

}

int copy_first_line(char** first_line, char** leftover, char* src, int src_len) 
{
    int index = my_strchr_index(src, '\n');

    // If no '\n' found return NULL
    if (index == 0) {
        return 0;
    }

    // If there is only one line in string
    if (index == src_len) {
        *first_line = malloc(sizeof(char) * src_len + 1);
        my_strcpy(*first_line, src);
        *leftover = NULL;
        return index;
    }

    // Allocate memory
    char *temp_buf_1 = (char*)malloc(sizeof(char) * (src_len + 1));
    char *temp_buf_2 = (char*)malloc(sizeof(char) * (src_len + 1));
    memset(temp_buf_1, 0, src_len + 1);
    memset(temp_buf_2, 0, src_len + 1);

    // Store next line in temp_buf_1
    my_strncpy(temp_buf_1, src, index);

    // Store leftover in temp_buf_2
    my_strcpy(temp_buf_2, src + index);

    // Free source string and allocate memory for new strings
    free(src);
    int temp_buf_1_len = my_strlen(temp_buf_1);
    int temp_buf_2_len = my_strlen(temp_buf_2);

    // Copy buffers into new strings
    *first_line = malloc(sizeof(char) * temp_buf_1_len + 1);
    my_strcpy(*first_line, temp_buf_1);
    *leftover = malloc(sizeof(char) * temp_buf_2_len + 1);
    my_strcpy(*leftover, temp_buf_2);

    // Free buffers
    free(temp_buf_1);
    free(temp_buf_2);

    return temp_buf_1_len;
}

int is_echo(char* string, int bytes) 
{
    for (int i = 0; i < bytes - 1; i++) {
        if (string[i] == '\\' && string[i + 1] == 'n') {
            return 1;
        } 
    } 

    return 0;
}

int convert_newline_char(char* string, int bytes) 
{
    int j = 0;
    int k = 0;

    for (int i = 0; i < bytes - 1; i++) {
        if (string[i] == '\\' && string[i + 1] == 'n') {
            string[i] = '\n';
            j = i + 1;
            while (j < bytes - 1) {
                string[j] = string[j + 1];
                j += 1;
            }
            k = i;
        } 
    } 

    return k;
}

void init_my_readline(read_line_t **buf)
{
    free((*buf)->storage);
    free(*buf);
    *buf = NULL;
}
