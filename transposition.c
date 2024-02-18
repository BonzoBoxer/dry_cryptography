#include "transposition.h"
#include "error_codes.h"

int x = 0;
int recursion = 0;

/**
 * Function fills 'cipher_text' with the ciphered version of 'deciphered_text' using 'key' rails
 * @param cipher_text Empty array which gets filled with ciphered text using "Rail fence cipher"
 * @param deciphered_text Array filled with text to be ciphered
 * @param key Number of rails to be used (lines to break up deciphered text)
 * @return Returns whether or not ciphering was successful
 */
int transposition_cipher(char cipher_text[], char deciphered_text[], int key)
{
        int period = 2 * (key - 1);
        char** rail_fence;
        char* adjusted_text;
        char c;
        int outer_rails;
        int intermediate_rails;
        int rail = 0;
        int rail_char_index_outer = 0;
        int rail_char_index_inter = 0;
        int bool_rail_increment = 1;
        int deciphered_text_len = (int) strlen(deciphered_text);
        int deciphered_text_len_pure = 0;
        int adjusted_len;
        int empty_spaces;
        int status;
        int i, j;

        if (strlen(deciphered_text) < 3) {
                return INVALID_INPUT;
        }

        rail_fence = malloc(key * sizeof(char*));
        if (rail_fence == NULL) {
                return MALLOC_ERROR;
        }
        cipher_text[0] = '\0';

        for (i = 0; deciphered_text[i] != '\0'; ++i) {
                c = deciphered_text[i];
                if (isalnum(c) || (recursion && c == '`') || c == ' ' || ((ispunct(c)) && c != '`')) {
                        ++deciphered_text_len_pure;
                }
        }

        if (key < 2 || key >= deciphered_text_len_pure) {
                free(rail_fence);
                return INVALID_KEY;
        }

        for (empty_spaces = 0; ((deciphered_text_len_pure + empty_spaces) % period) != 0; ++empty_spaces)
        {}

        if (deciphered_text_len_pure % period == 0) {

                outer_rails = deciphered_text_len_pure / period;
                intermediate_rails = 2 * outer_rails;
                rail_fence[0] = malloc((outer_rails + 1) * sizeof(char));
                if (rail_fence[0] == NULL) {
                        free(rail_fence[0]);
                        free(rail_fence);
                        return MALLOC_ERROR;
                }
                rail_fence[key - 1] = malloc((outer_rails + 1) * sizeof(char));
                if (rail_fence[key - 1] == NULL) {
                        free(rail_fence[0]);
                        free(rail_fence[key - 1]);
                        free(rail_fence);
                        return MALLOC_ERROR;
                }
                for (i = 1; i < key - 1; ++i) {
                        rail_fence[i] = malloc((intermediate_rails + 1) * sizeof(char));
                        if (rail_fence[i] == NULL) {
                                for (j = 0; j <= i; ++j) {
                                        free(rail_fence[j]);
                                }
                                free(rail_fence[key - 1]);
                                free(rail_fence);
                                return MALLOC_ERROR;
                        }
                }

                for (i = 0; i < deciphered_text_len; ++i) {
                        c = deciphered_text[i];
                        if (isalnum(c) || c == ' ' || ((ispunct(c)) && c != '`')) {
                                if (rail == 0 || rail == key - 1) {
                                        rail_fence[rail][rail_char_index_outer] = deciphered_text[i];
                                        rail_fence[rail][rail_char_index_outer + 1] = '\0';
                                        if (bool_rail_increment == 1) {
                                                if (rail == key - 1) {
                                                        bool_rail_increment = 0;
                                                        ++rail_char_index_outer;
                                                        --rail;
                                                } else {
                                                        ++rail;
                                                }
                                        } else {
                                                if (rail == 0) {
                                                        bool_rail_increment = 1;
                                                        ++rail;
                                                } else {
                                                        --rail;
                                                }
                                        }
                                } else {
                                        rail_fence[rail][rail_char_index_inter] = deciphered_text[i];
                                        rail_fence[rail][rail_char_index_inter + 1] = '\0';
                                        if ((bool_rail_increment && rail == key - 2) || (!bool_rail_increment && rail == 1)) {
                                                ++rail_char_index_inter;
                                        }
                                        (bool_rail_increment) ? (++rail) : (--rail);
                                }
                        }
                }

                for (i = 0; i < key; ++i) {
                        strcat(cipher_text, rail_fence[i]);
                }

                if (recursion) {
                        deciphered_text_len_pure = 0;
                        for (i = 0; cipher_text[i] != '\0'; ++i) {
                                if (cipher_text[i] != '`') {
                                        ++deciphered_text_len_pure;
                                }
                        }
                }

                cipher_text[deciphered_text_len_pure] = '\0';

                recursion = 0;
                for (i = 0; i < key; ++i) {
                        free(rail_fence[i]);
                }

                free(rail_fence);

        } else {

                recursion = 1;
                adjusted_text = malloc((deciphered_text_len_pure + empty_spaces + 1) * sizeof(char));
                if (adjusted_text == NULL) {
                        free(rail_fence);
                        return MALLOC_ERROR;
                }

                j = 0;
                for (i = 0; i < deciphered_text_len; ++i) {
                        c = deciphered_text[i];
                        if (isalnum(c) || c == ' ' || ((ispunct(c)) && c != '`')) {
                                adjusted_text[j] = deciphered_text[i];
                                ++j;
                        }
                }

                adjusted_len = deciphered_text_len_pure + empty_spaces;
                for (i = deciphered_text_len_pure; i < adjusted_len; ++i) {
                        adjusted_text[i] = '`';
                }
                adjusted_text[i] = '\0';

                status = transposition_cipher(cipher_text, adjusted_text, key);
                free(adjusted_text);
                if (status != SUCCESS) {
                        return status;
                }

                for (i = 0; cipher_text[i] != '\0'; ++i) {
                        if (cipher_text[i] == '`') {
                                for (j = i + 1; cipher_text[j] != '\0'; ++j) {
                                        cipher_text[j - 1] = cipher_text[j];
                                }
                        }
                }

        }

        return SUCCESS;
}

