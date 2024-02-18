#ifndef READ_INPUT_H_INCLUDED
#define READ_INPUT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define READ_SUCCESS 5
#define WRITE_SUCCESS 6
#define CANCEL 1

#define EXIT 0

int read_file(char** input, char filename[]);
int read_line(char** input);
int print_to_file(char output[], char filename[]);

#endif
