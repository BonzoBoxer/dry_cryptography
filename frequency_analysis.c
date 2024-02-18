#include "frequency_analysis.h"
#include "error_codes.h"
#include "optics.h"

/*Häufigkeitsanalyse ist ein Verfahren welches nur auf
monoalphabetische Substitutionen angewendet werden kann*/

int is_syntax(char a) {
        if (isalnum(a) || ispunct(a) || a == ' ' || a == '\n') {
                return 1;
        } else {
                return 0;
        }
}


int count_frequency(char input[], int small_letter) 
{
        int i, count = 0;
        for (i = 0; input[i] != '\0'; ++i) {
                if (input[i] == small_letter || input[i] == (small_letter - 32)) {
                        ++count;
                } else if (!is_syntax(input[i])) {
                        return INVALID_INPUT;
                }
        }
        return count;
}

int get_frequency(int frequency[], char input[]) 
{
        int i, j = 0;
        int result;
        int existing_frequencies = 0;
        for (i = 0; i < 26; ++i) {
                result = count_frequency(input, i + 'a');
                if(result != INVALID_INPUT) {
                        frequency[j] = result; /*frequency[0] == a*/
                        if (result != 0) {
                                ++existing_frequencies;
                        }
                        ++j;
                } else {
                        return INVALID_INPUT;
                }
        }
        return existing_frequencies;
}



int sort_frequency(char input[], char output[])
{
        char decryption_map_low[ALPHABET_SIZE] = {"enisratdhulcgmobwfkzpvjyxq"};
        char decryption_map_high[ALPHABET_SIZE] = {"ENISRATDHULCGMOBWFKZPVJYXQ"};
        int j, k, l = 0; /*zählvariablen*/
        int largest, position, count = 0, existing_frequencies;
        int frequency[ALPHABET_SIZE] = {0};
        int strlen_input = (int)strlen(input);

        if (strlen(input) < 1) {
                return INVALID_INPUT;
        }

        existing_frequencies = get_frequency(frequency, input);/*zählt häufigkeit*/
        if (existing_frequencies == INVALID_INPUT) {
                return INVALID_INPUT;
        }

        strcpy(output, input);
        while(1) {
                largest = INT_MIN;
                for(k = 0; k < ALPHABET_SIZE; ++k) {
                        if (frequency[k] > largest) {
                                largest = frequency[k];
                                position = k;
                        }
                }

                if (largest == INT_MIN) {
                        break; /*beendet schleife*/
                }

                for (j = 0; j < strlen_input; ++j) {
                        if (input[j] == position + 'a') {
                                output[j] = decryption_map_low[l];
                        } else if (input[j] == position + 'A') {
                                output[j] = decryption_map_high[l];
                        }
                }
                ++count;
                ++l;

                frequency[position] = INT_MIN; /*löschen der aktuell größten Zahl*/
                position = INT_MIN;
                if (count == existing_frequencies) {
                        break;
                }
        }
        output[strlen_input] = '\0';
        return SUCCESS;
}


void print_fre_legend(void) {
        char characters[] = "ENISRATDHULCGMOBWFKZPVJYXQ";
        float percentages[] = {17.40, 9.78, 7.55, 7.38, 7.00, 6.51, 6.15, 5.08, 4.76, 4.35, 3.44, 3.06, 3.01, 2.53, 2.51, 1.89, 1.89, 1.66, 1.21, 1.13, 0.79, 0.67, 0.27, 0.04, 0.03, 0.02};
        int i;
        printf("\n\n");
        print_centered_text("Häufigkeitsverteilung von Buchstaben in deutschen Texten:");
        printf("\t\t       +================================+\n\t\t       ");
        printf("|  %c   %.2f%%\t    ", characters[0], percentages[0]);
        for (i = 1; i < 26; ++i) {
                if (i % 2 != 0) {
                        printf("%c    %.2f%%  ", characters[i], percentages[i]);
                        printf("|\n\t\t       ");
                } else {
                        printf("|  %c    %.2f%%\t    ", characters[i], percentages[i]);
                }
        }
        printf("+================================+");
}

void print_fre_legend_short(void)
{
        int i;
        char characters[] = {'E', 'N', 'I', 'S'};
        float percentages[] = {17.40, 9.78, 7.55, 7.27};
        printf("\n\n");
        print_centered_text("Häufigkeitsverteilung von Buchstaben in deutschen Texten:");
        printf("\t\t       +================================+\n\t\t       ");
        printf("|  %c   %.2f%%\t    ", characters[0], percentages[0]); /*1. Wert*/
        for (i = 1; i < 3; ++i) { /*Werte 2 + 3*/
                if (i % 2 != 0) {
                        printf("%c    %.2f%%  ", characters[i], percentages[i]);
                        printf("|\n\t\t       ");
                } else {
                        printf("|  %c    %.2f%%\t    ", characters[i], percentages[i]);
                }
        }
        printf("%c    %.2f%%  |\n", characters[3], percentages[3]); /*4. Wert*/
        printf("\t\t    ----------------------------------------\n");
}

int change_letters(char changed[], char input[], char orig_letter, char new_letter)
{
        int i;
        strcpy(changed, input);
        if (!is_syntax(new_letter) || !is_syntax(orig_letter)) {
                return INVALID_INPUT;
        }
        for (i = 0; i < (int)strlen(changed); ++i) {
                if (toupper(changed[i]) == toupper(orig_letter)) {
                        changed[i] = (isupper(changed[i])) ? (toupper(new_letter)) : (tolower(new_letter));
                } else if (toupper(changed[i]) == toupper(new_letter)) {
                        changed[i] = (isupper(changed[i])) ? (toupper(orig_letter)) : (tolower(orig_letter));
                }
        }

        return SUCCESS;
}


void return_to_original(char input[], char original[])
 {
        /*input soll wieder original sein*/
        int i;
        for (i = 0; i < (int)strlen(original); ++i) {
                input[i] = original[i];
        }
}
