#ifndef POLYBIOS_H_INCLUDED
#define POLYBIOS_H_INCLUDED

#include <string.h>

void fill_alphabet(char* key, int keylen);
void fill_square(char* key);
int encrypt_polybios(char text[], char key[], char encrypted[]);
int decrypt_polybios(char encrypted[], char key[], char decrypted[]);
int verify_key_polybios(char* key);
int verify_text_polybios(char* text);
int verify_encryption_polybios(char* encryption);

#endif
