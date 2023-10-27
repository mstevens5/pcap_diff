#include <stdlib.h>
#include "dot11.h"

struct mac_header *create_mac_header()
{
    struct mac_header * mh = (struct mac_header*) malloc(sizeof(struct mac_header));
    mh->byte_len = 0;
    mh->type = 0;
    mh->subtype = 0;

}

void parse_frame_type(unsigned char cur_byte, uint8_t *type, uint8_t *subtype)
{
    uint8_t temp = cur_byte;
    *type = temp << 2 >> 6;
    *subtype = temp << 4 >> 4;
    return;
}

void read_dot11(const unsigned char * pkt)
{

    struct mac_header * mac_h = create_mac_header();
    // type and subtype
    uint8_t type, subtype;
    unsigned char cur_byte = *pkt;
    parse_frame_type(cur_byte, &type, &subtype);
    return;

}
