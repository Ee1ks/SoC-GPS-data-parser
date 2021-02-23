#include "../inc/server.h"

int getData(int sockfd, unsigned char *ram_addr)
{
    int n;
    int addr_pos = 0;
    char text[80] = {0};
    char buffer[81] = {0};

    if ((n = read(sockfd, buffer, 80)) < 0)
        _E("ERROR reading from socket");
    buffer[n] = '\0';
    _I("%s",buffer);
    sscanf(buffer, "%d,%s\n", &addr_pos, text);
    if (addr_pos >2400)
    {
        close(sockfd);
        return -2;
    }

    // _I("key: %d value: %s", addr_pos, text);
    //write to RAM
    uint8_t write_len = 80;
    // len for Date/time line
    if (addr_pos >7*80 && addr_pos <8*80)
        write_len = 40-6;
    // len for speed line
    else if(addr_pos >10*80 && addr_pos <11*80)
        write_len = 40-7;
    // len for altitude line
    else if(addr_pos >12*80 && addr_pos <13*80)
        write_len = 80-26;
    // len for satelite count
    else if (addr_pos >17*80 && addr_pos <18*80)
        write_len = 20-9;
    else
        write_len = 80;

    unsigned char *mem_target;
    for (uint8_t text_pos = 0; text_pos < write_len; text_pos++)
    {
        mem_target = ram_addr + addr_pos + text_pos;
        *mem_target = text[text_pos];
    }
    // close(sockfd);
    return 0;
}

void open_server(unsigned char *ram_addr)
{
    int sockfd, newsockfd, portno = 8086, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    int data;

    _I("using port #%d", portno);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        _E("ERROR opening socket");
    bzero((char *)&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
        {
            _E("ERROR on binding");
            return;
        }
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    //--- infinite wait on a connection ---
    while (1)
    {
        _I("waiting for new client...");
        if ((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&clilen)) < 0)
            _E("ERROR on accept");
        _I("opened new communication with client");
        while (1)
        {
            //---- wait for a number from client ---
            data = getData(newsockfd, ram_addr);
            if (data != 0)
                _I("got %d", data);
            if (data < 0)
                break;
        }
        // close(newsockfd);

        //--- if -2 sent by client, we can quit ---
        if (data == -2)
            break;
    }
}
