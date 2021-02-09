#include "display_driver.h"

void clear_display(unsigned char *ram_addr)
{
    unsigned char *mem_target;
    _I("Clearing display");
    for(int i = 0; i< 2400; i++)
    {
        mem_target = ram_addr + i;
        *mem_target = 0;
    }
}

void init_display(unsigned char *ram_addr)
{
    _I("Starting display layout");
    unsigned char *mem_target;
    //every row is 80 char and there are 30 rows = 80*30 = 2400
    uint8_t init_text[2400];
    char line1[] = "GLL,5656.37235,N,02408.00860,E,094312.00,A,A*7A";
    char line2[] = "RMC,094313.00,A,5656.37219,N,02408.00860,E,0.546,,181120,,,A*60";
    char line3[] = "VTG,,T,,M,0.546,N,1.012,K,A*38";
    char line4[] = "GGA,094313.00,5656.37219,N,02408.00860,E,1,10,1.90,23.4,M,22.9,M,,*75";
    char line5[] = "________________________________________________________________________________";
    char line6[] = "";
    char line7_40[] = "Date: None";
    char line7_80[] = "Time: None";
    memcpy(&init_text[0], line1, strlen(line1));
    memcpy(&init_text[80], line2, strlen(line2));
    memcpy(&init_text[160], line3, strlen(line3));
    memcpy(&init_text[240], line4, strlen(line4));
    memcpy(&init_text[320], line5, strlen(line5));
    memcpy(&init_text[400], line6, strlen(line6));
    memcpy(&init_text[480], line7_40, strlen(line7_40));
    memcpy(&init_text[520], line7_80, strlen(line7_80));
    _I("Data copyed, writing to RAM");


    //write to RAM
    for(uint16_t text_pos = 0; text_pos < 580; text_pos++)
    {
        mem_target = ram_addr + text_pos;
        *mem_target = init_text[text_pos];
    }
}

void write_to_display(unsigned char *ram_addr)
{
    // Test stuff for outputting data
    int row = 0;
    int offset = 0;
    uint8_t text[2400];
    uint8_t text_pos_in_ram = 0;
    unsigned char *mem_target;
    _I("Enter text to display:");
    scanf("%[^\n]",text);
    _I("Enter line to write to:");
    scanf("%d",&row);
    getchar();
    _I("Enter offset:");
    scanf("%d",&offset);
    getchar();

    text_pos_in_ram = offset + row*80;
    _I("\nEntered data:");
    _I("Row: %d \nOffset: %d \nText: %s",row, offset, text);
    _I("RAM address: %x",text_pos_in_ram);
    _I("Text size: %d",strlen(text));

    //write to RAM
    for(uint8_t text_pos = 0; text_pos < strlen(text); text_pos++)
    {
        mem_target = ram_addr + text_pos_in_ram + text_pos;
        *mem_target = text[text_pos];
    }
}