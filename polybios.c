#include "error_codes.h"
#include "polybios.h"

char alphabet_square_lowercase[5][5];
char alphabet_square_uppercase[5][5];
/* Alphabet ohne I */
char alphabet_25_uppercase[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
char alphabet_uppercase[26];
char alphabet_lowercase[26];

/**
 * Verifies the key
 * @param key Key to be used for polybius en-/decryption
 * @return Returns whether or not 'key' is valid
 */
int verify_key_polybios(char* key)
{
        /* Kontrolliert key auf Richtigkeit und gibt INVALID_KEY oder VALID_KEY zurück */
        int i, k, keylength;
        keylength = strlen(key);
        /* Key muss mindestens ein Zeichen haben */
        if (keylength == 0) {
                return INVALID_KEY;
        }
        for (i = 0; i < keylength; ++i) {
                /* Key darf nur aus Großbuchstaben bestehen */
                if ((key[i] < 'A') || (key[i] > 'Z')) {
                        return INVALID_KEY;
                } else if (key[i] == 'J') {
                        /* Key darf kein 'J' enthalten */
                        return INVALID_KEY;
                }
                /* Jeder Buchstabe im key darf nur einmal vorkommen */
                for (k = 0; k < keylength; ++k) {
                        if ((k != i) && (key[k] == key[i])) {
                                return INVALID_KEY;
                        }
                }
        }
        return VALID_KEY;
}

/**
 * Verifies the text to be encrypted
 * @param text String to be checked
 * @return Returns whether or not polybius-cipher can be applied to 'input'
 */
int verify_text_polybios(char* text)
{
        /* Überprüft text auf Richtigkeit und gibt INVALID_INPUT oder SUCCESS zurück */
        int i, textlength;
        textlength = strlen(text);
        if (textlength == 0) {
                return INVALID_INPUT;
        }
        for (i = 0; i < textlength; ++i) {
                /* Text darf keine Zahlen enthalten */
                if ((text[i] >= '0') && (text[i] <= '9')) {
                        return INVALID_INPUT;
                }
        }
        return SUCCESS;
}

/**
 * Verifies the text to be decrypted
 * @param encryption String to be checked
 * @return Returns whether or not polybius-decipher can be applied to 'encryption'
 */
int verify_encryption_polybios(char* encryption)
{
        /* Überprüft text auf Richtigkeit und gibt INVALID_ENCRYPTION oder VALID_INPUT zurück */
        int i, encryption_length;
        encryption_length = strlen(encryption);
        if (encryption_length == 0) {
                return INVALID_ENCRYPTION;
        }
        for (i = 0; i < encryption_length; ++i) {
                /* Verschlüsselter Text darf keine Buchstaben enthalten */
                if (((encryption[i] >= 'A') && (encryption[i] <= 'Z')) || ((encryption[i] >= 'a') && (encryption[i] <= 'z'))) {
                        return INVALID_ENCRYPTION;
                }
        }
        return VALID_INPUT;
}

void fill_alphabet(char* key, int keylen)
{
        int i, k, check, skip;
        check = 0;
        skip = 0;
        /* Erstellen des Großbuchstaben-Alphabets */
        for (i = 0; i < 26; ++i) {
                for (k = 0; k < keylen; ++k) {
                        if ((alphabet_25_uppercase[i]) == key[k]) {
                                check = 1;
                                ++skip;
                                break;
                        }
                }
                if (check == 0) {
                        alphabet_uppercase[i - skip] = alphabet_25_uppercase[i];
                        
                }
                check = 0;
        }
        /* Erstellen des Kleinbuchstaben-Alphabets */
        for (i = 0; i < (int) strlen(alphabet_uppercase); ++i) {
                alphabet_lowercase[i] = alphabet_uppercase[i] + 32;       
        }
}

void fill_square(char* key)
{
        int i, k, keylen_left, alphabet_left, alphabet_len, keylen;
        keylen = strlen(key);
        alphabet_len = strlen(alphabet_uppercase);
        alphabet_left = alphabet_len;
        keylen_left = keylen;
        fill_alphabet(key, keylen);
        /* "Befüllen" des Großbuchstaben-Quadrats */
        for (i = 0; i < 5; ++i) {
                for (k = 0; k < 5; ++k) {
                        if (keylen_left > 0) {
                                alphabet_square_uppercase[i][k] = key[keylen - keylen_left];
                                --keylen_left;
                        } else {
                                alphabet_square_uppercase[i][k] = alphabet_uppercase[alphabet_len - alphabet_left];
                                --alphabet_left;
                        }
                }
        }
        /* "Befüllen" des Großbuchstaben-Quadrats */
        for (i = 0; i < 5; ++i) {
                for (k = 0; k < 5; ++k) {
                        alphabet_square_lowercase[i][k] = alphabet_square_uppercase[i][k] + 32;
                }
        }
}

/**
 * Encrypts 'text' using 'key'
 * @param text String to be encrypted
 * @param key String to act as key
 * @param encrypted Empty string to be filled with result of encryption
 * @return Returns whether or not the encryption was successful
 */
int encrypt_polybios(char text[], char key[], char encrypted[])
{
        int str_pos, i, k, textLength, special_count;

        /* Text verifizieren */
        if (verify_text_polybios(text) == INVALID_INPUT) {
                return INVALID_INPUT;
        }
        /* Key verifizieren */
        if (verify_key_polybios(key) == INVALID_KEY) {
                return INVALID_KEY;
        }

        special_count = 0;
        textLength = strlen(text);
        fill_square(key);
        for (str_pos = 0; str_pos < textLength; ++str_pos) {
                if ((text[str_pos] >= 'A') && (text[str_pos] <= 'Z')) {
                        for (i = 0; i < 5; ++i) {
                                /* J wird durch I ersetzt */
                                if (text[str_pos] == 'J') {
                                        text[str_pos] = 'I';
                                }
                                for (k = 0; k < 5; ++k) {
                                        if (alphabet_square_uppercase[i][k] == text[str_pos]) {
                                                encrypted[2 * str_pos - special_count] = i + 1 + '0';
                                                encrypted[2 * str_pos - special_count + 1] = k + 1 + '0';
                                        }
                                }
                        }
                } else if ((text[str_pos] >= 'a') && (text[str_pos] <= 'z')) {
                        for (i = 0; i < 5; ++i) {
                                /* J wird durch I ersetzt */
                                if (text[str_pos] == 'j') {
                                        text[str_pos] = 'i';
                                }
                                for (k = 0; k < 5; ++k) {
                                        if (alphabet_square_lowercase[i][k] == text[str_pos]) {
                                                encrypted[2 * str_pos - special_count] = i + 1 + '0';
                                                encrypted[2 * str_pos - special_count + 1] = k + 1 + '0';
                                        }
                                }
                        }
                } else {
                        /* Alle Zeichen, die keine Groß- oder Kleinbuchstaben sind, werden unverändert kopiert */
                        encrypted[2 * str_pos - special_count] = text[str_pos];
                        ++special_count;
                }
        }
        encrypted[str_pos * 2 - special_count] = '\0';
        return SUCCESS;
}

/**
 * Decrypts 'encrypted' using 'key'
 * @param encrypted Encrypted text to be decrypted
 * @param key String to act as key
 * @param decrypted Empty string to be filled with decryption of 'encrypted'
 * @return Returns whether or not the decryption was successful
 */
int decrypt_polybios(char encrypted[], char key[], char decrypted[])
{
        /* Bei der Entschlüsselung werden alle Zahlen ausschließlich zu Großbuchstaben entschlüsselt! */
        int encrypted_len, str_pos, special_count, special_count_total;

        /* Encryption verifizieren */
        if (verify_encryption_polybios(encrypted) == INVALID_ENCRYPTION) {
                return INVALID_INPUT;
        }
        /* Key verifizieren */
        if (verify_key_polybios(key) == INVALID_KEY) {
                return INVALID_KEY;
        }

        special_count_total = 0;
        encrypted_len = strlen(encrypted);
        for (str_pos = 0; str_pos < encrypted_len; ++str_pos) {
                if ((encrypted[str_pos] < '0') || (encrypted[str_pos] > '9')) {
                        ++special_count_total;
                }
        }
        special_count = 0;
        fill_square(key);
        for (str_pos = 0; str_pos < (encrypted_len - special_count_total) / 2 + special_count_total; ++str_pos) {
                if ((encrypted[str_pos * 2 - special_count] < '0') || (encrypted[str_pos * 2 - special_count] > '9')) {
                        /*printf("(S) decrypted[%i] = encrypted[%i] => '%c'\n", str_pos, 2 * str_pos - special_count, encrypted[2 * str_pos - special_count]);*/
                        decrypted[str_pos] = encrypted[2 * str_pos - special_count];
                        ++special_count;
                } else {
                        /*printf("(N) decrypted[%i] = alphabet_square[encrypted[%i]][encrypted[%i]] => '%c'\n", str_pos, str_pos * 2 - special_count, str_pos * 2 + 1 - special_count, alphabet_square[encrypted[str_pos * 2 - special_count] - 1 - '0'][encrypted[str_pos * 2 + 1 - special_count] - 1 - '0']);*/
                        decrypted[str_pos] = alphabet_square_uppercase[encrypted[str_pos * 2 - special_count] - 1 - '0'][encrypted[str_pos * 2 + 1 - special_count] - 1 - '0'];
                }
        }
        decrypted[str_pos] = '\0';
        return SUCCESS;
}
