/*
LED Test (assuming LED at Pin 7 of port 2)
Author: Abhinav Pawar
Date: 11-10-2023
*/
#include<LPC17xx.h>
#define LED 7	//Making pin 7 as LED 
//Define functions
#define LED_ON()  LPC_GPIO2->FIOSET=1<<LED		//Set P2.7 bit
#define LED_OFF() LPC_GPIO2->FIOCLR=1<<LED		//clear P2.7 bit

unsigned int delay(int r1){
 	int r2;
	for(r2=0;r2<r1;r2++);
	return 0;
}
int main(void){
	SystemInit();
	//SystemCoreClockUpdate();
	LPC_PINCON->PINSEL4=0x00000000;	 //P2 is made as GPIO
	LPC_GPIO2->FIODIR=1<<LED;		 //p2.7 is output
	LPC_GPIO2->FIOCLR=1<<LED;	 	//Clear the P2.7 
	while(1){
		LED_ON();						//On the LED
		delay(100000);					//13usec to execute single instruction
		LED_OFF();						//Off the LED
		delay(100000);					//40msec for 10000 counts
	}
 }
