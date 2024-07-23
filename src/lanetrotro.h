#include "../external/cJSON/cJSON.h"

#define print_banner() ({                            \
    printf(                                          \
        "\n   /\\          /\\  "                    \
        "\n  ( \\\\        // ) "                    \
        "\n   \\ \\\\      // /  "                   \
        "\n    \\_\\\\||||//_/   "                   \
        "\n     \\/ _  _ \\     lanetrotro"          \
        "\n    \\/|(O)(O)|     "                     \
        "\n/_\\/  \\      /     "                    \
        "\n//     |____|      github.com/traumatism" \
        "\n|     /      \\     "                     \
        "\n|     \\ 0  0 /     "                     \
        "\nU    / \\_//_/      \n\n\n");             \
});

/* Log an info */

#define logger_info(...) ({ \
    printf("INFO: ");       \
    printf(__VA_ARGS__);    \
    printf("\n");           \
});

/* Log a success */

#define logger_success(...) ({ \
    printf("OKAY: ");          \
    printf(__VA_ARGS__);       \
    printf("\n");              \
});

/* Log a warning */

#define logger_warn(...) ({ \
    printf("WARN: ");       \
    printf(__VA_ARGS__);    \
    printf("\n");           \
});

/* Log an error message.*/

#define logger_error(...) ({ \
    printf("OOPS: ");        \
    printf(__VA_ARGS__);     \
    printf("\n");            \
});