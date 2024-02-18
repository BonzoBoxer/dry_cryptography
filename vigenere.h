#ifndef VIGENERE_H_INCLUDED
#define VIGENERE_H_INCLUDED

#include <string.h>

#define ALPHABET_LEN 26
#define MAX_LEN 50

void fill_tabula(void);
int encrypt_vigenere(char text[], char key[], char encrypted[]);
int decrypt_vigenere(char encrypted[], char key[], char decrypted[]);
int verify_key_vigenere(char* key);

#endif
