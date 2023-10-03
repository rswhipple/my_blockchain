#include "header.h"

char *my_realloc_str(char* ptr, size_t size) 
{
    char *buf = (char*)malloc(sizeof(char) * size);
    buf = my_strcpy(buf, ptr);
    free(ptr);

    return buf;
}

char* my_strchr(char* str_1, char char_1)
{
    int i;

    for (i = 0; i <= my_strlen(str_1); i++) {
        if (str_1[i] == char_1) {
            return &str_1[i];
        }
    }

    return "";
}

int my_strchr_index(char* str_1, char char_1)
{
    int i;

    for (i = 0; i <= my_strlen(str_1); i++) {
        if (str_1[i] == char_1) {
            return i + 1;
        }
    }

    return 0;
}

char* my_strcpy(char* dst, char* src)
{
    int i;
    int length = my_strlen(src);

    for (i = 0; i < length; i++) {
        dst[i] = src[i]; 
    }

    dst[i] = '\0';

    return dst;
}

char* my_strncpy(char* dst, char* src, int n)
{
    char* original_dst = dst;
    int i;

    for (i = 0; i < n; i++) {
        *dst++ = *src++;
    }

    *--dst = '\0';

    return original_dst;
}


int my_strlen(char* str) 
{
    int i = 0;

    do {
        i += 1;
    } while (str[i] != '\0');

    return i;
}

int my_strcmp(char* str_1, char* str_2)
{
    int i;
    int str_to_int_1 = 0;
    int str_to_int_2 = 0;

    for (i = 0; str_1[i] != '\0'; i++) {
        str_to_int_1 += str_1[i];
    } 

    for (i = 0; str_2[i] != '\0'; i++) {
        str_to_int_2 += str_2[i];
    } 
    
    if (str_to_int_1 == str_to_int_2) {
        return 0;
    } else if (str_to_int_1 > str_to_int_2) {
        return -1;
    } else {
        return 1;
    }

}

int zero_padded_char(char* data_field, int dst_len, char* src) 
{
    int length = strlen(src);
    int i = 0;

    // Copy src to dst
    while (i < length) {
        data_field[i] = src[i];
        i += 1;
    }

    // If src is shorter than dst, pad with NULL
    while (i < dst_len) {
        data_field[i++] = '\0';
    }

    // Return length of src
    return length;
}

void decimal_to_char(char* data_field, int length, int num) 
{
    // length -= 1;
    data_field[--length] = '\0'; // Null-terminate

    // Convert to char
    do {
        data_field[--length] = '0' + (num % 10);
        num /= 10;
    } while (num != 0);

    // If char is shorter than data_field, pad with '0'
    while (length > 0 ) {
        data_field[--length] = '0';
    }
}

long my_strtol(char *str, char **endptr, int base) 
{
    // Skip leading whitespace 
    while (my_is_space(*str)) {
        str += 1;
    }

    // Conversion
    long result = 0;
    while (*str != '\0') {
        int digit;
        if (my_is_digit(*str)) {
            digit = *str - '0';
        } else if (my_is_alpha(*str)) {
            digit = my_to_downcase(*str) - 'a' + 10;
        } else {
            break;  // Invalid character, stop conversion
        }

        if (digit >= base) {
            break;  // Invalid digit for base, stop conversion
        }

        result = result * base + digit;
        str += 1;
    }

    // Update endptr if provided
    if (endptr != NULL) {
        *endptr = (char *)str;
    }

    return result;
}

int my_is_space(int c)
{
    if (c == ' ' || c == '\t' || c == '\n') {
        return 1; 
    } else {
        return 0;
    }
}

int my_is_digit(int c)
{
    if (c >= '0' && c <= '9') {
        return 1; 
    } else {
        return 0;
    }
}

int my_is_alpha(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        return 1; 
    } else {
        return 0;
    }
}

int my_to_downcase(int c)
{
    int output = c;
    if (c >= 'A' && c <= 'Z') {
        output += 32;
    } 

    return output;
}

void free_array(char** array) {
    int i = 0;
    while (i < 4) {
        free(array[i]);
        i++;
    }
    free(array);
}
