#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pcap/pcap.h>
#include "rtap.h"
#include "common.h"

// Set default values for antenna struct
void init_antenna(struct antenna ant){
    ant.num_ant = 0;
    ant.id = NULL;
    ant.signal = NULL;
    return;
}

// Initialize rtap struct to default values
//
// return pointer to rtap struct or NULL on error.
struct rtap * init_rtap(){
    struct rtap * rt = malloc(sizeof(struct rtap));
    if (!rt) return NULL;
    if (rt == NULL)
        return NULL;
    rt->rate = 0;
    rt->channel = 0;
    rt->mcs_rate = 0;
    init_antenna(rt->ant);
    return rt;
}

// Print radiotap values to stdout
void print_rtap(struct rtap * rt)
{
    if (rt == NULL)
        return;
    printf("*** Radio Tap Values ****\n");
    printf("Channel: %u ", rt->channel);
    printf("Rate: %u ", rt->rate);
    printf("\n");
    return;
}

// This function parses the body of the radiotap portion of the packet and
// sets found data in a rtap structure.
//
// it_present:  Pointer to the first byte of the first it_present field in the
//              radiotap header
// body:    Pointer to the first byte of the body porton of the radiotap
//          section (i.e., the first byte after the last it_present field of
//          the header)
// return: An rtap struct holding the relavent radiotap information from
//         the packet. NULL is returned on error.
struct rtap * parse_body(uint32_t *it_present, const u_char *body)
{
    assert(it_present);
    assert(body);

    struct rtap *rt = init_rtap();
    if (rt == NULL)
        return NULL;
    uint32_t one = 1;
    uint32_t present = *it_present;
    // All radiotap packet info is little endian, so convert if needed.
    if (!is_little_end())
        present = reverse_32(present);
 
    // SKIP Mac Timestamp if present
    if (present & one << PRESENT_TSFT_BIT){
        body+= 8;
    }

    // SKIP Flags if present
    if (present & one << PRESENT_FLAGS_BIT)
        body++;

    // Record rate if present
    if (present & one << PRESENT_RATE_BIT){
        rt->rate = *body;
        body++;
    }

    // Record channel if present
    if (present & one << PRESENT_CHANNEL_BIT){
        // "Channel" requires 2 byte alignment
        int bytes_aligned = 2;
        if ((uintptr_t)body % bytes_aligned != 0)
            body++;
        // First two bytes represent channel in MHz
        rt->channel = *(uint16_t*)body; 
        if (!is_little_end())
            rt->channel = reverse_16(rt->channel);
        body+= 4;
    }
    return rt;
}

// Find the start of the radiotap body (first byte past the header)
// present: pointer to the first it_present section of the rtap header 
const u_char * find_body(uint32_t * present)
{
    assert(present);
    // Get initial "it_present" bitmask
    uint32_t cur = *present;
    if (!is_little_end())
        cur = reverse_32(cur);

    // Loop until we move past the last "it_present" field in the rtap header
    while (check_extended_bit(cur)){
        present += 1;
        cur = *present;
        if (!is_little_end())
            cur = reverse_32(cur);
    }
    // "present" currently points to the last bitmask in the header.
    // The next byte is the start of the body. 
    return (const u_char *) (present+1);
}

// Return true if the extended bit is set for the it_present header field.
//
// it_present: 4 byte radio tap header field
int check_extended_bit(uint32_t it_present)
{
    uint32_t mask = 1 << PRESENT_EXTENDED_BIT;
    if (it_present & mask)
        return 1;
    return 0;
}

// Read raw packet data where radio tap starts and store important information
//  in struct rtap. 
// 
// pkt: *pkt holds the starting address of the radio tap section in the raw
//      packet data. NOTE: Upon completion of the function, this pointer is 
//      moved forward past the radiotap section of the packet.
//
// return: A pointer to rtap struct that holds appropriate rtap information.
struct rtap * read_rtap(const u_char ** pkt)
{
    assert(pkt);
    assert(*pkt);

    // pointer to first byte of packet (i.e., first byte of the rtap header)
    const u_char * pkt_ptr = (const u_char*) *pkt;

    uint32_t * present = (uint32_t *)&pkt_ptr[4];

    // get the first byte of the radiotap body
    const u_char * body = find_body(present);
    if (!body) return NULL;

    struct rtap * rt = parse_body(present, body);
    if (!rt) return NULL;

    uint16_t len = pkt_ptr[2];
    if (!is_little_end())
        len = reverse_16(len);

    // Move packet pointer past the radiotap header.
    (*pkt)+= len;
    return rt;
}
