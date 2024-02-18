#include "optics.h"
#include "error_codes.h"


/**
 * Prints the intro-animation
 */
void print_intro(void)
{
        if (get_terminal_width() < MIN_TERMINAL_WIDTH || get_terminal_height() < MIN_TERMINAL_HEIGHT) {
                SET_SIZE();
        }

        CLEAR();

        printf("\n\n");
        printf(MAGENTA);
        print_intro_picture(1, 6);

        delay(1);
        CLEAR();

        printf("\n\n");
        printf(BLUE);
        print_intro_picture(2, 6);

        delay(1);
        CLEAR();

        printf("\n\n");
        printf(RED);
        print_intro_picture(3, 6);

        delay(1);
        CLEAR();

        printf("\n\n");
        printf(BRIGHT_CYAN);
        print_intro_picture(4, 6);

        delay(1);
        CLEAR();

        printf("\n\n");
        printf(YELLOW);
        print_intro_picture(5, 6);

        delay(1);
        CLEAR();

        printf("\n\n");
        printf(BRIGHT_WHITE);
        print_intro_picture(6, 6);

        delay(1);
        CLEAR();
}

/**
 * Prints program name when exited
 */
void print_outro(void)
{
        CLEAR();

        printf("\n\n");
        printf(MAGENTA);
        print_name(1);
        delay(2);
        CLEAR();
}

void delay(int seconds)
{
        time_t start_time, current_time;

        time(&start_time);
        do {
                time(&current_time);
        } while ((current_time - start_time) < seconds);
}

/**
 * Prints the single intro picture (not the animation)
 * @param tabs Number of tabs to be printed (increases per picture outputted)
 * @param total_tabs Number of tabs used in last picture
 */
void print_intro_picture(int tabs, int total_tabs)
{
        if (get_terminal_height() < MIN_TERMINAL_HEIGHT || get_terminal_width() < MIN_TERMINAL_WIDTH) {
                SET_SIZE();
        }
        printf("\n\n\n\n");
        print_tabs(tabs);
        printf("███      ███    ██      ██\n");
        print_tabs(tabs);
        printf("██ ██    ██ ██   ██    ██\n");
        print_tabs(tabs);
        printf("██  ██   ██  ██   ██  ██\n");
        print_tabs(tabs);
        printf("██   ██  ██ ██     ████\n");
        print_tabs(tabs);
        printf("██  ██   ███        ██\n");
        print_tabs(tabs);
        printf("██ ██    ██ ██      ██\n");
        print_tabs(tabs);
        printf("███      ██  ██     ██\n");
        print_tabs(tabs);
        printf("      ");
        printf("CRYPTOGRAPHY\n\n\n\n");
        print_tabs(tabs);
        printf("A cryptography program by\n");
        print_tabs(tabs + 1);
        printf("Daniel Carp\n");
        print_tabs(tabs);
        printf("      Raphael Wagner\n");
        print_tabs(tabs);
        printf("    Yannick Sodonougbo\n");
        print_tabs(tabs);
        printf("      2024.1 (macOS)\n");
        printf("\n\n");
        printf(COLOR_RESET);
        print_load_progress(tabs, total_tabs);
        printf("\n\n");
}

void print_tabs(int tabs)
{
        int i;
        for (i = 0; i < tabs; ++i) {
                printf("\t");
        }
}

/**
 * Prints the load-progress bar
 * @param percentage percentage of intro screen animation completed
 * @param total
 */
void print_load_progress(double percentage, double total)
{
        int i;
        int completion = (int) (percentage / total * 10);
        if (get_terminal_width() < MIN_TERMINAL_WIDTH || get_terminal_height() < MIN_TERMINAL_HEIGHT) {
                SET_SIZE();
        }
        for (i = 0; i < 10; ++i) {
                if (i <= completion) {
                        printf("████████");
                } else {
                        printf("________");
                }
        }
        printf("\n\t\t\t\t    WELCOME"SLOW_BLINK"..."RESET_TXT_ATTRIBUTES);
}

/**
 * prints the name of the program
 * @param background zero if no background should be printed, else not zero
 */
void print_name(int background)
{
        if (background) {
                printf("\t\t\t\t"BOLD BRIGHT_WHITE BACKGROUND"DRY"RESET_TXT_ATTRIBUTES BRIGHT_WHITE BACKGROUND"CRYPTOGRAPHY\n");
        } else {
                printf("\t\t\t\t"BOLD"DRY"RESET_TXT_ATTRIBUTES"CRYPTOGRAPHY\n\n\n");
        }
}

/**
 * Clears the terminal and immediately prints all important information in an aesthetic way
 * @param method method used for en- or decryption
 * @param direction can be decryption or encryption
 * @param input kind of input (via terminal or via text-file)
 * @param key key used for en- or decryption
 * @return Returns whether or not clearing was successful
 */
