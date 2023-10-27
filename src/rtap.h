#ifndef RTAP_H
#define RTAP_H

enum present_field_bits{
                                // Data Required:
    PRESENT_TSFT_BIT = 0,       // eight bytes
    PRESENT_FLAGS_BIT = 1,      // one byte
    PRESENT_RATE_BIT = 2,       // one byte
    PRESENT_CHANNEL_BIT = 3,    // four bytes
    PRESENT_EXTENDED_BIT = 31,
};

struct antenna{
    uint8_t num_ant;
    uint8_t * id;
    uint8_t * signal;
};

struct rtap{
    uint8_t rate;
    uint16_t channel;
    uint8_t mcs_rate;
    struct antenna ant;
};

/** For reference from radiotap website.
struct ieee80211_radiotap_header {
    uint8_t    it_version;     // set to 0 
    uint8_t    it_pad;
    uint16_t   it_len;         // entire length 
    uint32_t   it_present;     // fields present
};
**/

void init_antenna(struct antenna);
struct rtap * init_rtap();
void print_rtap(struct rtap *);
struct rtap * parse_body(uint32_t*, const unsigned char*);
const u_char * find_body(uint32_t*);
int check_extended_bit(uint32_t);
struct rtap *read_rtap(const unsigned char **);


  
#endif
