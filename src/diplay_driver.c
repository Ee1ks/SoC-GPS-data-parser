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
    uint8_t init_text[2400] = {0};
    char line1[80] = "GLL,5656.37235,N,02408.00860,E,094312.00,A,A*7A";
    char line2[80] = "RMC,094313.00,A,5656.37219,N,02408.00860,E,0.546,,181120,,,A*60";
    char line3[80] = "VTG,,T,,M,0.546,N,1.012,K,A*38";
    char line4[80] = "GGA,094313.00,5656.37219,N,02408.00860,E,1,10,1.90,23.4,M,22.9,M,,*75";
    char line5[80] = "________________________________________________________________________________";
    char line6[80] = {0};
    char line7_40[40] = "Date: None";
    char line7_80[40] = "Time: None";
    char line8[80] = "________________________________________________________________________________";
    char line9[80] = {0};
    char line10_40[40] = "Speed: None (knots)";
    char line10_80[40] = "Speed: None (km/h)";
    char line11[80] = {0};
    char line12[80] = "Altitude above sea level: None (m)";
    char line13[80] = "________________________________________________________________________________";
    char line14[80] = {0};
    char line15[80] = "Number of satelites:";
    char line16[80] = {0};
    char line17_1[20] = "RUSSIA: None";
    char line17_2[20] = "CHINA: None";
    char line17_3[20] = "USA: None";



    memcpy(&init_text[80*1], line1, sizeof(line1));
    memcpy(&init_text[80*2], line2, sizeof(line2));
    memcpy(&init_text[80*3], line3, sizeof(line3));
    memcpy(&init_text[80*4], line4, sizeof(line4));
    memcpy(&init_text[80*5], line5, sizeof(line5));
    memcpy(&init_text[80*6], line6, sizeof(line6));
    memcpy(&init_text[80*7], line7_40, sizeof(line7_40));
    memcpy(&init_text[80*7+40], line7_80, sizeof(line7_80));
    memcpy(&init_text[80*8], line8, sizeof(line8));
    memcpy(&init_text[80*9], line9, sizeof(line9));
    memcpy(&init_text[80*10], line10_40, sizeof(line10_40));
    memcpy(&init_text[80*10+40], line10_80, sizeof(line10_80));
    memcpy(&init_text[80*11], line11, sizeof(line11));
    memcpy(&init_text[80*12], line12, sizeof(line12));
    memcpy(&init_text[80*13], line13, sizeof(line13));
    memcpy(&init_text[80*14], line14, sizeof(line14));
    memcpy(&init_text[80*15], line15, sizeof(line15));
    memcpy(&init_text[80*16], line16, sizeof(line16));
    memcpy(&init_text[80*17], line17_1, sizeof(line17_1));
    memcpy(&init_text[80*17+30], line17_2, sizeof(line17_2));
    memcpy(&init_text[80*17+60], line17_3, sizeof(line17_3));
    _I("Data copyed, writing to RAM");


    //write to RAM
    for(uint16_t text_pos = 0; text_pos < 2400; text_pos++)
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