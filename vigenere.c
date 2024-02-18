#include "error_codes.h"
#include "vigenere.h"

char tabula_recta_uppercase[ALPHABET_LEN][ALPHABET_LEN];
char tabula_recta_lowercase[ALPHABET_LEN][ALPHABET_LEN];

int verify_key_vigenere(char* key)
{
        /* Kontrolliert key auf Richtigkeit und gibt Fehlerwert oder VALID_KEY zurück */
        int i, keylength;
        keylength = strlen(key);
        /* Key muss mindestens ein Zeichen haben */
        if (keylength == 0) {
                return INVALID_KEY;
        }
        for (i = 0; i < keylength; ++i) {
                /* Key darf nur aus Großbuchstaben bestehen */
                if ((key[i] < 'A') || (key[i] > 'Z')) {
                        return INVALID_KEY;
                }
        }
        return VALID_KEY;
}

/**
 * Fills tabula recta (for both capital letters and lowercase letters)
 */
void fill_tabula(void)
{
        int i, j;
        /* "Befüllen" der Tabula recta für Großbuchstaben */
        for (i = 0; i < ALPHABET_LEN; ++i) {
                for (j = 0; j < ALPHABET_LEN; ++j) {
                        if ((i + j) <= 25) {
                                tabula_recta_uppercase[i][j] = 'A' + i + j;
                        } else {
                                tabula_recta_uppercase[i][j] = 'A' + i + j - ALPHABET_LEN;
                        }
                }
        }
        /* "Befüllen" der Tabula recta für Kleinbuchstaben */
        for (i = 0; i < ALPHABET_LEN; ++i) {
                for (j = 0; j < ALPHABET_LEN; ++j) {
                        if ((i + j) <= 25) {
                                tabula_recta_lowercase[i][j] = 'a' + i + j;
                        } else {
                                tabula_recta_lowercase[i][j] = 'a' + i + j - ALPHABET_LEN;
                        }
                }
        }
}

/**
 * Encrypts 'text' with 'key' using the vigenere-cipher (https://www.youtube.com/watch?v=3PCEzxK0dso)
 * @param text String to be encrypted
 * @param key String to be used as key
 * @param encrypted Empty string to be filled with encryption
 * @return Returns whether or not the encryption was successful
 */
int encrypt_vigenere(char text[], char key[], char encrypted[])
{
        int i, quotient;
        int special_count = 0;
        int keyLength = (int)strlen(key);
        int textLength = (int)strlen(text);

        /* Key verifizieren */
        if (verify_key_vigenere(key) == INVALID_KEY) {
                return INVALID_KEY;
        }

        if (strlen(text) < 1) {
                return INVALID_INPUT;
        }

        /* Verschlüsseln */
        for (i = 0; i < (textLength); ++i) {
                if ((text[i] >= 'A') && (text[i] <= 'Z')) {
                        quotient = (i - special_count) / keyLength;
                        encrypted[i] = tabula_recta_uppercase[(key[i - special_count - quotient * keyLength] - 'A')][(text[i] - 'A')];
                } else if ((text[i] >= 'a') && (text[i] <= 'z')) {
                        quotient = (i - special_count) / keyLength;
                        encrypted[i] = tabula_recta_lowercase[(key[i - special_count - quotient * keyLength] - 'A')][(text[i] - 'a')];
                } else {
                        /* Alle Zeichen, die keine Buchstaben sind bleiben gleich */
                        encrypted[i] = text[i];
                        /* Alle Zeichen, die keine Buchstaben sind werden "übersprungen" und nicht mitgezählt */
                        ++special_count;
                }
        }
        encrypted[i] = '\0';
        return SUCCESS;
}

/**
 * Decrypts 'encrypted' using 'key'
 * @param encrypted String to be decrypted
 * @param key String to be used as key
 * @param decrypted Empty string to be filled with decrypted 'encrypted'
 * @return
 */
int decrypt_vigenere(char encrypted[], char key[], char decrypted[])
{
        int i, k, quotient, encrypted_len;
        int special_count;
        int keyLength = (int)strlen(key);

        /* Key verifizieren */
        if (verify_key_vigenere(key) == INVALID_KEY) {
                return INVALID_KEY;
        }

        if (strlen(encrypted) < 1) {
                return INVALID_INPUT;
        }

        /* Entschlüsseln */
        encrypted_len = strlen(encrypted);
        special_count = 0;
        for (i = 0; i < (encrypted_len); ++i) {
                quotient = (i - special_count) / keyLength;
                if ((encrypted[i] >= 'A') && (encrypted[i] <= 'Z')) {
                        for (k = 0; k < ALPHABET_LEN; ++k) {
                                if ((tabula_recta_uppercase[key[i - special_count - quotient * keyLength] - 'A'][k]) == encrypted[i]) {
                                        decrypted[i] = tabula_recta_uppercase[0][k];
                                        break;
                                }
                        }
                } else if ((encrypted[i] >= 'a') && (encrypted[i] <= 'z')) {
                        for (k = 0; k < ALPHABET_LEN; ++k) {
                                if ((tabula_recta_lowercase[key[i - special_count - quotient * keyLength] - 'A'][k]) == encrypted[i]) {
                                        decrypted[i] = tabula_recta_lowercase[0][k];
                                        break;
                                }
                        }
                } else {
                        decrypted[i] = encrypted[i];
                        /* Alle Zeichen, die keine Großbuchstaben sind "übersprungen" und nicht mitgezählt */
                        ++special_count;
                }
        }
        decrypted[i] = '\0';
        return SUCCESS;
}
