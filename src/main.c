#include "../inc/cmd_parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdint.h>
#include <string.h>

/* utilities */
#define _I(fmt, args...) printf(fmt "\n", ##args)
#define _E(fmt, args...) printf("ERROR: " fmt "\n", ##args)

/* physical address spans */
#define HPS2FPGA_BASE 0xc0000000   /* physical address of the H2F bridge */
#define HPS2FPGA_SPAN 0x1000       /* address span to map */

#define UART0_BASE 0xFFC02000 //physical uart0 addr
#define UART0_SPAN 0x1        //UART0 span 4KB
#define UART0_RX_BUFF 0x0
#define UART0_LINE_STATUS 0x14

int main(int argc, char *argv[])
{
    printf("FPGA SOC GPS data parser");

    int fd;                   /* file descriptor */
    unsigned char *mem_uart0;
    unsigned char *mem_h2f;   /* memory pointer for HPS2FPGA bridge */
    unsigned char *mem_target;
    unsigned long data;


    /* Acquire "/dev/mem" file's descriptor (use "open" syscall) */
    // LAB: your code goes here
    _I("Opening \"/dev/mem\" file");
    fd = open("/dev/mem", O_RDWR);
    if (fd == -1)
    {
        _E("Failed to open \"/dev/mem\" file");
    }

    /* Map HPS2FPGA physical address to this process (use "mmap" syscall) */
    // LAB: your code goes here
    _I("Mapping physical address of HPS2FPGA");
    mem_h2f = mmap(NULL, HPS2FPGA_SPAN, PROT_READ | PROT_WRITE,
                     MAP_SHARED, fd, HPS2FPGA_BASE);
    if ((int)mem_h2f == -1)
    {
        _E("Failed to map physical address");
    }

    // Test stuff for outputting data
    int row = 0;
    int offset = 0;
    char text[2400];
    int ram_address = 0;
    _I("Enter text to display:");
    scanf("%[^\n]",text);
    _I("Enter line to write to:");
    scanf("%d",&row);
    _I("Enter offset:");
    scanf("%d",&offset);

    ram_address = offset + row*80;
    _I("\nEntered data:");
    _I("Row: %d \nOffset: %d \nText: %s",row, offset, text);
    _I("RAM address: %x",ram_address);
    _I("Text size: %d",strlen(text));

    //write to RAM
    for(int text_pos = 0; text_pos < strlen(text); text_pos++)
    {
        mem_target = mem_h2f + ram_address + text_pos;
        *mem_target = text[text_pos];
    }
    

    // // print test
    // for(int i =0 ; i< sizeof(GLL_test); i++)
    // {
    //     _I("Value %c",GLL_test[i]);
    //     mem_target = mem_h2f + strtoul(argv[1], NULL, 10) + i;
    //     *mem_target = (char)GLL_test[i];
    // }

    // uart testing
    // _I("Mapping physical address of UART0");
    // mem_uart0 = mmap(NULL, UART0_SPAN, PROT_READ,
    //                  MAP_SHARED, fd, UART0_BASE);
    // if ((int)mem_uart0 == -1)
    // {
    //     _E("Failed to map physical address");
    // }
    // mem_target = mem_uart0;

    // //read data from uart when data is ready
    // // if enter is pressed , break
    // while(1)
    // {
    //     //if bit0 is set = data ready
    //     if((*(mem_uart0 + UART0_LINE_STATUS) & 0x1))
    //     {
    //         data = *(mem_uart0 + UART0_RX_BUFF);
    //         _I("%c", (char)(data));
    //         if(data == '\r')
    //         {
    //             break;
    //         }
    //     }
    // }

    return 0;
}
