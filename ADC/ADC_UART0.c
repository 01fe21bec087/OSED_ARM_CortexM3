/*********************************************************************
 * Internal ADC Demonstration - ADC0.0
 *--------------------------------------------------------------------
 * Controller	: LPC1768
 * Project		: ALS-PJTBRD-ARMCTXM3-01
 * Description	: This example scans the channel ADC0.0. Voltage at
 * 				the pin P0.23 is varied by varying the pot P1. Since ref
 *				voltage is 3.3, ADC output range is 000 to FFF (12 bit) 
 **********************************************************************/

 #include<LPC17xx.h>
 #include<stdio.h>
 #include"UART0.h"
 //#include"lcd.h"

 #define	Ref_Vtg		3.300
 #define	Full_Scale	0xFFF			//12 bit ADC
char vtg[100],dval[100];
int main(void)
{
	
	unsigned long adc_temp;
	unsigned int i,j=0;
	float in_vtg;
	//unsigned char vtg[7],dval[7];
	//unsigned char Msg1[14] = {"ALS BENGALURU"};
	unsigned char Msg2[32] = {"AD CONVERTER (Display in UART0)"};
	unsigned char Msg3[11] = {"ANALOG IP:"};
	unsigned char Msg4[12] = {"ADC OUTPUT:"};

	SystemInit();
	UART0_Init();
	//SystemCoreClockUpdate();
	
	LPC_SC->PCONP |= (1<<15); //Power for GPIO block
    //lcd_init();
    LPC_PINCON->PINSEL1 &= ~(0x11<<14);
    LPC_PINCON->PINSEL1 |= 0x01<<14;	//P0.23 as AD0.0
	LPC_SC->PCONP |= (1<<12);			//enable the peripheral ADC
	
    i=0;
		while(Msg2[i]!='\0'){
			LPC_UART0->THR = Msg2[i];
			while(tx0_flag == 0x00);
			tx0_flag = 0x00;
			i++;
		}
		LPC_UART0->THR = '\n';
	    while(tx0_flag == 0x00);
		tx0_flag = 0x00;

		while(1)
	{
		LPC_ADC->ADCR = (1<<0)|(1<<21)|(1<<24);//0x01200001;	//ADC0.0, start conversion and operational	
		for(i=0;i<2000;i++);			//delay for conversion
		while((adc_temp = LPC_ADC->ADGDR) == 0x80000000);	//wait till 'done' bit is 1, indicates conversion complete
		adc_temp = LPC_ADC->ADGDR;
		adc_temp >>= 4;
		adc_temp &= 0x00000FFF;			//12 bit ADC
		in_vtg = (((float)adc_temp * (float)Ref_Vtg))/((float)Full_Scale);	//calculating input analog voltage
		sprintf(vtg,"%3.2fV",in_vtg);	//convert the readings into string to display on LCD
		sprintf(dval,"%x",adc_temp);
		for(i=0;i<2000;i++);
		if(j%100==0){
		i=0;
		while(Msg3[i]!='\0'){
			LPC_UART0->THR = Msg3[i];
			while(tx0_flag == 0x00);
			tx0_flag = 0x00;
			i++;
		}
		i=0;
		while(vtg[i]!='\0'){
			LPC_UART0->THR = vtg[i];
			while(tx0_flag == 0x00);
			tx0_flag = 0x00;
			i++;
		}
		LPC_UART0->THR = ' ';
	    while(tx0_flag == 0x00);
		tx0_flag = 0x00;
		
		i=0;
		while(Msg4[i]!='\0'){
			LPC_UART0->THR = Msg4[i];
			while(tx0_flag == 0x00);
			tx0_flag = 0x00;
			i++;
		}
		i=0;
		while(dval[i]!='\0'){
			LPC_UART0->THR = dval[i];
			while(tx0_flag == 0x00);
			tx0_flag = 0x00;
			i++;
		}
		LPC_UART0->THR = '\n';
	    while(tx0_flag == 0x00);
		tx0_flag = 0x00;
	  }
		  j++;
	}
}

	  