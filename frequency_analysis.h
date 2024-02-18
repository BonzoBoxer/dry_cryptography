#ifndef OPTIMIZED_HA_INCLUDED
#define OPTIMIZED_HA_INCLUDED

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define VALID_LETTER_CHANGE 1000
#define ALPHABET_SIZE 26
/*
// Häufigkeitsanalyse ist ein Verfahren welches nur auf monoalphabetische Substitutionen angewendet werden kann*/

int is_syntax(char a);
int count_frequency(char input[], int small_letter);
int get_frequency(int frequency[], char input[]);
int sort_frequency(char input[], char output[]);
void print_fre_legend(void);
void print_fre_legend_short(void);
int change_letters(char changed[], char input[], char orig_letter, char new_letter);
void return_to_original(char input[], char original[]);


#endif
