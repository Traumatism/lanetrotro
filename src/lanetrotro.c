#include "lanetrotro.h"

#include "lib/module.h"
#include "modules/modules.h"

#include "../external/cJSON/cJSON.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    /* Node content */

    char *id;   /* Node ID */
    char *type; /* Node type */
    char *text; /* Node content */

    /* 2D-Map parameters */

    signed x;
    signed y;

    int width;
    int height;
} Node;

/* Print a node to stdout. */
int print_node(Node *node)
{
    return printf("Node { id: %s, type: %s, text: %s, x: %d, y: %d, w: %d, h: %d }\n", node->id, node->type, node->text, node->x, node->y, node->width, node->height);
}

int main(int argc, char **argv)
{
    Module *modules[] = {
        &ipinfo_module,
        // &ctlogs_module,
    };

    int modules_count = sizeof(modules) / sizeof(modules[0]);

    print_banner();

    if (argc != 2)
    {
        logger_error("Please provide an Obsidian canva file.");
        return 1;
    }

    char *file_path = argv[1];

    FILE *fp = fopen(file_path, "r");

    if (fp == NULL)
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
    int i = -1;

    while ((c = fgetc(fp)) != EOF)
        buffer[i = i + 1] = c;

    buffer[buffer_size] = '\0';

    if (ferror(fp))
    {
        logger_error("Error while reading file content.");
        return 1;
    }

    fclose(fp);

    cJSON *nodes = cJSON_Parse(buffer)->child;
    int nodes_count = cJSON_GetArraySize(nodes);

    logger_info("Found %d nodes", nodes_count);

    for (int i = 0; i < nodes_count; i++)
    {
        cJSON *node_json_obj = cJSON_GetArrayItem(nodes, i);

        cJSON *id_obj = cJSON_GetObjectItem(node_json_obj, "id");
        cJSON *type_obj = cJSON_GetObjectItem(node_json_obj, "type");
        cJSON *text_obj = cJSON_GetObjectItem(node_json_obj, "text");
        cJSON *x_obj = cJSON_GetObjectItem(node_json_obj, "x");
        cJSON *y_obj = cJSON_GetObjectItem(node_json_obj, "y");
        cJSON *width_obj = cJSON_GetObjectItem(node_json_obj, "width");
        cJSON *height_obj = cJSON_GetObjectItem(node_json_obj, "height");

        Node node = {
            .id = cJSON_GetStringValue(id_obj),
            .type = cJSON_GetStringValue(type_obj),
            .text = cJSON_GetStringValue(text_obj),
            .x = cJSON_GetNumberValue(x_obj),
            .y = cJSON_GetNumberValue(y_obj),
            .width = cJSON_GetNumberValue(width_obj),
            .height = cJSON_GetNumberValue(height_obj),
        };

        logger_info("Running modules for node: %s", node.id);

        Module *module;

        for (int i = 0; i < modules_count; i++)
        {
            module = modules[i];

            char *to_validate = malloc(strlen(node.text) + 1);

            if (to_validate == NULL)
            {
                logger_error("Out of memory!");
                return 0;
            }

            strcpy(to_validate, node.text);

            int is_valid = module->module_valiator_func(to_validate);

            free(to_validate);

            if (!is_valid)
                continue;

            logger_info("Running module %s for data: %s", module->name, node.text);

            module->module_run_func(node.text);
        }
    }

    return 0;
}