int clear_running(int method, int direction, int input, char key[])
{
        char* key_output = NULL;
        if (get_terminal_width() < MIN_TERMINAL_WIDTH || get_terminal_height() < MIN_TERMINAL_HEIGHT) {
                SET_SIZE();
        }
        CLEAR();
        print_name(0);
        switch (method) {
                case RFC:
                        print_centered_text("GARTENZAUN-METHODE");
                        break;
                case SCC:
                        print_centered_text("CÄSAR-CHIFFRE (höhere Sicherheit)");
                        break;
                case CCC:
                        print_centered_text("CÄSAR-CHIFFRE (höhere Kompatibilität)");
                        break;
                case VC:
                        print_centered_text("VIGENÈRE-CHIFFRE");
                        break;
                case PC:
                        print_centered_text("POLYBIOS-CHIFFRE");
                        break;
                case FA:
                        print_centered_text("HÄUFIGKEITSANALYSE");
                        direction = DECRYPT;
                        break;
                case SE:
                        print_centered_text("CÄSAR-CHIFFRE (höhere Kompatibilität)");
                        direction = DECRYPT;
                        break;
        }
        switch (direction) {
                case ENCRYPT:
                        print_centered_text("VERSCHLÜSSELUNG");
                        break;
                case DECRYPT:
                        print_centered_text("ENTSCHLÜSSELUNG");
                        break;
        }
        switch (input) {
                case TXT_FILE:
                        print_centered_text("EINGABEART: Textdatei");
                        break;
                case TERMINAL:
                        print_centered_text("EINGABEART: Kommandozeile");
                        break;
        }
        if (strcmp(key, KEY_UNKNOWN) != 0) {
                key_output = malloc((13 + strlen(key)) * sizeof(char));
                if (key_output == NULL) {
                        return MALLOC_ERROR;
                }
                strcpy(key_output, "SCHLÜSSEL: ");
                strncat(key_output, key, strlen(key));
                print_centered_text(key_output);
                free(key_output);
        }
        printf("\n");
        return SUCCESS;
}

void print_centered_text(char text[])
{
        int total_width = 80;
        int text_width = strlen(text);
        int i, j, part_width, padding;

        if (text_width >= total_width - 16) {
                i = 0;
                while (i < text_width) {
                        part_width = (text_width - i >= total_width - 16) ? (total_width - 16) : (text_width - i);

                        j = part_width - 1;
                        while (j >= 0 && text[i + j] != ' ' && text[i + j] != '\n') {
                                j--;
                        }

                        if (j >= 0 && part_width - j <= 16) {
                                part_width -= (part_width - j);
                        }

                        padding = (total_width - part_width) / 2;

                        for (j = 0; j < padding; ++j) {
                                printf(" ");
                        }

                        for (j = 0; j < part_width; ++j) {
                                printf("%c", text[i + j]);
                        }

                        printf("\t\n");

                        i += part_width;
                        while (i < text_width && (isspace(text[i]) || text[i] == '\n')) {
                                i++;
                        }
                }
        } else {
                padding = (total_width - text_width) / 2;

                for (i = 0; i < padding; ++i) {
                        printf(" ");
                }

                printf("%s", text);

                for (i = 0; i < padding; ++i) {
                        printf(" ");
                }

                printf("\n");
        }
}

void print_left_aligned(char text[])
{
        int i, j;
        int width = 0;
        int word_width;
        printf("\t");
        for (i = 0; text[i] != '\0'; ++i) {
                word_width = 0;
                for (j = i; text[j] != ' ' && text[j] != '\0' && text[j] != '\n'; ++j) {
                        ++word_width;
                }
                if (text[i] == '\n') {
                        printf("\n\t");
                        width = 0;
                } else if (word_width > MAXIMUM_TEXT_WIDTH) {
                        if (width < MAXIMUM_TEXT_WIDTH) {
                                printf("%c", text[i]);
                                ++width;
                        } else {
                                printf("\n\t%c", text[i]);
                                width = 0;
                        }
                } else if (word_width + width >= MAXIMUM_TEXT_WIDTH) {
                        printf("\n\t%c", text[i]);
                        width = 0;
                } else if (word_width + width < MAXIMUM_TEXT_WIDTH) {
                        printf("%c", text[i]);
                        ++width;
                }
        }
}

int get_terminal_width(void)
{
        FILE* terminal;
        char size[MAX_SIZE] = {0};
        int width;
        int height;

        terminal = popen(SIZE, "r");

        if (terminal != NULL) {
                if (fgets(size, MAX_SIZE, terminal) != NULL) {
                        if (sscanf(size, "%i%i", &height, &width) == 2) {
                                pclose(terminal);
                                return width;
                        }
                }
        }

        return TERMINAL_ERROR;
}

