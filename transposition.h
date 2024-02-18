#ifndef TRANSPOSITION_H_INCLUDED
#define TRANSPOSITION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int transposition_cipher(char cipher_text[], char deciphered_text[], int key);
int transposition_decipher(char deciphered_text[], char ciphered_text[], int key);
int calculate_diagonals(int text_length, int rails);
void remove_placeholders(char adjusted_text[], char is_placeholder[]);
int fill_cipher_rails(char*** ciphered_rails, char* ciphered_text_pure, int outer_rails_len, int inter_rails_len, int key);
void join_rails(char** ciphered_rails, char deciphered_text[], int ciphered_text_len, int key);

#endif
