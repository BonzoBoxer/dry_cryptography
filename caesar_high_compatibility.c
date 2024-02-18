#include "error_codes.h"
#include "caesar.h"

/**
 * Encrypts 'input' by shifting every letter by 'key'
 * @param input String containing text to be encrypted
 * @param output Empty string to be filled with encryption
 * @param key Number of shifts to be applied
 * @return Returns whether or not the encryption was successful
 */
int compatible_caesar_cipher(char input[], char output[], int key)
{
        int i;
        char base;
        if (key < 1) {
                return INVALID_KEY;
        }
        if (strlen(input) < 1) {
                return INVALID_INPUT;
        }
        key = (key + 26) % 26;
        for (i = 0; input[i] != '\0'; ++i) {
                if (isalpha(input[i])) {
                        base = (isupper(input[i]) ? ('A') : ('a'));
                        output[i] = (input[i] - base + key + 26) % 26 + base;
                } else {
                        output[i] = input[i];
                }
        }
        output[i] = '\0';
        return ENCIPHER_SUCCESS;
}

/**
 * Decrypts 'input' by shifting all letters by -('key')
 * @param input String containing encrypted text
 * @param output Empty string to be filled with decrypted text
 * @param key Number of shifts used when text was encrypted
 * @return Returns whether or not the decryption was successful
 */
int compatible_caesar_decipher(char input[], char output[], int key)
{
        int i;
        char base;
        if (key < 1) {
                return INVALID_KEY;
        }
        if (strlen(input) < 1) {
                return INVALID_INPUT;
        }
        key = (key + 26) % 26;
        for (i = 0; input[i] != '\0'; ++i) {
                if (isalpha(input[i])) {
                        base = (isupper(input[i]) ? ('A') : ('a'));
                        output[i] = (input[i] - base - key + 26) % 26 + base;
                } else {
                        output[i] = input[i];
                }
        }
        output[i] = '\0';
        return DECIPHER_SUCCESS;
}