int get_terminal_height(void)
{
        FILE* terminal;
        char size[MAX_SIZE] = {0};
        int width;
        int height;

        terminal = popen(SIZE, "r");

        if (terminal != NULL) {
                if(fgets(size, MAX_SIZE, terminal) != NULL) {
                        if (sscanf(size, "%i%i", &height, &width) == 2) {
                                pclose(terminal);
                                return height;
                        }
                }
                pclose(terminal);
        }

        return TERMINAL_ERROR;
}

int print_encrypt_animation(char input[], char output[], int method, int direction, int input_type, char key[])
{
        int i, k, j, polybios_input_specials, polybios_output_specials, output_len, input_len, input_spaces, output_spaces, spaces_used, specials_used, line_counter, input_line_count, output_line_count;
        char **input_lines = NULL;
        char **output_lines = NULL;
        char **new_input_lines= NULL;
        char **new_output_lines = NULL;
        input_line_count = 1;
        output_line_count = 1;
        output_len = strlen(output);
        input_len = strlen(input);

        /* Absätze zählen */
        for (i = 0; i < input_len; ++i) {
                if (input[i] == '\n') {
                        ++input_line_count;
                }
        }
        if (input[i - 1] == '\n') {
                --input_line_count;
                input[i - 1] = '\0';
                --input_len;
        }
        for (i = 0; i < output_len; ++i) {
                if (output[i] == '\n') {
                        ++output_line_count;
                }
        }
        if (output[i - 1] == '\n') {
                output[i - 1] = '\0';
                --output_len;
        }
        /* Reservieren von Speicher für input_lines und output_lines */
        input_lines = malloc(input_line_count * sizeof(char*));
        for (i = 0; i < input_line_count; ++i) {
                input_lines[i] = malloc(sizeof(char));
                if (input_lines[i] == NULL) {
                        for (k = 0; k < i; ++k) {
                                free(input_lines[k]);
                        }
                        free(input_lines);
                        return MALLOC_ERROR;
                }
        }
        output_lines = malloc(output_line_count * sizeof(char*));
        for (i = 0; i < output_line_count; ++i) {
                output_lines[i] = malloc(sizeof(char));
                if (output_lines[i] == NULL) {
                        for (k = 0; k < i; ++k) {
                                free(output_lines[k]);
                        }

                        free(output_lines);
                        return MALLOC_ERROR;
                }
        }

        /* "Befüllen" der Matrizen für die input- und output-Zeilen */
        /* (input & output werden jeweils in einer Matrix zeilenweise gespeichert) */
        line_counter = 0;
        k = 0;
        for (i = 0; i <= input_len; ++i) {
                if (input[i] == '\n' || input[i] == '\0') {
                        j = 0;
                        while ((input[k] != '\n') && (input[k] != '\0')) {
                                input_lines[line_counter] = realloc(input_lines[line_counter], (j + 2) * sizeof(char));
                                if (input_lines[line_counter] == NULL) {
                                        return MALLOC_ERROR;
                                }
                                input_lines[line_counter][j] = input[k];
                                ++j;
                                ++k;
                        }
                        input_lines[line_counter][j] = '\0';
                        ++line_counter;
                        k = i + 1;
                }
        }
        line_counter = 0;
        k = 0;
        for (i = 0; i <= output_len; ++i) {
                if (output[i] == '\n' || output[i] == '\0') {
                        j = 0;
                        while ((output[k] != '\n') && (output[k] != '\0')) {
                                output_lines[line_counter] = realloc(output_lines[line_counter], (j + 2) * sizeof(char));
                                if (output_lines[line_counter] == NULL) {
                                        return MALLOC_ERROR;
                                }
                                output_lines[line_counter][j] = output[k];
                                ++j;
                                ++k;
                        }
                        output_lines[line_counter][j] = '\0';
                        ++line_counter;
                        k = i + 1;
                }
        }
        /* Reservieren von Speicher für new_input_lines und new_output_lines */
        new_input_lines = malloc(input_line_count * sizeof(char*));
        for (i = 0; i < input_line_count; ++i) {
                new_input_lines[i] = malloc(sizeof(char));
                if (new_input_lines[i] == NULL) {
                        for (k = 0; k < i; ++k) {
                                free(new_input_lines[k]);
                        }
                        free(new_input_lines);
                        return MALLOC_ERROR;
                }
        }
        new_output_lines = malloc(output_line_count * sizeof(char*));
        for (i = 0; i < output_line_count; ++i) {
                new_output_lines[i] = malloc(sizeof(char));
                if (new_output_lines[i] == NULL) {
                        for (k = 0; k < i; ++k) {
                                free(new_output_lines[k]);
                        }
                        free(new_output_lines);
                        return MALLOC_ERROR;
                }
        }
        for (i = 0; i < input_line_count; ++i) {
                input_len = strlen(input_lines[i]);
                output_len = strlen(output_lines[i]);
                input_spaces = 0;
                for (k = 0; k < input_len; ++k) {
                        if (input_lines[i][k] == ' ') {
                                ++input_spaces;
                        }
                }
                output_spaces = 0;
                for (k = 0; k < output_len; ++k) {
                        if (output_lines[i][k] == ' ') {
                                ++output_spaces;
                        }
                }

                if (method == PC) {
                        polybios_input_specials = 0;
                        if (output_len > input_len) {
                                for (k = 0; k < input_len; ++k) {
                                        if ((input_lines[i][k] < 'A') || (input_lines[i][k] > 'Z')) {
                                                ++polybios_input_specials;
                                        }
                                }
                        } else {
                                for (k = 0; k < input_len; ++k) {
                                        if ((input_lines[i][k] < '1') || (input_lines[i][k] > '9')) {
                                                ++polybios_input_specials;
                                        }
                                }
                        }
                        polybios_output_specials = 0;
                        if (input_len > output_len) {
                                for (k = 0; k < output_len; ++k) {
                                        if ((output_lines[i][k] < 'A') || (output_lines[i][k]) > 'Z') {
                                                ++polybios_output_specials;
                                        }
                                }
                        } else {
                                for (k = 0; k < output_len; ++k) {
                                        if ((output_lines[i][k] < '0') || (output_lines[i][k]) > '9') {
                                                ++polybios_output_specials;
                                        }
                                }
                        }
                        if ((output_len - output_spaces) == ((input_len - input_spaces) * 2)) {

                                /* Die Output-Zeile ist doppelt so lange wie die Input-Zeile */
                                new_input_lines[i] = realloc(new_input_lines[i], (output_len + 1) * sizeof(char));
                                spaces_used = 0;
                                for (k = 0; k < input_len; ++k) {
                                        if (input_lines[i][k] == ' ') {
                                                new_input_lines[i][(2 * k) - spaces_used] = input_lines[i][k];
                                                ++spaces_used;
                                        } else {
                                                new_input_lines[i][(2 * k) - spaces_used] = input_lines[i][k];
                                                new_input_lines[i][(2 * k + 1) - spaces_used] = ' ';
                                        }
                                }
                                new_input_lines[i][(2 * k) - spaces_used] = '\0';
                                /* output_lines wird unverändert nach new_output_lines kopiert */
                                new_output_lines[i] = realloc(new_output_lines[i], ((output_len + 1) * sizeof(char)));
                                for (k = 0; k < output_len; ++k) {
                                        new_output_lines[i][k] = output_lines[i][k];
                                }
                                new_output_lines[i][k] = '\0';
                        } else if ((input_len - input_spaces) == ((output_len - output_spaces) * 2)) {
                                /* Die Input-Zeile ist doppelt so lange wie die Output-Zeile */
                                new_output_lines[i] = realloc(new_output_lines[i], (input_len + 1) * sizeof(char));
                                spaces_used = 0;
                                for (k = 0; k < output_len; ++k) {
                                        if (output_lines[i][k] == ' ') {
                                                new_output_lines[i][(2 * k) - spaces_used] = output_lines[i][k];
                                                ++spaces_used;
                                        } else {
                                                new_output_lines[i][(2 * k) - spaces_used] = output_lines[i][k];
                                                new_output_lines[i][(2 * k + 1) - spaces_used] = ' ';
                                        }
                                }
                                new_output_lines[i][(2 * k) - spaces_used] = '\0';

                                /* input_lines wird unverändert nach new_input_lines kopiert */
                                new_input_lines[i] = realloc(new_input_lines[i], ((input_len + 1) * sizeof(char)));
                                for (k = 0; k < input_len; ++k) {
                                        new_input_lines[i][k] = input_lines[i][k];
                                }
                                new_input_lines[i][k] = '\0';
                        } else if ((output_len - polybios_output_specials) == ((input_len - polybios_input_specials) * 2)) {

                                /* Die Output-Zeile ist doppelt so lange wie die Input-Zeile */
                                new_input_lines[i] = realloc(new_input_lines[i], (output_len + 1) * sizeof(char));
                                specials_used = 0;
                                for (k = 0; k < input_len; ++k) {
                                        if ((input_lines[i][k] < 'A') || (input_lines[i][k] > 'Z')) {
                                                new_input_lines[i][(2 * k) - specials_used] = input_lines[i][k];
                                                ++specials_used;
                                        } else {
                                                new_input_lines[i][(2 * k) - specials_used] = input_lines[i][k];
                                                new_input_lines[i][(2 * k) + 1 - specials_used] = ' ';
                                        }
                                }
                                new_input_lines[i][(2 * k) - specials_used] = '\0';
                                /* output_lines wird unverändert nach new_output_lines kopiert */
                                new_output_lines[i] = realloc(new_output_lines[i], ((output_len + 1) * sizeof(char)));
                                for (k = 0; k < output_len; ++k) {
                                        new_output_lines[i][k] = output_lines[i][k];
                                }
                                new_output_lines[i][k] = '\0';
                        } else if ((input_len - polybios_input_specials) == ((output_len - polybios_output_specials) * 2)) {
                                /* Die input-Zeile ist doppelt so lange wie die output-Zeile */
                                new_output_lines[i] = realloc(new_output_lines[i], (input_len + 1) * sizeof(char));
                                specials_used = 0;
                                for (k = 0; k < output_len; ++k) {
                                        if ((output_lines[i][k] < 'A') || (output_lines[i][k] > 'Z')) {
                                                new_output_lines[i][(2 * k) - specials_used] = output_lines[i][k];
                                                ++specials_used;
                                        } else {
                                                new_output_lines[i][(2 * k) - specials_used] = output_lines[i][k];
                                                new_output_lines[i][(2 * k) + 1 - specials_used] = ' ';
                                        }
                                }
                                new_output_lines[i][(2 * k) - specials_used] = '\0';
                                /* input_lines wird unverändert nach new_input_lines kopiert */
                                new_input_lines[i] = realloc(new_input_lines[i], ((input_len + 1) * sizeof(char)));
                                for (k = 0; k < input_len; ++k) {
                                        new_input_lines[i][k] = input_lines[i][k];
                                }
                                new_input_lines[i][k] = '\0';
                        } else if (output_len > input_len) {
                                /* Die Output-Zeile ist länger als die Input-Zeile */

                                new_input_lines[i] = realloc(new_input_lines[i], ((output_len + 1) * sizeof(char)));
                                for (k = 0; k < output_len; ++k) {
                                        if (k < input_len) {
                                                /* input_lines wird unverändert nach new_input_lines kopiert */
                                                new_input_lines[i][k] = input_lines[i][k];
                                        } else {
                                                /* Restlicher Platz wird mit Leerzeichen aufgefüllt */
                                                new_input_lines[i][k] = ' ';
                                        }

                                }
                                new_input_lines[i][k] = '\0';
                                /* output_lines wird unverändert nach new_output_lines kopiert */
                                new_output_lines[i] = realloc(new_output_lines[i], ((output_len + 1) * sizeof(char)));
                                for (k = 0; k < output_len; ++k) {
                                        new_output_lines[i][k] = output_lines[i][k];
                                }
                                new_output_lines[i][k] = '\0';
                        } else if (input_len > output_len) {
                                /* Die Input-Zeile ist länger als die Output-Zeile */

                                new_output_lines[i] = realloc(new_output_lines[i], ((input_len + 1) * sizeof(char)));
                                for (k = 0; k < input_len; ++k) {
                                        if (k < output_len) {
                                                /* output_lines wird unverändert nach new_output_lines kopiert */
                                                new_output_lines[i][k] = output_lines[i][k];
                                        } else {
                                                /* Restlicher Platz wird mit Leerzeichen aufgefüllt */
                                                new_output_lines[i][k] = ' ';
                                        }

                                }
                                new_output_lines[i][k] = '\0';
                                /* input_lines wird unverändert nach new_input_lines kopiert */
                                new_input_lines[i] = realloc(new_input_lines[i], ((input_len + 1) * sizeof(char)));
                                for (k = 0; k < input_len; ++k) {
                                        new_input_lines[i][k] = input_lines[i][k];
                                }
                                new_input_lines[i][k] = '\0';
                        } else {
                                /* Die Input- und die Output-Zeile sind gleichlang */
                                /* input_lines wird unverändert nach new_input_lines kopiert */
                                new_input_lines[i] = realloc(new_input_lines[i], ((input_len + 1) * sizeof(char)));
                                for (k = 0; k < input_len; ++k) {
                                        new_input_lines[i][k] = input_lines[i][k];
                                }
                                new_input_lines[i][k] = '\0';

                                /* output_lines wird unverändert nach new_output_lines kopiert */
                                new_output_lines[i] = realloc(new_output_lines[i], ((output_len + 1) * sizeof(char)));
                                for (k = 0; k < output_len; ++k) {
                                        new_output_lines[i][k] = output_lines[i][k];
                                }
                                new_output_lines[i][k] = '\0';
                        }
                } else {
                        if ((output_len - output_spaces) == ((input_len - input_spaces) * 2)) {
                                /* Die Output-Zeile ist doppelt so lange wie die Input-Zeile */
                                new_input_lines[i] = realloc(new_input_lines[i], (output_len + 1) * sizeof(char));
                                spaces_used = 0;
                                for (k = 0; k < input_len; ++k) {
                                        if (input_lines[i][k] == ' ') {
                                                new_input_lines[i][(2 * k) - spaces_used] = input_lines[i][k];
                                                ++spaces_used;
                                        } else {
                                                new_input_lines[i][(2 * k) - spaces_used] = input_lines[i][k];
                                                new_input_lines[i][(2 * k + 1) - spaces_used] = ' ';
                                        }
                                }
                                new_input_lines[i][(2 * k) - spaces_used] = '\0';
                                /* output_lines wird unverändert nach new_output_lines kopiert */
                                new_output_lines[i] = realloc(new_output_lines[i], ((output_len + 1) * sizeof(char)));
                                for (k = 0; k < output_len; ++k) {
                                        new_output_lines[i][k] = output_lines[i][k];
                                }
                                new_output_lines[i][k] = '\0';
                        } else if ((input_len - input_spaces) == ((output_len - output_spaces) * 2)) {
                                /* Die Input-Zeile ist doppelt so lange wie die Output-Zeile */
                                new_output_lines[i] = realloc(new_output_lines[i], (input_len + 1) * sizeof(char));
                                spaces_used = 0;
                                for (k = 0; k < output_len; ++k) {
                                        if (output_lines[i][k] == ' ') {
                                                new_output_lines[i][(2 * k) - spaces_used] = output_lines[i][k];
                                                ++spaces_used;
                                        } else {
                                                new_output_lines[i][(2 * k) - spaces_used] = output_lines[i][k];
                                                new_output_lines[i][(2 * k + 1) - spaces_used] = ' ';
                                        }
                                }
                                new_output_lines[i][(2 * k) - spaces_used] = '\0';

                                /* input_lines wird unverändert nach new_input_lines kopiert */
                                new_input_lines[i] = realloc(new_input_lines[i], ((input_len + 1) * sizeof(char)));
                                for (k = 0; k < input_len; ++k) {
                                        new_input_lines[i][k] = input_lines[i][k];
                                }
                                new_input_lines[i][k] = '\0';
                        } else if (output_len > input_len) {
                                /* Die Output-Zeile ist länger als die Input-Zeile */

                                new_input_lines[i] = realloc(new_input_lines[i], ((output_len + 1) * sizeof(char)));
                                for (k = 0; k < output_len; ++k) {
                                        if (k < input_len) {
                                                /* input_lines wird unverändert nach new_input_lines kopiert */
                                                new_input_lines[i][k] = input_lines[i][k];
                                        } else {
                                                /* Restlicher Platz wird mit Leerzeichen aufgefüllt */
                                                new_input_lines[i][k] = ' ';
                                        }

                                }
                                new_input_lines[i][k] = '\0';

                                /* output_lines wird unverändert nach new_output_lines kopiert */
                                new_output_lines[i] = realloc(new_output_lines[i], ((output_len + 1) * sizeof(char)));
                                for (k = 0; k < output_len; ++k) {
                                        new_output_lines[i][k] = output_lines[i][k];
                                }
                                new_output_lines[i][k] = '\0';
                        } else if (input_len > output_len) {
                                /* Die Input-Zeile ist länger als die Output-Zeile */

                                new_output_lines[i] = realloc(new_output_lines[i], ((input_len + 1) * sizeof(char)));
                                for (k = 0; k < input_len; ++k) {
                                        if (k < output_len) {
                                                /* output_lines wird unverändert nach new_output_lines kopiert */
                                                new_output_lines[i][k] = output_lines[i][k];
                                        } else {
                                                /* Restlicher Platz wird mit Leerzeichen aufgefüllt */
                                                new_output_lines[i][k] = ' ';
                                        }

                                }
                                new_output_lines[i][k] = '\0';
                                /* input_lines wird unverändert nach new_input_lines kopiert */
                                new_input_lines[i] = realloc(new_input_lines[i], ((input_len + 1) * sizeof(char)));
                                for (k = 0; k < input_len; ++k) {
                                        new_input_lines[i][k] = input_lines[i][k];
                                }
                                new_input_lines[i][k] = '\0';
                        } else {
                                /* Die Input- und die Output-Zeile sind gleichlang */
                                /* input_lines wird unverändert nach new_input_lines kopiert */
                                new_input_lines[i] = realloc(new_input_lines[i], ((input_len + 1) * sizeof(char)));
                                for (k = 0; k < input_len; ++k) {
                                        new_input_lines[i][k] = input_lines[i][k];
                                }
                                new_input_lines[i][k] = '\0';

                                /* output_lines wird unverändert nach new_output_lines kopiert */
                                new_output_lines[i] = realloc(new_output_lines[i], ((output_len + 1) * sizeof(char)));
                                for (k = 0; k < output_len; ++k) {
                                        new_output_lines[i][k] = output_lines[i][k];
                                }
                                new_output_lines[i][k] = '\0';
                        }
                }
        }
        for (i = 0; i < input_line_count; ++i) {
                for (k = 0; new_input_lines[i][k] != '\0'; ++k) {
                        print_char(new_input_lines, new_output_lines, i, k, input_line_count, method, direction, input_type, key);
                }
        }
        /* Speicherplatz freigeben */
        for (i = 0; i < input_line_count; ++i) {
                free(input_lines[i]);
                free(output_lines[i]);
                free(new_input_lines[i]);
                free(new_output_lines[i]);
        }
        free(input_lines);
        free(output_lines);
        free(new_input_lines);
        free(new_output_lines);
        return SUCCESS;
}

