#ifndef RTAP_H
#define RTAP_H

enum present_field_bits{
                                    // Total storage requirement:
    PRESENT_TSFT_BIT = 0,           // eight bytes
    PRESENT_FLAGS_BIT = 1,          // one byte
    PRESENT_RATE_BIT = 2,           // one byte
    PRESENT_CHANNEL_BIT = 3,        // four bytes (2 byte align)
    PRESENT_FHSS_BIT = 4,           // two bytes
    PRESENT_DBM_ANTENNA_SIGNAL_BIT = 5,     // one byte
    PRESENT_DBM_ANTENNA_NOISE_BIT = 6,      // one byte
    PRESENT_LOCK_QUALITY_BIT = 7,           // two bytes (2 align)
    PRESENT_TX_ATTENUATION_BIT = 8,         // two bytes (2 align)
    PRESENT_DB_TX_ATTENUATION_BIT = 9,      // two bytes (2 align)
    PRESENT_DBM_TX_POWER_BIT = 10,          // one byte
    PRESENT_ANTENNA_PRESENT_BIT = 11,       // one byte
    PRESENT_DB_ANTENNA_SIGNAL_BIT = 12,     // one byte
    PRESENT_DB_ANTENNA_NOISE_BIT = 13,      // one byte
    PRESENT_RX_FLAGS_BIT = 14,      // two bytes (2 align)
    PRESENT_TX_FLAGS_BIT = 15,      // two bytes (2 align)
    PRESENT_RTX_RETRIES_BIT = 16,   //** one or two bytes depending on OS
    PRESENT_DATA_RETRIES_BIT = 17,  //** one byte
    PRESENT_XCHANNEL_BIT = 18,      //** (FreeBD and MacOS) 8 bytes
    PRESENT_MCS_BIT = 19,           // three bytes (1 byte align)
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
    struct antenna ant; // currently not being used.
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
void _align_two_bytes(const u_char **body);


  
#endif