/**
 * Function fills 'deciphered_text' with the deciphered version of 'ciphered_text' with the KNOWN 'key'
 * @param deciphered_text Empty array which gets filled with deciphered rail fence text
 * @param ciphered_text Array filled with rail fence ciphered text
 * @param key Number of rails to be used for deciphering
 * @return Returns whether or not deciphering was successful
 */
int transposition_decipher(char deciphered_text[], char ciphered_text[], int key)
{
        int i, j;
        int status;
        int ciphered_text_len = 0;
        int ciphered_text_len_pure = 0;
        int period = 2 * (key - 1);
        int outer_rails_len;
        int inter_rails_len;
        int empty_spaces;
        char* ciphered_text_pure = NULL;
        char* temp = NULL;
        char** ciphered_rails = NULL;
        char** rails = NULL;
        char* adjusted_text = NULL;
        char c;
        int y;
        int adjusted_len;
        int adjusted_index;

        if (strlen(ciphered_text) < 1) {
                return INVALID_INPUT;
        }

        for (i = 0; ciphered_text[i] != '\0'; ++i) {
                ++ciphered_text_len;
        }

        temp = malloc(1);
        if (temp == NULL) {
                return MALLOC_ERROR;
        }

        for (i = 0; i < ciphered_text_len; ++i) {
                c = ciphered_text[i];
                if (isalnum(c) || c == ' ' || ((ispunct(c)) && c != '`')) {
                        temp = realloc(ciphered_text_pure, (ciphered_text_len_pure + 2) * sizeof(char));
                        if (temp == NULL) {
                                free(ciphered_text_pure);
                                return MALLOC_ERROR;
                        }
                        ciphered_text_pure = temp;
                        ciphered_text_pure[ciphered_text_len_pure] = ciphered_text[i];
                        ++ciphered_text_len_pure;
                }
        }

        ciphered_text_pure[ciphered_text_len_pure] = '\0';

        if (key >= ciphered_text_len_pure || key < 2) {
                free(ciphered_text_pure);
                return INVALID_KEY;
        }

        for (empty_spaces = 0; ((ciphered_text_len_pure + empty_spaces) % period) != 0; ++empty_spaces)
        {}

        if (ciphered_text_len_pure % period == 0) {

                outer_rails_len = ciphered_text_len_pure / period;
                inter_rails_len = 2 * outer_rails_len;

                status = fill_cipher_rails(&ciphered_rails, ciphered_text_pure, outer_rails_len, inter_rails_len, key);

                if (status != SUCCESS) {
                        free(ciphered_text_pure);
                        return status;
                }

                deciphered_text[0] = '\0';
                join_rails(ciphered_rails, deciphered_text,ciphered_text_len_pure, key);
                deciphered_text[ciphered_text_len_pure] = '\0';
                for (i = 0; i < key; ++i) {
                        free(ciphered_rails[i]);
                }
                free(ciphered_rails);
        } else {
                y = calculate_diagonals(ciphered_text_len_pure, key);
                adjusted_len = ciphered_text_len_pure + y;
                adjusted_index = adjusted_len - 1;

                adjusted_text = malloc(adjusted_len + 1);

                adjusted_text[adjusted_len] = '\0';

                outer_rails_len = (adjusted_len + (key - 2)) / period;
                inter_rails_len = 2 * outer_rails_len - 1;

                if (x % 2 == 0) {
                        if (y) {
                                adjusted_text[adjusted_index] = '`';
                                --y;
                        }
                        for (i = adjusted_index - outer_rails_len; i >= outer_rails_len; i -= inter_rails_len) {
                                while (y) {
                                        adjusted_text[i] = '`';
                                        --y;
                                        break;
                                }
                        }
                }

                if (x % 2 != 0) {
                        --y;
                        ++inter_rails_len;
                        adjusted_index = outer_rails_len + inter_rails_len - 1;
                        for (i = adjusted_index; i < (outer_rails_len + (key - 2) * inter_rails_len); i += inter_rails_len) {
                                while (y) {
                                        adjusted_text[i] = '`';
                                        --y;
                                        break;
                                }
                        }
                }

                j = 0;

                for (i = 0; i < adjusted_len; ++i) {
                        if (adjusted_text[i] != '`') {
                                adjusted_text[i] = ciphered_text_pure[j];
                                ++j;
                        }
                }

                status = fill_cipher_rails(&rails, adjusted_text, outer_rails_len, inter_rails_len, key);

                if (status != SUCCESS) {
                        free(adjusted_text);
                        free(ciphered_text_pure);
                        return status;
                }

                join_rails(rails, deciphered_text, ciphered_text_len_pure, key);

                for (i = 0; i < key; ++i) {
                        free(rails[i]);
                }
                free(rails);
                free(adjusted_text);

                deciphered_text[ciphered_text_len_pure] = '\0';
        }

        free(ciphered_text_pure);
        return SUCCESS;
}