int print_char(char **input, char **output, int i, int k, int input_line_count, int method, int direction, int input_type, char key[])
{
        int c, c2, j, l, status;
        c = output[i][k];
        if ((c >= 'A') && (c <= 'Z')) {
                for (c2 = 'A'; c2 <= c; ++c2) {
                        /* Terminal leeren */
                        status =  clear_running(method, direction, input_type, key);
                        printf(BOLD"\n\tErgebnis:\n\n"RESET_TXT_ATTRIBUTES);
                        if (check_error(status) < 0) {
                                return status;
                        }
                        for (j = 0; j < input_line_count; ++j) {
                                printf("\t");
                                if (j < i) {
                                        printf("%s", output[j]);
                                } else if (j == i) {
                                        for (l = 0; l < (int) strlen(input[j]); ++l) {
                                                if (l < k) {
                                                        printf("%c", output[j][l]);
                                                } else if (l == k) {
                                                        /* hier mit Animation ausgeben */
                                                        printf("%c", c2);
                                                } else {
                                                        printf("%c", input[j][l]);
                                                }
                                        }
                                } else {
                                        printf("%s", input[j]);
                                }
                                printf("\n");
                        }
                        /* Ausgabepuffer leeren */
                        fflush(stdout);
                }
        } else if ((c >= 'a') && (c <= 'z')) {
                for (c2 = 'a'; c2 <= c; ++c2) {
                        /* Terminal leeren */
                        status =  clear_running(method, direction, input_type, key);
                        printf(BOLD"\n\tErgebnis:\n\n"RESET_TXT_ATTRIBUTES);
                        if (check_error(status) < 0) {
                                return status;
                        }
                        for (j = 0; j < input_line_count; ++j) {
                                printf("\t");
                                if (j < i) {
                                        printf("%s", output[j]);
                                } else if (j == i) {
                                        for (l = 0; l < (int) strlen(input[j]); ++l) {
                                                if (l < k) {
                                                        printf("%c", output[j][l]);
                                                } else if (l == k) {
                                                        /* hier mit Animation ausgeben */
                                                        printf("%c", c2);
                                                } else {
                                                        printf("%c", input[j][l]);
                                                }
                                        }
                                } else {
                                        printf("%s", input[j]);
                                }
                                printf("\n");
                        }
                        /* Ausgabepuffer leeren */
                        fflush(stdout);
                }
        } else if ((c >= '0') && (c <= '9')) {
                for (c2 = '0'; c2 <= c; ++c2) {
                        /* Terminal leeren */
                        status = clear_running(method, direction, input_type, key);
                        printf(BOLD"\n\tErgebnis:\n\n"RESET_TXT_ATTRIBUTES);
                        if (check_error(status) < 0) {
                                return status;
                        }
                        for (j = 0; j < input_line_count; ++j) {
                                printf("\t");
                                if (j < i) {
                                        printf("%s", output[j]);
                                } else if (j == i) {
                                        for (l = 0; l < (int) strlen(input[j]); ++l) {
                                                if (l < k) {
                                                        printf("%c", output[j][l]);
                                                } else if (l == k) {
                                                        /* hier mit Animation ausgeben */
                                                        printf("%c", c2);
                                                } else {
                                                        printf("%c", input[j][l]);
                                                }
                                        }
                                } else {
                                        printf("%s", input[j]);
                                }
                                printf("\n");
                        }
                        /* Ausgabepuffer leeren */
                        fflush(stdout);
                }
        } else if (ispunct(c)) {
                c2 = '!';
                while (c2 <= c) {
                        /* Terminal leeren */
                        status = clear_running(method, direction, input_type, key);
                        printf(BOLD"\n\tErgebnis:\n\n"RESET_TXT_ATTRIBUTES);
                        if (check_error(status) < 0) {
                                return status;
                        }
                        for (j = 0; j < input_line_count; ++j) {
                                printf("\t");
                                if (j < i) {
                                        printf("%s", output[j]);
                                } else if (j == i) {
                                        for (l = 0; l < (int) strlen(input[j]); ++l) {
                                                if (l < k) {
                                                        printf("%c", output[j][l]);
                                                } else if (l == k) {
                                                        /* hier mit Animation ausgeben */
                                                        printf("%c", c2);
                                                } else {
                                                        printf("%c", input[j][l]);
                                                }
                                        }
                                } else {
                                        printf("%s", input[j]);
                                }
                                printf("\n");
                        }
                        /* Ausgabepuffer leeren */
                        fflush(stdout);
                        if (c2 == '/') {
                                c2 += 11;
                        } else if (c2 == '@' || c2 == '`') {
                                c2 += 26;
                        } else {
                                ++c2;
                        }
                }
        } else if (c == ' ') {
                c2 = ' ';
                /* Terminal leeren */
                status = clear_running(method, direction, input_type, key);
                printf(BOLD"\n\tErgebnis:\n\n"RESET_TXT_ATTRIBUTES);
                if (check_error(status) < 0) {
                        return status;
                }
                for (j = 0; j < input_line_count; ++j) {
                        printf("\t");
                        if (j < i) {
                                printf("%s", output[j]);
                        } else if (j == i) {
                                for (l = 0; l < (int) strlen(input[j]); ++l) {
                                        if (l < k) {
                                                printf("%c", output[j][l]);
                                        } else if (l == k) {
                                                /* hier mit Animation ausgeben */
                                                printf("%c", c2);
                                        } else {
                                                printf("%c", input[j][l]);
                                        }
                                }
                        } else {
                                printf("%s", input[j]);
                        }
                        printf("\n");
                }
                /* Ausgabepuffer leeren */
                fflush(stdout);
        }

        return SUCCESS;
}

