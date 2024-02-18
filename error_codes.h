#ifndef ERROR_CODES_H_INCLUDED
#define ERROR_CODES_H_INCLUDED

#include <stdio.h>

#define SUCCESS 1
#define VALID_INPUT 2
#define VALID_KEY 3

/*general error codes*/
#define INVALID_INPUT (-1)
#define INVALID_KEY (-2)
#define MALLOC_ERROR (-3)
#define EXIT 0

/*caesar specific codes*/
#define NO_KEY (-10)

/*polybius specific codes*/
#define INVALID_ENCRYPTION (-20)

/*frame specific codes*/
#define FILE_NOT_FOUND (-31)
#define TERMINAL_ERROR (-32)

int check_error(int value);
int print_error(int value);

#endif
