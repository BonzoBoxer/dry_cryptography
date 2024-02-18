#ifndef CAESAR_H_INCLUDED
#define CAESAR_H_INCLUDED

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>


#define LOW_KEY 1
#define UPPER_KEY 94

#define UPPER_BORDER 126
#define LOW_BORDER 32
#define DIFFERENCE_BORDER 95 /*Upper Border muss ebenfalls beinhaltet sein*/


#define ENCIPHER_SUCCESS 5000
#define DECIPHER_SUCCESS 5001

int cs_encipher(int key, char input[], char encipher_text[]);
int cs_decipher(int key, char input[], char decipher_text[]);
int control_key(int key);

int compatible_caesar_cipher(char input[], char output[], int key);
int compatible_caesar_decipher(char input[], char output[], int key);

#endif
