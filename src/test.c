#include <stdio.h>
#include <pcap/pcap.h>
#include "rtap.h"
#include "common.h"


void testing_rtap_parsing(char * pcap_file)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *cap = pcap_open_offline(pcap_file, errbuf);
    // Determine link-layer header type
    int ret = pcap_datalink(cap);
    int pkt_type = ret;
    printf("link-layer header type %d\n", ret);

    struct pcap_pkthdr *pkt_header;
    const u_char * contents;
    ret = pcap_next_ex(cap, &pkt_header, &contents);


    printf("%p\n", contents);
    printf("%d\n", (int)*contents);
    printf("caplen: %u\n", pkt_header->caplen);
    printf("len: %u\n", pkt_header->len);

    if (pkt_type != 127){
        pcap_close(cap);
        return;
    }
    printf("Reading radiotap header..\n");
    struct rtap *rt = read_rtap(&contents);
    print_rtap(rt);

    int count = 1;
    printf("count %d\n\n",count);
    while (pcap_next_ex(cap, &pkt_header, &contents) != PCAP_ERROR_BREAK){
        count++;
        struct rtap * rt = read_rtap(&contents);
        print_rtap(rt);
        printf("count %d\n\n",count);
    }
    printf("count = %d\n", count);
    pcap_close(cap);
    return;
}

void testing_dot11_parsing(char * pcap_file)
{
    printf("Testing dot11 parsing\n");
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *cap = pcap_open_offline(pcap_file, errbuf);
    // Determine link-layer header type
    int ret = pcap_datalink(cap);
    int pkt_type = ret;
    printf("link-layer header type %d\n", ret);

    struct pcap_pkthdr *pkt_header;
    const u_char * contents;

    int count = 0;
    while (pcap_next_ex(cap, &pkt_header, &contents) != PCAP_ERROR_BREAK){
        count++;
        struct rtap *rt;
        // pkt_type of 127 means radiotap followed by 802.11 header
        if (pkt_type == 127)
            rt = read_rtap(&contents);
            printf("Next byte: %x\n", *contents);
        printf("count %d\n\n",count);
    }
    printf("count = %d\n", count);

    pcap_close(cap);
}

int main(){

    char * pcap_file = "../pcaps/pcap_jungle";
    testing_rtap_parsing(pcap_file);
    testing_dot11_parsing(pcap_file);

    return 0;
}
