#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int is_ip_address(char *text)
{
    if (text == NULL)
        return 0;

    int dots = 0;

    char *ptr = strtok(text, ".");

    while (ptr)
    {
        if (*ptr == '\0' || !isdigit(ptr[0]))
            return 0;

        int n = atoi(ptr);

        if (!(0 <= n && n < 256))
            return 0;

        ptr = strtok(NULL, ".");
        dots++;
    }

    return dots == 4;
}
