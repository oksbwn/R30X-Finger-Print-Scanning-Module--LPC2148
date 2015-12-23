#include <LPC214X.H>
#include "Serial.h"
#include "Utility.h"
#include "LCD4.h"
#include "Glcd.h"

unsigned char Message[16] = {0XEF,0X01,0XFF,0XFF,0XFF,0XFF,0X01,0X00,0X07,0X13,0X00,0X00,0X00,0X00,0X00,0X1B};
unsigned char ack[12]={0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};
unsigned char gim[12]={0XEF,0X01,0XFF,0XFF,0XFF,0XFF,0X01,0X00,0X03,0X01,0X00,0X05};
unsigned char uim[12]={0XEF,0X01,0XFF,0XFF,0XFF,0XFF,0X01,0X00,0X03,0X0A,0X00,0X0E};
int main (void)
{   int i;
	PINSEL0 = 0;
	PINSEL1 = 0;
	PINSEL2 &= 0x0000000C;
	PINSEL2 |= 0x00000030;
	DelayProc(0.2 * CCLOCK);

	 LCD4_init(&IOPIN0, 20/*D4*/, 12/*RS*/, 14/*E*/);
	UART1_init(9600/*bps*/, 15000/*kHz*/,length_8_bit, stop_bit_1, parity_disable, parity_odd);
	UART0_init(9600/*bps*/, 15000/*kHz*/, length_8_bit, stop_bit_1, parity_disable, parity_odd);

	
	for(i=0;i<16;i++)
	{
	UART1_sendchar(Message[i]);
	
	}
    for(i=0;i<12;i++)
	{
    ack[i]=UART1_getchar();
	}
	 if(ack[9]==0x00)
{
//UART0_sendstring("password checked sucessfully\n\n");
LCD4_sendstr (0,2, "password checked sucessfully");
} 
  label:
	   for(i=0;i<12;i++)
	{
	UART1_sendchar(gim[i]);
	
	}
	for(i=0;i<12;i++)
	{
    ack[i]=UART1_getchar();
	} 

	 if(ack[9]==0x02)
{
//UART0_sendstring("cant find finger\n\n");
LCD4_sendstr (0,1, "cant find finger");
DelayProc(.7 * CCLOCK);
LCD4_sendstr (0,1, "Put finger");
//UART0_sendstring("Put finger\n\n");
DelayProc(.7* CCLOCK);
goto label;

}
if(ack[9]==0x00)
{
//UART0_sendstring("finger scan sucessfully completed\n\n");
LCD4_sendstr (0,1, "finger scan sucessfully completed");
}

 for(i=0;i<12;i++)
	{
	UART1_sendchar(uim[i]);
	
	}
	for(i=0;i<40000;i++)
	{
    UART0_sendchar(UART1_getchar());
	} 


      LCD4_sendstr (0,1, "image downloaded");

}


