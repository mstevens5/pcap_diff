#include <stdlib.h>
#include "common.h"

int is_little_end()
{
    unsigned int x = 1;
    char *c = (char*) &x;
    return (int)*c;
}

u_int16_t reverse_16(u_int16_t value)
{
    return (((value & 0x00FF) << 8) |
            ((value & 0xFF00) >> 8));
}

u_int32_t reverse_32(u_int32_t value) 
{
    return (((value & 0x000000FF) << 24) |
            ((value & 0x0000FF00) <<  8) |
            ((value & 0x00FF0000) >>  8) |
            ((value & 0xFF000000) >> 24));
}

u_int64_t reverse_64(u_int64_t value) 
{
    return (((value & 0x00000000000000FF) << 56) |
            ((value & 0x000000000000FF00) << 40) |
            ((value & 0x0000000000FF0000) << 24) |
            ((value & 0x00000000FF000000) <<  8) |
            ((value & 0x000000FF00000000) >>  8) |
            ((value & 0x0000FF0000000000) >> 24) |
            ((value & 0x00FF000000000000) >> 40) |
            ((value & 0xFF00000000000000) >> 56));
}