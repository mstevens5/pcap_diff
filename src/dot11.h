#ifndef DOTLL_H
#define DOTLL_H

struct dot11_tagged_param{
    uint8_t id;
    uint8_t id_extension; // optional. 0 possible and likely
    uint8_t length;
    uint8_t * info;
    char * ascii_str;
};

struct dot11_fixed_param{
    uint8_t info;
    uint8_t length;
    char * tag;
    char * value;
};

struct mac_frame{
    uint8_t type;
    uint8_t subtype;
    int8_t byte_len;
    char * s_addr;
    char * d_addr;
    char * bssid;
    char * t_addr; // transmitting
    char * r_addr; // receiving
    char * info;
    uint32_t num_tagged;
    struct dot11_tagged_param * tagged_params;
    uint32_t num_fixed;
    struct dot11_fixed_param * fixed_params;
};

//struct dot

struct mac_frame * read_mac_frame(const u_char*);
struct mac_frame * parse_frame(const u_char *);
void populate_frame_type(const unsigned char, struct mac_frame *);
void populate_frame_data(const u_char *, struct mac_frame *);
void read_dot11(const u_char **);
void print_mac_info(struct mac_frame *);

#endif