/**
 * Calculates the number of empty spaces in the last diagonal
 * @param test_length The length of the pure text
 * @param rails The number of rails used
 * @return Returns the number of rails that need padding
 */
int calculate_diagonals(int text_length, int rails)
{
        int denominator;
        int y = 0;
        while (text_length >= rails + ((rails - 1) * x)) {
                ++x;
        }
        denominator = rails + ((rails - 1) * x);
        while ((text_length + y) / denominator != 1) {
                ++(y);
        }
        return y;
}

/**
 * Deletes placeholders from 'adjusted_text'
 * @param adjusted_text The array to be checked for placeholders
 * @param is_placeholder An array containing the positions of the placeholders (1 if placeholder, 0 else)
 */
void remove_placeholders(char adjusted_text[], char is_placeholder[])
{
        int i, j = 0;

        for (i = 0; adjusted_text[i] != '\0'; ++i) {
                if (adjusted_text[i] != 'x' || is_placeholder[i] == '0') {
                        adjusted_text[j++] = adjusted_text[i];
                }
        }

        adjusted_text[j] = '\0';
}

/**
 * Splits 'ciphered_text_pure' into the rail segments and fills 'ciphered_rails' accordingly
 * @param ciphered_rails 2D array to be filled with the rails
 * @param ciphered_text_pure String containing the ciphered text only with alphanumeric characters
 * @param outer_rails_len The number of characters in the first and last rail
 * @param inter_rails_len The number of characters in the rails between the first and the last rail
 * @param key The number of rails to be used
 * @return Returns whether or not the memory allocation through 'malloc' and 'realloc' was successful
 */
