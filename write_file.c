#include "read_input.h"
#include "error_codes.h"

int print_to_file(char output[], char filename[])
{
        FILE *file;
        file = fopen(filename, "w");

        if (file == NULL) {
                return FILE_NOT_FOUND;
        }

        fprintf(file, "%s", output);

        fclose(file);
        return WRITE_SUCCESS;
}
