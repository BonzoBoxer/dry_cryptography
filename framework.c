#include "optics.h"
#include "read_input.h"
#include "error_codes.h"
#include "transposition.h"
#include "caesar.h"
#include "vigenere.h"
#include "polybios.h"
#include "frequency_analysis.h"
#include "shift_e.h"

int application(void);
int check_file_ending(char filename[]);
int fa_editor(char input[], char output[]);

int method = UNKNOWN, direction = UNKNOWN, input_kind = UNKNOWN;
char* key_characters = NULL;

int main(void) {
        application();
        return 0;
}

int application(void) {
        char* c = NULL;
        char* m = NULL; /*Method*/
        char* input = NULL;
        char* output = NULL;
        char* input_formatted = NULL;
        char* output_formatted = NULL;
        char* fa_temp = NULL; /*Output für Buchstabeneditor*/
        char* filename = NULL;
        int key = UNKNOWN;
        int status;
        int quit_flag = 0;
        int file_output_flag = 0;
        int input_status;
        int current_width;
        int clear_status;
        time(NULL);
        print_intro();
        key_characters = malloc((strlen(KEY_UNKNOWN) + 1) * sizeof(char));
        if (key_characters == NULL) {
                print_tabs(1);
                printf("\tERROR %i: Fehler bei der Speicherallokation\n", MALLOC_ERROR);
                delay(5);
        }
        strcpy(key_characters, KEY_UNKNOWN);
        print_tabs(4);
        printf(BOLD"DRY"RESET_TXT_ATTRIBUTES"CRYPTOGRAPHY\n\n\n\tist ein Programm zur Ver- und Entschlüsselung"
               " von Texten.\n\tFolgende Verschlüsselungsverfahren werden"
               " unterstützt:\n\n"BOLD"\t\tGartenzaun-Methode\t    Cäsar-Chiffre\n\n"
               "\t\t Vigenère-Chiffre\t   Polybios-Chiffre"RESET_TXT_ATTRIBUTES"\n\n");
        printf("\tIst der Schlüssel eines monoalphabetisch substituierten Textes \n\tunbekannt, so kann mittels"
               ""BOLD" Häufigkeitsanalyse"RESET_TXT_ATTRIBUTES" eine mögliche \n\tEntschlüsselung gefunden werden.\n\n");
        printf("\tDie Eingabe und Ausgabe des Textes ist über die Kommandozeile sowie\n\tüber eine Textdatei möglich.\n"
               "\tUnterstützt werden die standard ASCII Zeichen.\n\n");
        printf("\tUm von "BOLD"Vorne zu beginnen"RESET_TXT_ATTRIBUTES", geben Sie 'r' in die Kommandozeile ein.\n\n");
        printf("\tUm das "BOLD"Programm zu beenden"RESET_TXT_ATTRIBUTES", geben Sie 'q' in die Kommandozeile ein.\n\n");
        printf("\tDrücken Sie ENTER um loszulegen!\n\t");
        read_line(&c);
        if (*c == 'q') {
                quit_flag = 1;
        }
        while(1) {
                output = NULL;
                method = UNKNOWN;
                direction = UNKNOWN;
                input_kind = UNKNOWN;
                key = UNKNOWN;
                strcpy(key_characters, KEY_UNKNOWN);
                file_output_flag = 0;
                clear_status = clear_running(method, direction, input_kind, key_characters);
                if (check_error(clear_status) < 0) {
                        break;
                }
                if (quit_flag) {
                        break;
                }
                printf("\n\n\n\n\tVerschlüsselungsverfahren wählen:\n\n");
                printf(BOLD"\tGartenzaun-Methode:"RESET_TXT_ATTRIBUTES"\t\t\t   'g'\n\t"BOLD"Cäsar-Chiffre mit höherer Sicherheit:"RESET_TXT_ATTRIBUTES"      's'\n\t"
                       BOLD "Cäsar-Chiffre mit höherer Kompatibilität:"RESET_TXT_ATTRIBUTES"  'c'\n\t"
                       BOLD"Vigenère-Chiffre:"RESET_TXT_ATTRIBUTES"\t\t\t   'v'\n\t"BOLD"Polybios-Chiffre:"RESET_TXT_ATTRIBUTES"\t\t\t   'p'\n\t"
                       BOLD"Häufigkeitsanalyse:"RESET_TXT_ATTRIBUTES"\t\t\t   'h'\n\n\tEingabe: ");
                input_status = 1;
                while (input_status) {
                        status = read_line(&m);
                        if (check_error(status) < 0) {
                                m = "q";
                                break;
                        }
                        if (!strcmp(m, "g")) {
                                method = RFC;
                                break;
                        } else if (!strcmp(m, "s")) {
                                method = SCC;
                                break;
                        } else if (!strcmp(m, "c")) {
                                method = CCC;
                                break;
                        } else if (!strcmp(m, "v")) {
                                method = VC;
                                break;
                        } else if (!strcmp(m, "p")) {
                                method = PC;
                                break;
                        } else if (!strcmp(m, "h")) {
                                method = FA;
                                break;
                        } else if (!strcmp(m, "q")) {
                                break;
                        } else if (!strcmp(m, "r")) {
                                break;
                        } else {
                                printf("\a");
                                clear_status = clear_running(method, direction, input_kind, key_characters);
                                if (check_error(clear_status) < 0) {
                                        m = "q";
                                        break;
                                }
                                printf("\n\n\n\n\tVerschlüsselungsverfahren wählen:\n\n");
                                printf(BOLD"\tGartenzaun-Methode:"RESET_TXT_ATTRIBUTES"\t\t\t   'g'\n\t"BOLD"Cäsar-Chiffre mit höherer Sicherheit:"RESET_TXT_ATTRIBUTES"      's'\n\t"
                                       BOLD "Cäsar-Chiffre mit höherer Kompatibilität:"RESET_TXT_ATTRIBUTES"  'c'\n\t"
                                       BOLD"Vigenère-Chiffre:"RESET_TXT_ATTRIBUTES"\t\t\t   'v'\n\t"BOLD"Polybios-Chiffre:"RESET_TXT_ATTRIBUTES"\t\t\t   'p'\n\t"
                                       BOLD"Häufigkeitsanalyse:"RESET_TXT_ATTRIBUTES""
                                       "\t\t\t   'h'\n\n\t"RED"*Nicht unterstützte Eingabe*"RESET_TXT_ATTRIBUTES
                                       "\n\n\tBitte wählen Sie eine gültige Methode!\n\tEingabe: ");
                        }
                }
                input_status = 1;

                if (!strcmp(m, "q")) {
                        break;
                } else if (!strcmp(m, "r")) {
                        continue;
                }
                clear_status = clear_running(method, direction, input_kind, key_characters);
                if (check_error(clear_status) < 0) {
                        break;
                }

                if (strcmp(m, "h")) {
                        printf("\n\n\n\tVerschlüsselungsrichtung wählen:\n\n\t"
                               BOLD"Verschlüsselung:"RESET_TXT_ATTRIBUTES" 'v'\n\t"
                               BOLD"Entschlüsselung:"RESET_TXT_ATTRIBUTES" 'e'\n\n\t"
                               "Eingabe: ");
                        while (input_status) {
                                status = read_line(&c);
                                if (check_error(status) < 0) {
                                        c = "q";
                                }
                                if (!strcmp(c, "v")) {
                                        direction = ENCRYPT;
                                        break;
                                } else if (!strcmp(c, "e")) {
                                        direction = DECRYPT;
                                        break;
                                } else if (!strcmp(c, "q")) {
                                        break;
                                } else if (!strcmp(c, "r")) {
                                        break;
                                } else {
                                        printf("\a");
                                        clear_status = clear_running(method, direction, input_kind, key_characters);
                                        if (check_error(clear_status) < 0) {
                                                input_status = 0;
                                                c = "q";
                                                break;
                                        }
                                        printf("\n\n\n\tVerschlüsselungsrichtung wählen:\n\n\t"
                                               BOLD"Verschlüsselung:"RESET_TXT_ATTRIBUTES" 'v'\n\t"
                                               BOLD"Entschlüsselung:"RESET_TXT_ATTRIBUTES" 'e'\n\n\t"
                                               RED"*Nicht unterstützte Eingabe*"COLOR_RESET"\n\n\tBitte wählen "
                                               "Sie eine gültige Verschlüsselungsrichtung!\n\tEingabe: ");
                                }
                        }
                        if (!strcmp(c, "q")) {
                                break;
                        } else if (!strcmp(c, "r")) {
                                continue;
                        }
                        input_status = 1;
                } else {
                        direction = DECRYPT;
                }
                clear_status = clear_running(method, direction, input_kind, key_characters);
                if (check_error(clear_status) < 0) {
                        break;
                }
                printf("\n\n\tEingabeart wählen:\n\n\t"
                       BOLD"Textdatei:"RESET_TXT_ATTRIBUTES"     't'\n\t"
                       BOLD"Kommandozeile:"RESET_TXT_ATTRIBUTES" 'k'\n\n\tEingabe: ");
                while (input_status) {
                        status = read_line(&c);
                        if (check_error(status) < 0) {
                                c = "q";
                                break;
                        }
                        if (!strcmp(c, "t")) {
                                input_kind = TXT_FILE;
                                break;
                        } else if (!strcmp(c, "k")) {
                                input_kind = TERMINAL;
                                break;
                        } else if (!strcmp(c, "q")) {
                                break;
                        } else if (!strcmp(c, "r")) {
                                break;
                        } else {
                                printf("\a");
                                clear_status = clear_running(method, direction, input_kind, key_characters);
                                if (check_error(clear_status) < 0) {
                                        input_status = 0;
                                        *c = 'q';
                                        break;
                                }
                                printf("\n\n\tEingabeart wählen:\n\n\t"
                                       BOLD"Textdatei:"RESET_TXT_ATTRIBUTES"     't'\n\t"
                                       BOLD"Kommandozeile:"RESET_TXT_ATTRIBUTES" 'k'\n\n\t"
                                       RED"*Nicht unterstützte Eingabe*"COLOR_RESET"\n\n\tBitte wählen Sie eine"
                                       " gültige Eingabeart!\n\t"
                                       "Eingabe: ");
                        }
                }
                if (!strcmp(c, "q")) {
                        break;
                } else if (!strcmp(c, "r")) {
                        continue;
                }
                input_status = 1;
                if (input_kind == TXT_FILE) {
                        clear_status = clear_running(method, direction, input_kind, key_characters);
                        if (check_error(clear_status) < 0) {
                                break;
                        }
                        printf("\n\n\n\n\tBitte geben Sie den Dateinamen oder Pfad an: ");
                        status = read_line(&filename);
                        if (check_error(status) < 0) {
                                break;
                        }
                        if (!strcmp(filename, "q")) {
                                break;
                        } else if (!strcmp(filename, "r")) {
                                clear_status = clear_running(method, direction, input_kind, key_characters);
                                if (check_error(clear_status) < 0) {
                                        break;
                                }
                                continue;
                        }
                        input_status = read_file(&input, filename);
                        while (input_status < 0) {
                                printf("\a");
                                clear_status = clear_running(method, direction, input_kind, key_characters);
                                if (check_error(clear_status) < 0) {
                                        filename = "q";
                                        break;
                                }
                                check_error(input_status);
                                clear_status = clear_running(method, direction, input_kind, key_characters);
                                if (check_error(clear_status) < 0) {
                                        filename = "q";
                                        break;
                                }
                                printf("\n\n\t"RED"*Datei \"%s\" nicht gefunden!*"COLOR_RESET"\n\n\t"
                                       "Bitte geben Sie den Dateinamen oder Pfad an: ", filename);
                                status = read_line(&filename);
                                if (check_error(status) < 0) {
                                        filename = "q";
                                        break;
                                } else if (!strcmp(filename, "q")) {
                                        break;
                                } else if (!strcmp(filename, "r")) {
                                        break;
                                }
                                input_status = read_file(&input, filename);
                        }
                        input_status = 1;
                        if (!strcmp(filename, "q")) {
                                break;
                        } else if (!strcmp(filename, "r")) {
                                continue;
                        }
                } else if (input_kind == TERMINAL) {
                        clear_status = clear_running(method, direction, input_kind, key_characters);
                        if (check_error(clear_status) < 0) {
                                break;
                        }
                        printf("\n\n\n\n\tBitte geben Sie den Text ein: ");
                        status = read_line(&input);
                        if (check_error(status) < 0) {
                                break;
                        }
                        if (!strcmp(input, "q")) {
                                break;
                        } else if (!strcmp(input, "r")) {
                                continue;
                        }
                }
                if (method != FA) {
                        if (method == CCC && direction == DECRYPT) {
                                printf("\t"YELLOW"Bitte geben Sie den Schlüssel ein (sollte dieser nicht bekannt\n\tsein, "
                                       "geben Sie 'u' ein): ");
                                status = read_line(&key_characters);
                                printf(COLOR_RESET);
                                if (check_error(status) < 0) {
                                        break;
                                }
                                if (!strcmp(key_characters, "q")) {
                                        break;
                                } else if (!strcmp(key_characters, "r")) {
                                        break;
                                } else if (!strcmp(key_characters, "u")) {
                                        method = SE;
                                        strcpy(key_characters, KEY_UNKNOWN);
                                } else {
                                        key = atoi(key_characters);
                                }
                        } else {
                                printf("\t"YELLOW"Bitte geben Sie den Schlüssel ein: ");
                                status = read_line(&key_characters);
                                printf(COLOR_RESET);
                                if (check_error(status) < 0) {
                                        break;
                                }
                                if (!strcmp(key_characters, "q")) {
                                        break;
                                } else if (!strcmp(key_characters, "r")) {
                                        continue;
                                }
                                key = atoi(key_characters);
                        }
                }
                if (direction == ENCRYPT) {
                        clear_status = clear_running(method, direction, input_kind, key_characters);
                        if (check_error(clear_status) < 0) {
                                break;
                        }
                        output = (char *) malloc((strlen(input) + 1) * sizeof(char));
                        if (output == NULL) {
                                print_tabs(2);
                                printf("\tERROR %i: Fehler bei der Speicherallokation\n", MALLOC_ERROR);
                                delay(5);
                                break;
                        }
                        strcpy(output, "");
                        switch (method) {
                                case RFC:
                                        status = transposition_cipher(output, input, key);
                                        break;
                                case SCC:
                                        status = cs_encipher(key, input, output);
                                        break;
                                case CCC:
                                        status = compatible_caesar_cipher(input, output, key);
                                        break;
                                case VC:
                                        fill_tabula();
                                        status = encrypt_vigenere(input, key_characters, output);
                                        break;
                                case PC:
                                        output = realloc(output, (2 * strlen(input) + 1) * sizeof(char));
                                        if (output == NULL) {
                                                print_tabs(2);
                                                printf("\tERROR %i: Fehler bei der Speicherallokation\n", MALLOC_ERROR);
                                                delay(5);
                                                input_status = 0;
                                                break;
                                        }
                                        strcpy(output, "");
                                        status = encrypt_polybios(input, key_characters, output);
                                        break;
                        }
                        input_status = 1;
                        while (check_error(status) == 0) {
                                printf("\a");
                                if (status == INVALID_KEY) {
                                        printf("\t"YELLOW"Bitte geben Sie den Schlüssel ein: ");
                                        status = read_line(&key_characters);
                                        printf(COLOR_RESET);
                                        if (check_error(input_status) < 0) {
                                                key_characters = "q";
                                                break;
                                        }
                                        printf(COLOR_RESET);
                                        if (!strcmp(key_characters, "q") || !strcmp(key_characters, "r")) {
                                                break;
                                        }
                                        key = atoi(key_characters);
                                } else if (status == INVALID_INPUT && input_kind == TXT_FILE) {
                                        printf("\n\n\tDie angegebene Textdatei enthielt keinen lesbaren Inhalt!");
                                        printf("\n\n\tBitte geben Sie den Dateinamen oder Pfad an: ");
                                        input_status = read_line(&filename);
                                        if (check_error(input_status) < 0) {
                                                break;
                                        }
                                        if (!strcmp(filename, "q")) {
                                                key_characters = "q";
                                                break;
                                        } else if (!strcmp(filename, "r")) {
                                                clear_status = clear_running(method, direction, input_kind,
                                                                             key_characters);
                                                if (check_error(clear_status) < 0) {
                                                        break;
                                                }
                                                key_characters = "r";
                                                break;
                                        }
                                        input_status = read_file(&input, filename);
                                        while (input_status < 0) {
                                                clear_status = clear_running(method, direction, input_kind,
                                                                             key_characters);
                                                if (check_error(clear_status) < 0) {
                                                        filename = "q";
                                                        break;
                                                }
                                                check_error(input_status);
                                                printf("\n\n\t"RED"*Datei \"%s\" nicht gefunden!*"COLOR_RESET"\n\n\t"
                                                       "Bitte geben Sie den Dateinamen oder Pfad an: ", filename);
                                                input_status = read_line(&filename);
                                                if (check_error(input_status) < 0) {
                                                        filename = "q";
                                                        break;
                                                } else if (!strcmp(filename, "q")) {
                                                        break;
                                                } else if (!strcmp(filename, "r")) {
                                                        break;
                                                }
                                                input_status = read_file(&input, filename);
                                        }
                                        input_status = 1;
                                        if (!strcmp(filename, "q")) {
                                                break;
                                        } else if (!strcmp(filename, "r")) {
                                                continue;
                                        }
                                } else if (status == INVALID_INPUT && input_kind == TERMINAL) {
                                        printf("\n\n\tBitte geben Sie den Text ein: ");
                                        input_status = read_line(&input);
                                        if (check_error(input_status) < 0) {
                                                key_characters = "q";
                                                break;
                                        } else if (!strcmp(input, "q")) {
                                                key_characters = "q";
                                                break;
                                        } else if (!strcmp(input, "r")) {
                                                *key_characters = 'r';
                                                break;
                                        }
                                }
                                output = malloc((strlen(input) + 1) * sizeof(char));
                                if (output == NULL) {
                                        print_tabs(2);
                                        printf("\tERROR %i: Fehler bei der Speicherallokation\n", MALLOC_ERROR);
                                        delay(5);
                                        break;
                                }
                                strcpy(output, "");
                                switch (method) {
                                        case RFC:
                                                status = transposition_cipher(output, input, key);
                                                break;
                                        case SCC:
                                                status = cs_encipher(key, input, output);
                                                break;
                                        case CCC:
                                                status = compatible_caesar_cipher(input, output, key);
                                                break;
                                        case VC:
                                                fill_tabula();
                                                status = encrypt_vigenere(input, key_characters, output);
                                                break;
                                        case PC:
                                                output = realloc(output, (2 * strlen(input) + 1) * sizeof(char));
                                                if (output == NULL) {
                                                        print_tabs(2);
                                                        printf("\tERROR %i: Fehler bei der Speicherallokation\n",
                                                               MALLOC_ERROR);
                                                        delay(5);
                                                        input_status = 0;
                                                        break;
                                                }
                                                strcpy(output, "");
                                                status = encrypt_polybios(input, key_characters, output);
                                                break;
                                }
                                clear_status = clear_running(method, direction, input_kind, key_characters);
                                if (check_error(clear_status) < 0) {
                                        key_characters = "q";
                                        break;
                                }
                        }
                        if (!strcmp(key_characters, "q")) {
                                break;
                        } else if (!strcmp(key_characters, "r")) {
                                continue;
                        }
                } else if (direction == DECRYPT) {
                        clear_status = clear_running(method, direction, input_kind, key_characters);
                        if (check_error(clear_status) < 0) {
                                input_status = 0;
                                break;
                        }
                        output = (char *) malloc((strlen(input) + 1) * sizeof(char));
                        if (output == NULL) {
                                print_tabs(2);
                                printf("\tERROR %i: Fehler bei der Speicherallokation\n", MALLOC_ERROR);
                                delay(5);
                                break;
                        }
                        strcpy(output, "");
                        switch (method) {
                                case RFC:
                                        status = transposition_decipher(output, input, key);
                                        break;
                                case SCC:
                                        status = cs_decipher(key, input, output);
                                        break;
                                case CCC:
                                        status = compatible_caesar_decipher(input, output, key);
                                        break;
                                case VC:
                                        fill_tabula();
                                        status = decrypt_vigenere(input, key_characters, output);
                                        break;
                                case PC:
                                        status = decrypt_polybios(input, key_characters, output);
                                        break;
                                case FA:
                                        status = sort_frequency(input, output);
                                        break;
                                case SE:
                                        status = shift_e(input, output);
                                        break;
                        }
                        if (!input_status) {
                                break;
                        }
                        while (check_error(status) == 0) {
                                printf("\a");
                                if (status == INVALID_KEY) {
                                        if (method == SE) {
                                                printf("\t"YELLOW"Bitte geben Sie den Schlüssel ein (sollte dieser nicht bekannt\n\tsein, "
                                                       "geben Sie 'u' ein): ");
                                                status = read_line(&key_characters);
                                                printf(COLOR_RESET);
                                                if (check_error(status) < 0) {
                                                        key_characters = "q";
                                                        break;
                                                }
                                                if (!strcmp(key_characters, "q") || !strcmp(key_characters, "r")) {
                                                        break;
                                                } else if (!strcmp(key_characters, "u")) {
                                                        method = SE;
                                                        strcpy(key_characters, KEY_UNKNOWN);
                                                        break;
                                                } else {
                                                        key = atoi(key_characters);
                                                }
                                        } else {
                                                printf("\t"YELLOW"Bitte geben Sie einen gültigen Schlüssel ein: ");
                                                status = read_line(&key_characters);
                                                printf(COLOR_RESET);
                                                if (check_error(status) < 0) {
                                                        key_characters = "q";
                                                        break;
                                                }
                                                if (!strcmp(key_characters, "q") || !strcmp(key_characters, "r")) {
                                                        break;
                                                }
                                                key = atoi(key_characters);
                                        }
                                } else if (status == INVALID_INPUT && input_kind == TXT_FILE) {
                                        printf("\n\n\tDie angegebene Textdatei enthielt keinen lesbaren Inhalt!");
                                        printf("\n\n\tBitte geben Sie den Dateinamen oder Pfad an: ");
                                        status = read_line(&filename);
                                        if (check_error(status) < 0) {
                                                break;
                                        } else if (!strcmp(filename, "q")) {
                                                key_characters = "q";
                                                break;
                                        } else if (!strcmp(filename, "r")) {
                                                clear_status = clear_running(method, direction, input_kind,
                                                                             key_characters);
                                                if (check_error(clear_status) < 0) {
                                                        break;
                                                }
                                                key_characters = "r";
                                                break;
                                        }
                                        input_status = read_file(&input, filename);
                                        while (input_status < 0) {
                                                clear_status = clear_running(method, direction, input_kind,
                                                                             key_characters);
                                                if (check_error(clear_status) < 0) {
                                                        filename = "q";
                                                        break;
                                                }
                                                check_error(input_status);
                                                printf("\n\n\t"RED"*Datei \"%s\" nicht gefunden!*"COLOR_RESET"\n\n\t"
                                                       "Bitte geben Sie den Dateinamen oder Pfad an: ", filename);
                                                status = read_line(&filename);
                                                if (check_error(status) < 0) {
                                                        filename = "q";
                                                        break;
                                                } else if (!strcmp(filename, "q")) {
                                                        break;
                                                } else if (!strcmp(filename, "r")) {
                                                        break;
                                                }
                                                input_status = read_file(&input, filename);
                                        }
                                        input_status = 1;
                                        if (!strcmp(filename, "q")) {
                                                break;
                                        } else if (!strcmp(filename, "r")) {
                                                continue;
                                        }
                                } else if (status == INVALID_INPUT && input_kind == TERMINAL) {
                                        printf("\n\n\tBitte geben Sie den Text ein: ");
                                        status = read_line(&input);
                                        if (check_error(status) < 0) {
                                                key_characters = "q";
                                                break;
                                        } else if (!strcmp(input, "q")) {
                                                key_characters = "q";
                                                break;
                                        } else if (!strcmp(input, "r")) {
                                                key_characters = "r";
                                                break;
                                        }
                                }
                                output = (char *) malloc((strlen(input) + 1) * sizeof(char));
                                if (output == NULL) {
                                        print_tabs(2);
                                        printf("\tERROR %i: Fehler bei der Speicherallokation\n", MALLOC_ERROR);
                                        delay(5);
                                        break;
                                }
                                strcpy(output, "");
                                switch (method) {
                                        case RFC:
                                                status = transposition_decipher(output, input, key);
                                                break;
                                        case SCC:
                                                status = cs_decipher(key, input, output);
                                                break;
                                        case CCC:
                                                status = compatible_caesar_decipher(input, output, key);
                                                break;
                                        case VC:
                                                fill_tabula();
                                                status = decrypt_vigenere(input, key_characters, output);
                                                break;
                                        case PC:
                                                status = decrypt_polybios(input, key_characters, output);
                                                break;
                                        case FA:
                                                status = sort_frequency(input, output);
                                                break;
                                        case SE:
                                                status = shift_e(input, output);
                                                break;
                                }
                                clear_status = clear_running(method, direction, input_kind, key_characters);
                                if (check_error(clear_status) < 0) {
                                        key_characters = "q";
                                        break;
                                }
                        }
                        if (!strcmp(key_characters, "q")) {
                                break;
                        } else if (!strcmp(key_characters, "r")) {
                                continue;
                        }
                } else if (!strcmp(c, "q")) {
                        break;
                }
                printf("\n\n\n\tMöchten Sie das Ergebnis in einer Textdatei speichern? (y/n)\n\tEingabe: ");
                while (input_status) {
                        status = read_line(&c);
                        if (check_error(status) < 0) {
                                c = "q";
                                break;
                        }
                        if (!strcmp(c, "y")) {
                                input_status = 0;
                                clear_status = clear_running(method, direction, input_kind, key_characters);
                                if (check_error(clear_status) < 0) {
                                        c = "q";
                                        break;
                                }
                                printf("\n\n\n\tBitte geben Sie den Dateinamen oder Pfad an.\n\tEingabe: ");
                                status = read_line(&filename);
                                if (check_error(status) < 0) {
                                        c = "q";
                                        break;
                                } else if (!strcmp(filename, "q")) {
                                        c = "q";
                                        break;
                                } else if (!strcmp(filename, "r")) {
                                        c = "r";
                                        break;
                                }
                                status = print_to_file(output, filename);
                                while (check_error(status) == 0) {
                                        printf("\a");
                                        clear_status = clear_running(method, direction, input_kind, key_characters);
                                        if (check_error(clear_status) < 0) {
                                                input_status = 0;
                                                c = "q";
                                                break;
                                        }
                                        printf("\n\n\t"RED"*Datei \"%s\" nicht gefunden!*"COLOR_RESET"\n\n\t"
                                               "Bitte geben Sie den Dateinamen oder Pfad an.\n\tEingabe: ", filename);
                                        status = read_line(&filename);
                                        if (check_error(status) < 0) {
                                                filename = "q";
                                        }
                                        if (!strcmp(filename, "q")) {
                                                input_status = 0;
                                                c = "q";
                                                break;
                                        } else if (!strcmp(filename, "r")) {
                                                input_status = 0;
                                                c = "r";
                                                break;
                                        }
                                        status = print_to_file(output, filename);
                                }
                                file_output_flag = 1;
                        } else if (!strcmp(c, "n") || !strcmp(c, "q") || !strcmp(c, "r")) {
                                input_status = 0;
                        } else {
                                printf("\a");
                                clear_status = clear_running(method, direction, input_kind, key_characters);
                                if (check_error(clear_status) < 0) {
                                        input_status = 0;
                                        c = "q";
                                        break;
                                }
                                printf("\n\n\n\tMöchten Sie das Ergebnis in einer Textdatei speichern? (y/n)\n\n\t"
                                       RED"*Nicht unterstützte Eingabe!*"COLOR_RESET"\n\n\tEingabe: ");
                        }
                }
                input_formatted = malloc((strlen(input) + 1) * sizeof(char));
                if (input_formatted == NULL) {
                        print_tabs(2);
                        printf("\tERROR %i: Fehler bei der Speicherallokation\n", MALLOC_ERROR);
                        delay(5);
                        break;
                }
                strcpy(input_formatted, "");
                output_formatted = malloc((strlen(output) + 1) * sizeof(char));
                if (output_formatted == NULL) {
                        print_tabs(2);
                        printf("\tERROR %i: Fehler bei der Speicherallokation\n", MALLOC_ERROR);
                        delay(5);
                        break;
                }
                strcpy(output_formatted, "");
                status = add_line_breaks(input, &input_formatted, MAXIMUM_TEXT_WIDTH);
                if (check_error(status) < 0) {
                        delay(5);
                        break;
                }
                status = add_line_breaks(output, &output_formatted, MAXIMUM_TEXT_WIDTH);
                if (check_error(status) < 0) {
                        delay(5);
                        break;
                }
                clear_status = clear_running(method, direction, input_kind, key_characters);
                if (check_error(clear_status) < 0) {
                        c = "q";
                }
                if (!strcmp(c, "q")) {
                        break;
                } else if (!strcmp(c, "r")) {
                        continue;
                }
                printf(BOLD"\n\tErgebnis:\n\n"RESET_TXT_ATTRIBUTES);
                if (strlen(output) > 450) {
                        print_left_aligned(output_formatted);
                } else {
                        print_encrypt_animation(input_formatted, output_formatted, method, direction, input_kind, key_characters);
                }
                if (method == FA) {
                        print_fre_legend_short();
                        print_left_aligned("Geben Sie 't' ein, um die Tabelle zu expandieren.");
                        printf("\n\t\t\t\t"BOLD"oder"RESET_TXT_ATTRIBUTES);
                        printf("\n\tGeben Sie 'e' ein, um den Buchstabeneditor zu starten.\n");
                        if (file_output_flag) {
                                if (check_file_ending(filename)) {
                                        printf("\n\tDas Ergebnis wurde in '%s' gespeichert.\n", filename);
                                } else {
                                        printf("\n\tDas Ergebnis konnte ggf. "BOLD"NICHT"RESET_TXT_ATTRIBUTES" in '%s' gespeichert werden.\n",
                                               filename);
                                }
                        }
                        printf("\n\tDrücken Sie ENTER, um einen weiteren Text zu ver- oder entschlüsseln.\n\tGeben Sie"
                               " 'q' ein, um das Programm zu beenden.\n\t");
                        status = read_line(&c);
                        if (check_error(status) < 0) {
                                break;
                        }
                        if (!strcmp(c, "q")) {
                                break;
                        }
                }
                if (method == FA && !strcmp(c, "t")) {
                        clear_status = clear_running(method, direction, input_kind, key_characters);
                        if (check_error(clear_status) < 0) {
                                break;
                        }
                        printf(BOLD"\n\tErgebnis:\n\n"RESET_TXT_ATTRIBUTES);
                        print_left_aligned(output);
                        if (get_terminal_height() < MIN_TERMINAL_HEIGHT_FRE_LEGEND) {
                                current_width = get_terminal_width();
                                SET_SIZE_FRE_LEGEND(current_width);
                        }
                        print_fre_legend();
                        if (file_output_flag) {
                                if (check_file_ending(filename)) {
                                        printf("\n\tDas Ergebnis wurde in '%s' gespeichert.", filename);
                                } else {
                                        printf("\n\tDas Ergebnis konnte ggf. "BOLD"NICHT"RESET_TXT_ATTRIBUTES" in '%s' gespeichert werden.",
                                               filename);
                                }
                        }
                        printf("\n\n\tDrücken Sie ENTER, um einen weiteren Text zu ver- oder entschlüsseln.\n\tGeben Sie"
                               " 'q' ein, um das Programm zu beenden.\n\t");
                        status = read_line(&c);
                        if (check_error(status) < 0) {
                                break;
                        }
                        if (!strcmp(c, "q")) {
                                break;
                        }
                        clear_status = clear_running(method, direction, input_kind, key_characters);
                        if (check_error(clear_status) < 0) {
                                break;
                        }
                } else if (method == FA && !strcmp(c, "e")) {
                        fa_temp = malloc((strlen(output) + 1) * sizeof(char));
                        if (fa_temp == NULL) {
                                break;
                        }
                        strcpy(fa_temp, "");
                        status = fa_editor(output, fa_temp);
                        if (status <= 0) {
                                break;
                        }
                        free(fa_temp);
                } else if (method == FA && (strcmp(c, "t") && strcmp(c, "e"))) {
                        if (check_error(status) < 0) {
                                break;
                        }
                        if (!strcmp(c, "q")) {
                                break;
                        }
                        clear_status = clear_running(method, direction, input_kind, key_characters);
                        if (check_error(clear_status) < 0) {
                                break;
                        }
                } else {
                        if (file_output_flag) {
                                if (check_file_ending(filename)) {
                                        printf("\n\n\n\tDas Ergebnis wurde in '%s' gespeichert.", filename);
                                } else {
                                        printf("\n\n\n\tDas Ergebnis konnte ggf. "BOLD"NICHT"RESET_TXT_ATTRIBUTES" in '%s' gespeichert werden.",
                                               filename);
                                }
                        }
                        printf("\n\n\tDrücken Sie ENTER, um einen weiteren Text zu ver- oder entschlüsseln.\n\tGeben Sie"
                                " 'q' ein, um das Programm zu beenden.\n\t");
                        status = read_line(&c);
                        if (check_error(status) < 0) {
                                break;
                        }
                        if (!strcmp(c, "q")) {
                                break;
                        }
                        clear_status = clear_running(method, direction, input_kind, key_characters);
                        if (check_error(clear_status) < 0) {
                                break;
                        }
                }
        }
        print_outro();
        free(c);
        free(m);
        free(input);
        free(output);
        free(input_formatted);
        free(output_formatted);
        free(key_characters);
        free(filename);
        return 0;
}

