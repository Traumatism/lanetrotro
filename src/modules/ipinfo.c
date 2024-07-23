#include "../lib/module.h"

int ipinfo_run(char *text)
{
    return 1;
}

int ipinfo_validator(char *text)
{
    return 1;
}

Module ipinfo_module = {
    .name = "IPInfo",
    .module_valiator_func = ipinfo_validator,
    .module_run_func = ipinfo_run,
};