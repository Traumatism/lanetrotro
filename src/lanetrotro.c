#include "lanetrotro.h"
#include "../external/cJSON/cJSON.h"
#include "lib/module.h"

#include "modules/modules.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *id;
    char *type;
    char *text;

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
    Module null_module = {
        .name = "__null_module",
    };

    Module *modules[] = {
        &ipinfo_module,
        &ctlogs_module,

        /* TODO: assert this is the only module with name: __null_module */
        &null_module,
    };

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

        int j = 0;
        Module *module;

        while ((module = modules[j]) != &null_module)
        {
            logger_info("Running module: %s", module->name);

            j = j + 1;
        }
    }

    return 0;
}