/**
 * Checks if the file ending of 'filename' is '.txt'
 * @param filename A string containing the filename
 * @return Returns whether or not the file ending is '.txt'
 */
int check_file_ending(char filename[])
{
        int i, j = 3;
        char ending[5] = {0};
        int bound = strlen(filename) - 5;
        ending[4] = '\0';
        for (i = strlen(filename) - 1; i > bound; --i) {
                ending[j] = filename[i];
                --j;
        }
        if (strcmp(ending, ".txt") == 0) {
                return 1;
        } else {
                return 0;
        }
}

/**
 * Editor for changing the result of the frequency_analysis
 * @param input String filled with original frequency analysis result
 * @param output Empty string to be filled with changed input string
 * @return Returns if malloc was successful and how the program should resume after this function is called
 */
int fa_editor(char input[], char output[])
{
        char* temp = NULL;
        char* orig_letter = NULL;
        char* new_letter = NULL;
        char* c = NULL;
        int input_status;
        int status;
        int first_run = 1;
        int error = 0;

        temp = malloc((strlen(input) + 1) * sizeof(char));
        if (temp == NULL) {
                return MALLOC_ERROR;
        }
        strcpy(temp, "");
        while (1) {
                clear_running(method, direction, input_kind, key_characters);
                if (error) {
                        error = 0;
                        printf(RED"\n\tBitte geben Sie nur "BOLD"einen Buchstaben "RESET_TXT_ATTRIBUTES RED"ein!\n\n"COLOR_RESET);
                } else {
                        printf("\n\n\n");
                }
                if (first_run) {
                        print_left_aligned(input);

                } else {
                        print_left_aligned(temp);
                }
                printf("\n\n\tGeben Sie den Buchstaben ein, den Sie verändern möchten: ");
                input_status = read_line(&orig_letter);
                if (input_status < 0) {
                        free(temp);
                        return input_status;
                }
                if (first_run) {
                        if ((strchr(input, toupper(*orig_letter)) == NULL) && (strchr(input, tolower(*orig_letter)) == NULL)) {
                                printf("\a");
                                error = 1;
                                free(orig_letter);
                                continue;
                        } else if (strlen(orig_letter) > 1) {
                                printf("\a");
                                error = 1;
                                free(orig_letter);
                                continue;
                        }
                } else {
                        if ((strchr(temp, toupper(*orig_letter)) == NULL) && (strchr(temp, tolower(*orig_letter)) == NULL)) {
                                printf("\a");
                                error = 1;
                                free(orig_letter);
                                continue;
                        } else if (strlen(orig_letter) > 1) {
                                printf("\a");
                                error = 1;
                                free(orig_letter);
                                continue;
                        }
                }
                printf("\n\tGeben Sie den neuen Buchstaben ein: ");
                input_status = read_line(&new_letter);
                if (input_status < 0) {
                        free(orig_letter);
                        free(temp);
                        return input_status;
                }
                if (strlen(new_letter) > 1) {
                        printf("\a");
                        error = 1;
                        free(orig_letter);
                        free(new_letter);
                        free(temp);
                        continue;
                }
                if (!isalpha(*orig_letter) || !isalpha(*new_letter)) {
                        printf("\a");
                        error = 1;
                        free(orig_letter);
                        free(new_letter);
                        continue;
                }
                clear_running(method, direction, input_kind, key_characters);

                printf("\n\n\tVeränderung: %c -> %c\n\n", toupper(*orig_letter), toupper(*new_letter));
                if (first_run) {
                        status = change_letters(output, input, *orig_letter, *new_letter);
                } else {
                        status = change_letters(output, temp, *orig_letter, *new_letter);
                }
                if (!check_error(status)) {
                        free(orig_letter);
                        free(new_letter);
                        free(temp);
                        return status;
                }
                print_left_aligned(output);
                strcpy(temp, output);
                printf("\n\n\tGeben Sie 'r' ein, um den Editor zu verlassen.");
                printf("\n\tGeben Sie 'q' ein, um das Programm zu beenden.");
                printf("\n\tDrücken Sie ENTER um einen weiteren Buchstaben zu verändern.\n\t");
                input_status = read_line(&c);
                if (input_status < 0) {
                        return input_status;
                }
                first_run = 0;
                switch (*c) {
                        case 'r':
                                free(orig_letter);
                                free(new_letter);
                                free(c);
                                free(temp);
                                return SUCCESS;
                        case 'q':
                                free(orig_letter);
                                free(new_letter);
                                free(c);
                                free(temp);
                                return EXIT;
                }
        }
}
