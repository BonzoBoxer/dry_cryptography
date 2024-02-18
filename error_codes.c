#include "error_codes.h"
#include "optics.h"


int check_error(int value) {
        int status;
        status = print_error(value);
        return status;
}

int print_error(int value)
{
        switch(value) {
                case (INVALID_INPUT):
                        printf(RED"\n\n\t*Ungültige Texteingabe!*"COLOR_RESET);
                        return 0;
                case (INVALID_KEY):
                        printf(RED"\n\n\t*Ungültiger Schlüssel!*\n\n"COLOR_RESET);
                        return 0;
                case (MALLOC_ERROR):
                        printf("\n\tMALLOC_ERROR (%i)", MALLOC_ERROR);
                        delay(5);
                        return MALLOC_ERROR;
                case (NO_KEY):
                        printf("\n\tNO_KEY (%i)", NO_KEY);
                        delay(5);
                        return NO_KEY;
                case (FILE_NOT_FOUND):
                        return 0;
                default:
                        return value;
        }
}
