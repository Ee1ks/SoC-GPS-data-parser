#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint8_t GLL_test[] = "GNGLL,5656.37235,N,02408.00860,E,094312.00,A,A*7A";
uint8_t RMC_test[] = "GNRMC,094313.00,A,5656.37219,N,02408.00860,E,0.546,,181120,,,A*60";
uint8_t VTG_test[] = "GNVTG,,T,,M,0.546,N,1.012,K,A*38";
uint8_t GGA_test[] = "GNGGA,094313.00,5656.37219,N,02408.00860,E,1,10,1.90,23.4,M,22.9,M,,*75";
uint8_t GSA_test[] = "GNGSA,A,3,26,06,02,25,31,22,03,09,04,,,,3.07,1.90,2.42*1F";

void parse_by_comma(uint8_t *cmd)
{
    uint8_t count = 0;
    uint8_t i = 0;
    uint8_t start = 0;
    uint8_t *tmp = NULL;
    while(cmd[i] != '\0')
    {
        // printf("Letter \"%c\"\n", GLL_test[i]);
        if(cmd[i] == ',')
        {
            tmp = (uint8_t *)malloc((i - start+1)*sizeof(uint8_t));
            memcpy(tmp,&cmd[start], i - start);
            tmp[i-start] = '\0';
            printf("Data : %s\n",tmp);
            start = i+1;
        }
        i++;
        count++;
    }
    tmp = (uint8_t *)malloc((i - start+1)*sizeof(uint8_t));
    memcpy(tmp,&cmd[start], i - start);
    tmp[i-start] = '\0';
    printf("Data : %s\n",tmp);

    printf("count = %d\n",count);
}

uint16_t main(uint16_t argc,uint8_t *argv[])
{
    printf("Parser GLL\n");
    parse_by_comma(GLL_test);
    printf("Parser RMC\n");
    parse_by_comma(RMC_test);
    printf("Parser VTG\n");
    parse_by_comma(VTG_test);
    printf("Parser GGA\n");
    parse_by_comma(GGA_test);
    printf("Parser GSA\n");
    parse_by_comma(GSA_test);

}
