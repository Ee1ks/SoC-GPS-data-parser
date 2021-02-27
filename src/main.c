#include "../inc/cmd_parser.h"
#include "../inc/utils.h"
#include "../inc/display_driver.h"
#include "../inc/server.h"

/* physical address spans */
#define HPS2FPGA_BASE 0xc0000000 /* physical address of the H2F bridge */
#define HPS2FPGA_SPAN 0x1000     /* address span to map */

int main(int argc, char *argv[])
{
    printf("FPGA SOC GPS data parser");

    int fd; /* file descriptor */
    uint8_t *mem_uart0;
    unsigned char *mem_h2f; /* memory pointer for HPS2FPGA bridge */

    _I("Opening \"/dev/mem\" file");
    fd = open("/dev/mem", O_RDWR);
    if (fd == -1)
    {
        _E("Failed to open \"/dev/mem\" file");
    }

    _I("Mapping physical address of HPS2FPGA");
    mem_h2f = mmap(NULL, HPS2FPGA_SPAN, PROT_READ | PROT_WRITE,
                   MAP_SHARED, fd, HPS2FPGA_BASE);
    if ((int)mem_h2f == -1)
    {
        _E("Failed to map physical address");
    }
    while (1)
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
        switch (action)
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
    return 0;
}
