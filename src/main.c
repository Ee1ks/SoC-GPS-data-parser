#include "../inc/cmd_parser.h"
#include "../inc/utils.h"
#include "../inc/display_driver.h"
#include "../inc/server.h"

/* physical address spans */
#define HPS2FPGA_BASE 0xc0000000   /* physical address of the H2F bridge */
#define HPS2FPGA_SPAN 0x1000       /* address span to map */

#define UART0_BASE 0xFFC02000 //physical uart0 addr
#define UART0_SPAN 0x1        //UART0 span 4KB
#define UART0_RX_BUFF 0x0
#define UART0_LINE_STATUS 0x14

#define USB_OTG         0xFFB00000
#define USB_OTG_PWR     0xFFB0000C
#define USB_PWR         0x00100000

int main(int argc, char *argv[])
{
    printf("FPGA SOC GPS data parser");

    int fd;                   /* file descriptor */
    uint8_t *mem_uart0;
    unsigned char *mem_h2f;   /* memory pointer for HPS2FPGA bridge */

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
while(1)
{
    int breakout = 0;
    _I("Choose an action:");
    _I("0 - Clear display");
    _I("1 - Init display");
    _I("2 - Write to display");
    _I("3 - Open server");
    _I("4 - Exit");
    int action = 0;
    scanf("%d", &action);
    getchar();
    switch(action)
    {
        case 0:
            clear_display(mem_h2f);
            break;
        case 1:
            init_display(mem_h2f);
            break;
        case 2:
            write_to_display(mem_h2f);
            break;
        case 3:
            open_server(mem_h2f);
            break;
        case 4:
            breakout = 1;
            break;
    }
    if (breakout == 1)
    {
        return 0;
    }
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
