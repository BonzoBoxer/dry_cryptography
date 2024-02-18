#include "shift_e.h"
#include "error_codes.h"


/**
 * Fills 'output' with the result of the frequency analysis (the most frequent letter in 'input' is shifted to be
 * an 'E'/'e', all other letters are moved by the same shift)
 * @param input A char-array containing the original text
 * @param output The empty char-array to be filled with the result
 * @return Returns whether or not the analysis was successful
 */
int shift_e(char input[], char output[])
{
        int difference;
        char most_frequent_char;
        int i;
        char base;
        if (strlen(input) < 1) {
                return INVALID_INPUT;
        }
        most_frequent_char = most_frequent(input);
        difference = most_frequent_char - (isupper(most_frequent_char) ? ('E') : ('e'));
        difference = (difference + 26) % 26;
        for (i = 0; input[i] != '\0'; ++i) {
                if (isalpha(input[i])) {
                        base = (isupper(input[i]) ? ('A') : ('a'));
                        output[i] = (input[i] - base - difference + 26) % 26 + base;
                } else {
                        output[i] = input[i];
                }
        }
        output[i] = '\0';
        return SUCCESS;
}


/**
 * Finds the most frequent letter in 'string'
 * @param string The string to be analysed
 * @return Returns the most frequent letter in 'string'
 */
char most_frequent(char string[])
{
        int i, j;
        char most_frequent;
        int max_frequency = 1;
        int frequency;
        char current_char;
        for (i = 1; string[i] != '\0'; ++i) {
                if (isalpha(string[i])) {
                        current_char = string[i];
                        frequency = 0;
                        for (j = 1; string[j] != '\0'; ++j) {
                                if (isalpha(string[j])) {
                                        if (string[j] == toupper(current_char) || string[j] == tolower(current_char)) {
                                                ++frequency;
                                        }
                                }
                        }

                        if (frequency > max_frequency) {
                                max_frequency = frequency;
                                most_frequent = current_char;
                        }
                }
        }
        return most_frequent;
}
