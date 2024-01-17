#include <stdlib.h>
#include <stdio.h>
#include <pcap/pcap.h>
#include "dot11.h"
/*
struct mac_frame * read_mac_frame(const u_char * pkt_ptr)
{
    struct mac_frame * mf = malloc(sizeof(struct mac_frame));
    load_frame_type(*pkt_ptr, mf);
    populate_frame_data();
    return mf;
}

void populate_frame_data(const u_char * pkt_ptr, struct mac_frame * mf)
{   
    // Use type/subtype to determine which parse function to call.
    // If management frame
    // parse_management_frame()

    // If control frame
    // parse_control_frame()

    // If data frame
    // parse_data_frame()

}

void parse_management_frame(const u_char * pkt_ptr, struct mac_frame * mf)
{
    switch (mf->subtype)
    {
    // Association Request
    case 0:
        break;
    // Association Response
    case 1:
        break;
    // Beacon
    case 8:
        handle_beacon_frame(pkt_ptr, mf);
        break
    default:
        // Shouldnt be here
        break;
    }
}

void handle_beacon_frame(const u_char * pkt_ptr, struct mac_frame * mf)
{

    // Parse Fixed Parameters (Non-Elements)
    int num_fixed = 3;
    mf->fixed_params = malloc(sizeof(struct dot11_fixed_param) * num_fixed);

    // Timestamp
    memcpy(mf->fixed_params[0].info, pkt_ptr, 8); 
    mf->fixed_params[0].length = 8;
    mf->fixed_params[0].tag = "Timestamp";
    //mf->fixed_params[0].;

    // Beacon Interval

    // Capability Information

    // Parse Tagged Parameters (Elements)
    int num_tagged = 67;
    mf->fields = malloc(sizeof(struct dot11_fields) * num_tagged);
    _add_dot11_element(mf, 0, 8)
    // Start adding fields


}

void _add_dot11_element(struct mac_frame * mf, uint8_t id, uint8_t len, uint8_t * info,
    uint8_t extension)
{
    size_t i = mf->num_fields; 
    mf->fields[i].id = id;
    mf->fields[i].id_extension = extension;
    mf->fields[i].length = len;
    mf->fields[i].info = malloc(sizeof(uint8_t) * len);
    mf->fields[i].ascii_str = NULL;
    return;
}

void populate_frame_type(const unsigned char cur_byte, struct mac_frame * mf)
{
    uint8_t temp = cur_byte;
    mf->type = (uint8_t)(temp << 4) >> 6;
    mf->subtype = temp >> 4;
    return;
}

void read_dot11(const u_char ** pkt)
{

    const u_char * pkt_ptr = (const u_char*) *pkt;

    struct mac_frame * mac_f = read_mac_frame(pkt_ptr);
    print_mac_info(mac_f);
    // type and subtype
    return;

}

void print_mac_info(struct mac_frame * mf){
    printf("Type is %u\n", mf->type);
    printf("Subtype is %u\n", mf->subtype);
    return;
}
*/