#ifndef OPTICS_H_INCLUDED
#define OPTICS_H_INCLUDED

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define MACOS 1
#define WINDOWS 2
#define LINUX 3

/*Cipher Methods*/
#define RFC 41 /*Rail-fence cipher*/
#define SCC 42 /*Safe caesar cipher*/
#define CCC 43 /*Compatible caesar cipher*/
#define VC 44 /*Vigenère cipher*/
#define PC 45 /*Polybius cipher*/
#define FA 46 /*Frequency analysis*/
#define SE 47 /*Shift e*/

#define ENCRYPT 51
#define DECRYPT 52

/*Input/Output choice*/
#define TXT_FILE 61
#define TERMINAL 62

#define UNKNOWN 40 /*Status for `clear_running`*/
#define KEY_UNKNOWN "0" /*Status for `clear_running` key*/

#define MAXIMUM_TEXT_WIDTH 64 /*80 terminal width minus 8 spaces to the left and 8 spaces to the right of text*/
#define MAX_SIZE 9 /*4 digits for width + space + 3 digits for height + '\0'*/
#define MIN_TERMINAL_HEIGHT_FRE_LEGEND 33
#define MIN_TERMINAL_HEIGHT 26
#define MIN_TERMINAL_WIDTH 80
#define MAX_WIDTH 5
#define MAX_HEIGHT 4

/*Color codes*/
#define RED "\x1b[31m"
#define BLUE "\x1b[34m"
#define BRIGHT_CYAN "\x1b[96m"
#define YELLOW "\x1B[33m"
#define MAGENTA "\x1b[35m"
#define BRIGHT_WHITE "\x1b[97m"
#define BACKGROUND "\033[40m"
#define COLOR_RESET "\x1b[0m"

/*Text attributes*/
#define UNDERLINE "\033[4m"
#define BOLD "\033[1m"
#define SLOW_BLINK "\033[5m"
#define STOP_BLINK "\033[25m"
#define RESET_TXT_ATTRIBUTES "\033[0m"

/*macOS SPECIFIC!!*/
#define CLEAR(void) system("clear")
#define SIZE "stty size"
#define SET_SIZE(void) do { \
        char command[20 + MAX_WIDTH]; \
        snprintf(command, sizeof(command), "printf \"\\033[8;%i;%it\"", MIN_TERMINAL_HEIGHT, MIN_TERMINAL_WIDTH); \
        system(command); \
        } while (0)
#define SET_SIZE_FRE_LEGEND(width) do { \
        char command[20 + MAX_WIDTH]; \
        snprintf(command, sizeof(command), "printf \"\\033[8;%i;%it\"", MIN_TERMINAL_HEIGHT_FRE_LEGEND, width); \
        system(command); \
        } while (0)

void print_intro(void);
void print_outro(void);
void delay(int seconds);
void test_delay(int milliseconds);
void print_intro_picture(int tabs, int total_tabs);
void print_tabs(int tabs);
void print_load_progress(double percentage, double total);
void print_name(int background);
int clear_running(int method, int direction, int input, char key[]);
void print_centered_text(char text[]);
void print_left_aligned(char text[]);
int get_terminal_width(void);
int get_terminal_height(void);
int print_encrypt_animation(char input[], char output[], int method, int direction, int input_type, char key[]);
int print_char(char **input, char **output, int i, int k, int input_line_count, int method, int direction, int input_type, char key[]);
int add_line_breaks(char* text, char** new_text, int max_line_len);

#endif
