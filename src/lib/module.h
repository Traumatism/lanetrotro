#pragma once
typedef struct
{
    char *name;
    int (*module_run_func)(char *);
    int (*module_valiator_func)(char *);
} Module;