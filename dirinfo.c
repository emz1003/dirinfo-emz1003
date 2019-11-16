#include "dirinfo.h"

char * format_mode(mode_t mode) {
    char * results = calloc(sizeof(char), 8);
    mode = mode % 01000;
    int p[3];
    p[2] = mode % 010;
    p[1] = mode % 0100 / 010;
    p[0] = mode / 0100;
    int i;
    for (i = 0; i < 3; i++)
    {
        if (p[i] & 0b100)
            strcat(results, "r");
        else
            strcat(results, "-");

        if (p[i] & 0b10)
            strcat(results, "w");
        else
            strcat(results, "-");

        if (p[i] & 0b1)
            strcat(results, "x");
        else
            strcat(results, "-");
    }
    return results;
}