/**
 * Saves 'text' with added '\n' characters in 'new_text' so 'text' can be printed with a maximum width
 * @param text String to be edited
 * @param new_text Empty string to be filled with edited version of 'text'
 * @param max_line_len Maximum number of characters allowed in one line
 * @return Return whether or not the edit was successful
 */
int add_line_breaks(char* text, char** new_text, int max_line_len)
{
        int i, j, k, new_text_len, word_len, spaces_removed, lines_added, line_len, textlen;
        textlen = strlen(text);
        line_len = 0;
        new_text_len = textlen;
        lines_added = 0;
        spaces_removed = 0;
        /* Fügt ein Leerzeichen nach max_line_len Zeichen ein, falls eine Zeile sonst länger als max_line_len Zeichen wäre */
        for (i = 0; i < textlen; ++i) {
                /* printf("(*new_text)[%i] = text[%i] => '%c'\n", i + lines_added, i, text[i]);*/
                (*new_text)[i + lines_added] = text[i];
                if (text[i] == '\n') {
                        line_len = 0;
                } else {
                        ++line_len;
                        if (line_len == max_line_len) {
                                ++lines_added;
                                /* new_text wird um 1 vergößert */
                                *new_text = realloc(*new_text, (textlen + 2) * sizeof(char));
                                if (*new_text == NULL) {
                                        return MALLOC_ERROR;
                                }
                                /* Zeilenumbruch wird eingefügt */
                                (*new_text)[i + lines_added] = '\n';
                                ++new_text_len;
                                line_len = 0;
                        } else {
                                j = i;
                                word_len = 0;
                                if ((text[i] == ' ') || (text[i] == '\n') || (text[i] == '\t') || (i == 0)) {
                                        /* Aktuelles Zeichen ist ein Zeilenumbruch oder Leerzeichen */
                                        /* Zeichen des nächsten Wortes zählen zählen */
                                        while ((text[j + 1] != ' ') && (text[j + 1] != '\n') && (text[j + 1] != '\t') && (text[j + 1] != '\0')) {
                                                ++j;
                                                ++word_len;
                                        }
                                }
                                /* printf("word_len: %i\n", word_len); */
                                if (line_len + word_len >= max_line_len) {
                                        /* printf("Case 2 reached!\n"); */
                                        ++lines_added;
                                        /* new_text wird um 1 vergößert */
                                        *new_text = realloc(*new_text, (new_text_len + 2) * sizeof(char));
                                        if (*new_text == NULL) {
                                                return MALLOC_ERROR;
                                        }
                                        ++new_text_len;
                                        /* Zeilenumbruch wird eingefügt */
                                        (*new_text)[i + lines_added] = '\n';
                                        line_len = 0;
                                        /* Wort wird nach new_text kopiert */
                                        for (k = i + 1; k <= i + word_len; ++k) {
                                                ++line_len;
                                                *new_text = realloc(*new_text, (new_text_len + 2) * sizeof(char));
                                                if (*new_text == NULL) {
                                                        return MALLOC_ERROR;
                                                }
                                                (*new_text)[k + lines_added] = text[k];
                                        }
                                        i = j;
                                }
                        }

                }
        }
        *new_text = realloc(*new_text, (new_text_len + 2) * sizeof(char));
        if (*new_text == NULL) {
                return MALLOC_ERROR;
        }
        (*new_text)[new_text_len] = '\0';
        /* Entfernt Leerzeichen am Anfang einer neuen Zeile */
        for (i = 0; i < new_text_len; ++i) {
                if (((*new_text)[i + spaces_removed] == '\n') && ((*new_text)[i + 1] == ' ')) {
                        (*new_text)[i + spaces_removed] = '\n';
                        for (j = i + spaces_removed + 1; j < new_text_len; ++j) {
                                (*new_text)[j] = (*new_text)[j + 1];
                        }
                        ++spaces_removed;
                }
        }
        return SUCCESS;
}

