#include "util.h"

void copy_str(const char *src, char *dst)
{
    int idx;
    for (idx = 0; src[idx]; idx++)
        dst[idx] = src[idx];
}