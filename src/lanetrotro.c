#include "lanetrotro.h"

#include "../external/cJSON/cJSON.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    print_banner();

    if (argc != 2)
    {
        logger_error("Please provide an Obsidian canva file.");
        return 1;
    }

    char *file_path = argv[1];
    FILE *fp;

    if (!(fp = fopen(file_path, "r")))
    {
        logger_error("Failed to open file.");
        return 1;
    }

    logger_info("Target file: %s", file_path);

    fseek(fp, 0L, SEEK_END); /* Go to file end */
    int buffer_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET); /* Go to file start */

    char buffer[buffer_size];

    int c;
    int i = 0;

    while ((c = fgetc(fp)) != EOF)
    {
        buffer[i] = c;
        i++;
    }

    buffer[buffer_size] = '\0';

    if (ferror(fp))
    {
        logger_error("Error while reading file content.");
        return 1;
    }

    fclose(fp);

    return 0;
}