int fill_cipher_rails(char*** ciphered_rails, char* ciphered_text_pure, int outer_rails_len, int inter_rails_len, int key)
{
        int i;
        int pure_text_index = 0;

        (*ciphered_rails) = malloc(key * sizeof(char*));
        if (*ciphered_rails == NULL) {
                return MALLOC_ERROR;
        }

        (*ciphered_rails)[0] = malloc((outer_rails_len + 1) * sizeof(char));
        if ((*ciphered_rails)[0] == NULL) {
                return MALLOC_ERROR;
        }

        (*ciphered_rails)[key - 1] = malloc((outer_rails_len + 1) * sizeof(char));
        if ((*ciphered_rails)[key - 1] == NULL) {
                return MALLOC_ERROR;
        }

        for (i = 1; i < key - 1; ++i) {
                (*ciphered_rails)[i] = malloc((inter_rails_len + 1) * sizeof(char));
                if ((*ciphered_rails)[i] == NULL) {
                        return MALLOC_ERROR;
                }
        }

        (*ciphered_rails)[0][0] = '\0';
        memcpy((*ciphered_rails)[0], ciphered_text_pure, outer_rails_len);
        (*ciphered_rails)[0][outer_rails_len] = '\0';
        pure_text_index += outer_rails_len;
        for (i = 1; i < key - 1; ++i) {
                memcpy((*ciphered_rails)[i], ciphered_text_pure + pure_text_index, inter_rails_len);
                (*ciphered_rails)[i][inter_rails_len] = '\0';
                pure_text_index += inter_rails_len;
        }

        memcpy((*ciphered_rails)[key - 1], ciphered_text_pure + pure_text_index, outer_rails_len);
        (*ciphered_rails)[key - 1][outer_rails_len] = '\0';
        return SUCCESS;
}


/**
 * Puts the contents of 'ciphered_rails' into 'deciphered_text' in rail-fence manners
 * @param ciphered_rails Array of strings filled with the different rails of the ciphered text
 * @param deciphered_text Destination of string put together of rails
 * @param ciphered_text_len Length of the pure cipher text
 * @param key Key used to cipher text
 */
void join_rails(char** ciphered_rails, char deciphered_text[], int ciphered_text_len, int key)
{
        int i;
        int rail = 0;
        int rail_char_index_outer = 0;
        int rail_char_index_inter = 0;
        int bool_rail_increment = 1;
        for (i = 0; i < ciphered_text_len; ++i) {
                if (rail == 0 || rail == key - 1) {
                        deciphered_text[i] = ciphered_rails[rail][rail_char_index_outer];
                        if (bool_rail_increment == 1) {
                                if (rail == key - 1) {
                                        bool_rail_increment = 0;
                                        ++rail_char_index_outer;
                                        --rail;
                                } else {
                                        ++rail;
                                }
                        } else {
                                if (rail == 0) {
                                        bool_rail_increment = 1;
                                        ++rail;
                                } else {
                                        --rail;
                                }
                        }
                } else {
                        deciphered_text[i] = ciphered_rails[rail][rail_char_index_inter];
                        if ((bool_rail_increment && rail == key - 2) || (!bool_rail_increment && rail == 1)) {
                                ++rail_char_index_inter;
                        }
                        (bool_rail_increment) ? (++rail) : (--rail);
                }
        }
        deciphered_text[i] = '\0';
}
