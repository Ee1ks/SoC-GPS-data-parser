#include "../inc/cmd_parser.h"

void parse_by_comma(uint8_t *cmd)
{
    uint8_t count = 0;
    uint8_t i = 0;
    uint8_t start = 0;
    uint8_t *tmp = NULL;
    while (cmd[i] != '\0')
    {
        // printf("Letter \"%c\"\n", GLL_test[i]);
        if (cmd[i] == ',')
        {
            tmp = (uint8_t *)malloc((i - start + 1) * sizeof(uint8_t));
            memcpy(tmp, &cmd[start], i - start);
            tmp[i - start] = '\0';
            printf("Data : %s\n", tmp);
            start = i + 1;
        }
        i++;
        count++;
    }
    tmp = (uint8_t *)malloc((i - start + 1) * sizeof(uint8_t));
    memcpy(tmp, &cmd[start], i - start);
    tmp[i - start] = '\0';
    printf("Data : %s\n", tmp);

    printf("count = %d\n", count);
}
