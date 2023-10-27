#ifndef DOTLL_H
#define DOTLL_H

struct mac_header{
    int8_t type;
    int8_t subtype;
    int8_t byte_len;
    char * address1;
    char * address2;
    char * address3;
    char * address4;
    unsigned char * body;
};

struct management_frame{
     

};

struct control_frame{

};

struct data_frame{

};

#endif