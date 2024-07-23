#include "../lib/module.h"

int ctlogs_run(char *text)
{
    return 1;
}

int ctlogs_validator(char *text)
{
    return 1;
}

Module ctlogs_module = {
    .name = "CTLogs",
    .module_valiator_func = ctlogs_validator,
    .module_run_func = ctlogs_run,
};