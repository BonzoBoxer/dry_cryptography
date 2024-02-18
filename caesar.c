#include "caesar.h"
#include "error_codes.h"

/*
//Encipher Funktionsweise: erwartet input feld mit zu verschlüsselndem text, schlüssel (verschiebungsparameter), zweites feld zum abspeichern des veränderten Textes
// Decipher analog
// arbeitet mit feldern deren Größe vordefiniert ist
// kleinster Schlüssel 1 | größter Schlüssel 94 (denn 95 wäre wieder 1)
// funktionen nutzen (int) error values -> negative Zahlen bedeuten fehler
// wenn nicht druckbare ascii zeichen übergeben werden werden diese zu leerzeichen umgewandelt
*/

int cs_encipher(int key, char input[], char encipher_text[])
{
        int i;
        if (control_key(key) == INVALID_KEY) {
                return INVALID_KEY;
        }
        if (strlen(input) < 1) {
                return INVALID_INPUT;
        }
        for (i = 0; input[i] != '\0'; ++i) {
                if (input[i] >= LOW_BORDER && input[i] <= UPPER_BORDER) {
                        encipher_text[i] = ((input[i] - LOW_BORDER + key + DIFFERENCE_BORDER) % DIFFERENCE_BORDER) + LOW_BORDER;
                } else if (input[i] == '\n') {
                        encipher_text[i] = '\n';
                } else {
                        encipher_text[i] = ' ';
                }
        }
        encipher_text[i] = '\0';
        return ENCIPHER_SUCCESS;
}

int cs_decipher(int key, char input[], char decipher_text[])
{
        int i;
        if (control_key(key) == INVALID_KEY) {
                return INVALID_KEY;
        }
        if (strlen(input) < 1) {
                return INVALID_INPUT;
        }
        for (i = 0; input[i] != '\0'; ++i) {
                if (input[i] >= LOW_BORDER && input[i] <= UPPER_BORDER) {
                        decipher_text[i] = ((input[i] - LOW_BORDER - key + DIFFERENCE_BORDER) % DIFFERENCE_BORDER) + LOW_BORDER;
                } else if (input[i] == '\n') {
                        decipher_text[i] = '\n';
                } else {
                        decipher_text[i] = ' '; /*non printable char are handled like space*/
                }
        }
        decipher_text[i] = '\0';
        return DECIPHER_SUCCESS;
}


int control_key(int key)
{
        if (key < LOW_KEY || key > UPPER_KEY) {
                return INVALID_KEY;
        }
        return VALID_KEY;
}
