#include "../lib/module.h"
#include "../lib/validate.h"

int ipinfo_validate(char *text)
{
    return is_ip_address(text);
}

int ipinfo_run(char *text)
{
    return 1;
}

Module ipinfo_module = {
    .name = "IPInfo",
    .module_valiator_func = ipinfo_validate,
    .module_run_func = ipinfo_run,
};