#include "lanetrotro.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    print_banner();

    if (argc != 2)
    {
        printf("Please provide an Obsidian canva file.\n");
        return 1;
    }

    char *file_path = argv[1];

    FILE *file_obj = fopen(file_path, "r");

    if (file_obj == NULL)
    {
        printf("Failed to open file.\n");
        return 1;
    }

    printf("Target file: %s\n", file_path);

    return 0;
}