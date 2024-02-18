#include "read_input.h"
#include "error_codes.h"

/**
 * Reads all characters from a file 'filename' and saves input in input
 * @param input A char** to be filled with the input (should be address of char* [&input])
 * @return Returns whether or not reading the input was successful
 */
int read_file(char** input, char filename[])
{
        FILE *file;
        int character;
        int i = 0;
        file = fopen(filename, "r");

        *input = (char*) malloc(5);

        if (file == NULL) {
                return FILE_NOT_FOUND;
        }

        while ((character = fgetc(file)) != EOF) {
                ++i;
                (*input) = realloc(*input, i + 1);
                (*input)[i - 1] = character;
        }
        (*input)[i] = '\0';

        fclose(file);
        return READ_SUCCESS;
}

/**
 * Reads all characters from input until the newline-character and saves them in input
 * @param input A char** to be filled with the input (should be address of char* [&input])
 * @return Returns whether or not line was successfully read
 */
int read_line(char** input)
{
        int i = 0;
        char c;
        (*input) = (char*) malloc(5);
        while ((c = getchar()) != '\n') {
                ++i;
                (*input) = realloc(*input, i + 1);
                if ((*input) == NULL) {
                        return MALLOC_ERROR;
                }
                (*input)[i - 1] = c;
        }
        (*input)[i] = '\0';
        return READ_SUCCESS;
}
