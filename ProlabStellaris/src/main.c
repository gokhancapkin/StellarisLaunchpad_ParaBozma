#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "Lcd.h"
#include "inc/lm4f120h5qr.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <math.h>
#include "stdbool.h"
char *
itoa (int value, char *result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}
void init_port_D() {
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTD_DIR_R |= 0x0F;
	GPIO_PORTD_AFSEL_R &= ~0x0F;
	GPIO_PORTD_DEN_R |= 0x0F;
}
void init_port_A() {
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTA_DIR_R |= 0x0F;
	GPIO_PORTA_AFSEL_R &= ~0x0F;
	GPIO_PORTA_DEN_R |= 0x0F;
}
void init_port_E() {
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTE_DIR_R |= 0x0F;
	GPIO_PORTE_AFSEL_R &= ~0x0F;
	GPIO_PORTE_DEN_R |= 0x0F;
}
void init_port_C() {
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTC_DIR_R |= 0x0F;
	GPIO_PORTC_AFSEL_R &= ~0x0F;
	GPIO_PORTC_DEN_R |= 0x0F;
}

#define PORTD (GPIO_PORTD_DATA_R)
#define PORTA (GPIO_PORTA_DATA_R)
#define PORTE (GPIO_PORTE_DATA_R)
#define PORTC (GPIO_PORTC_DATA_R)
#define RPD2	GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_2)
#define RPD3	GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_3)
#define RPC4	GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4)
#define RPA3	GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_3)
#define RPE3	GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_3)

int main(void) {

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    SysCtlClockSet(
                        SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ
                        | SYSCTL_OSC_MAIN);
        Lcd_init();
        init_port_D();
        init_port_A();
        init_port_E();
        init_port_C();
        //1-pd2 2-pd3 3-pa2 4-pa3 5-pa5
        GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_2);
        GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_3);
        GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_2);
        GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_3);
        GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_4);
        GPIOPinTypeGPIOInput(GPIO_PORTE_BASE,GPIO_PIN_3);
        GPIOPinTypeGPIOInput(GPIO_PORTE_BASE,GPIO_PIN_2);
        GPIOPinTypeGPIOInput(GPIO_PORTC_BASE,GPIO_PIN_4);
        int a=0,b=0,d=0,e=0;
        char as[10];
        char bs[10];
        char ds[10];
        char es[10];
        bool hesapla = false;
        bool sifirla = false;
        int sayac = 0;
		int noktaButon = 0;
        while(sayac < 3000000){
        	if(GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_2))
			{
				a=a+1;
				a=a%10;
				itoa(a,as,10);
				Lcd_Goto(1,12);
				Lcd_Puts(as);
				while(GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_2))
				{
				}
				hesapla = true;
				sayac = 0;
			}
        	else if(GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_3))
			{
				b=b+1;
				b=b%10;
				itoa(b,bs,10);
				Lcd_Goto(1,13);
				Lcd_Puts(bs);
				while(GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_3))
				{
				}
				hesapla = true;
				sayac= 0 ;
			}
        	else if(GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4))
			{
        		noktaButon=0;
				Lcd_Goto(1,14);
				Lcd_Puts(".");
				hesapla = true;
				noktaButon = 0;
				sayac = 0;
				while(GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4))
				{
					noktaButon++;
					if(noktaButon == 3000000)
					{
						a=0;b=0;d=0;e=0;
						sayac = 0;
						noktaButon = 0;
						hesapla = false;
						Lcd_Temizle();
						break;
					}
				}
				while(GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4))
				{

				}
			}
        	else if(GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_3))
			{
				d=d+1;
				d=d%10;
				itoa(d,ds,10);
				Lcd_Goto(1,15);
				Lcd_Puts(ds);
				while(GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_3))
											{
											}
				hesapla = true;
				sayac = 0;
			}
        	else if(GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_3))
			{
				e=e+1;
				e=e%10;
				itoa(e,es,10);
				Lcd_Goto(1,16);
				Lcd_Puts(es);
				while(GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_3))
											{
											}
				hesapla = true;
				sayac = 0;
			}
        	else if(hesapla == false)
        		sayac= 0;
        	else
        		sayac++;
        }
        Lcd_Goto(2,1);
        Lcd_Puts("Hesaplanacak");
        for(int delay=0;delay<5000000;delay++)
        {
        }
        Lcd_Temizle();

        int degisken = 10*a+b;
        int degisken2 = 10*d+e;
        char anapara[20];
        char tamKisim[10];
        char kusur[10];
        char nokta = ".";

        int temp =0 ;
        temp = degisken/20;
        degisken = degisken%20;
        itoa(degisken,tamKisim,10);
		itoa(degisken2,kusur,10);
		strcat(tamKisim,".");
		strcat(tamKisim,kusur);
		Lcd_Goto(1,12);
		Lcd_Puts(tamKisim);
        Lcd_Goto(2,1);
        char ekran[20];
        itoa(temp,ekran,10);
        char metin[20] = " adet yirmilik";
        strcat(ekran,metin);
        Lcd_Puts(ekran);
        for(int delay=0;delay<5000000;delay++)
                {
                }
        Lcd_Temizle();
		temp = degisken/10;
        degisken = degisken%10;
        itoa(degisken,tamKisim,10);
		itoa(degisken2,kusur,10);
		strcat(tamKisim,".");
		strcat(tamKisim,kusur);
		Lcd_Goto(1,12);
		Lcd_Puts(tamKisim);
        Lcd_Goto(2,1);
        char ekran2[20];
        itoa(temp,ekran2,10);
        strcpy(metin," adet onluk");
        strcat(ekran2,metin);
        Lcd_Puts(ekran2);
        for(int delay=0;delay<5000000;delay++)
                {
                }
        Lcd_Temizle();
		temp = degisken/5;
		degisken = degisken%5;
		itoa(degisken,tamKisim,10);
		itoa(degisken2,kusur,10);
		strcat(tamKisim,".");
		strcat(tamKisim,kusur);
		Lcd_Goto(1,12);
		Lcd_Puts(tamKisim);
		Lcd_Goto(2,1);
		itoa(temp,ekran2,10);
		strcpy(metin," adet beslik");
		strcat(ekran2,metin);
		Lcd_Puts(ekran2);
        for(int delay=0;delay<5000000;delay++)
                {
                }
        Lcd_Temizle();
		temp = degisken/1;
		degisken = degisken%1;
		itoa(degisken,tamKisim,10);
		itoa(degisken2,kusur,10);
		strcat(tamKisim,".");
		strcat(tamKisim,kusur);
		Lcd_Goto(1,12);
		Lcd_Puts(tamKisim);
		Lcd_Goto(2,1);
		itoa(temp,ekran2,10);
		strcpy(metin," adet birlik");
		strcat(ekran2,metin);
		Lcd_Puts(ekran2);
        for(int delay=0;delay<7000000;delay++)
                {
                }
        Lcd_Temizle();
		temp = degisken2/50;
		degisken2 = degisken2%50;
		itoa(degisken,tamKisim,10);
		itoa(degisken2,kusur,10);
		if(degisken2>10){
			strcat(tamKisim,".");
			strcat(tamKisim,kusur);
		}
		else
		{

			strcat(tamKisim,".0");
			strcat(tamKisim,kusur);
		}
		Lcd_Goto(1,12);
		Lcd_Puts(tamKisim);
		Lcd_Goto(2,1);
		itoa(temp,ekran2,10);
		strcpy(metin," adet yarimlik");
		strcat(ekran2,metin);
		Lcd_Puts(ekran2);
        for(int delay=0;delay<7000000;delay++)
                {
                }
        Lcd_Temizle();
		temp = degisken2/25;
		degisken2 = degisken2%25;
		itoa(degisken,tamKisim,10);
		itoa(degisken2,kusur,10);
		if(degisken2>10){
			strcat(tamKisim,".");
			strcat(tamKisim,kusur);
		}
		else
		{

			strcat(tamKisim,".0");
			strcat(tamKisim,kusur);
		}
		Lcd_Goto(1,12);
		Lcd_Puts(tamKisim);
		Lcd_Goto(2,1);
		itoa(temp,ekran2,10);
		strcpy(metin," adet ceyreklik");
		strcat(ekran2,metin);
		Lcd_Puts(ekran2);
        for(int delay=0;delay<7000000;delay++)
                {
                }
        Lcd_Temizle();
		temp = degisken2/10;
		degisken2 = degisken2%10;
		itoa(degisken,tamKisim,10);
		itoa(degisken2,kusur,10);
		if(degisken2>10){
			strcat(tamKisim,".");
			strcat(tamKisim,kusur);
		}
		else
		{

			strcat(tamKisim,".0");
			strcat(tamKisim,kusur);
		}
		Lcd_Goto(1,12);
		Lcd_Puts(tamKisim);
		Lcd_Goto(2,1);
		itoa(temp,ekran2,10);
		strcpy(metin," adet metelik");
		strcat(ekran2,metin);
		Lcd_Puts(ekran2);
        for(int delay=0;delay<7000000;delay++)
                {
                }
        Lcd_Temizle();
		temp = degisken2/5;
		degisken2 = degisken2%5;
		itoa(degisken,tamKisim,10);
		itoa(degisken2,kusur,10);
		if(degisken2>10){
			strcat(tamKisim,".");
			strcat(tamKisim,kusur);
		}
		else
		{

			strcat(tamKisim,".0");
			strcat(tamKisim,kusur);
		}
		Lcd_Goto(1,12);
		Lcd_Puts(tamKisim);
		Lcd_Goto(2,1);
		itoa(temp,ekran2,10);
		strcpy(metin," adet delik");
		strcat(ekran2,metin);
		Lcd_Puts(ekran2);
        for(int delay=0;delay<7000000;delay++)
                {
                }
        Lcd_Temizle();
		temp = degisken2/1;
		degisken2 = degisken2%1;
		itoa(degisken,tamKisim,10);
		itoa(degisken2,kusur,10);
		if(degisken2>10){
			strcat(tamKisim,".");
			strcat(tamKisim,kusur);
		}
		else
		{
			strcat(tamKisim,".0");
			strcat(tamKisim,kusur);
		}
		Lcd_Goto(1,12);
		Lcd_Puts(tamKisim);
		Lcd_Goto(2,1);
		itoa(temp,ekran2,10);
		strcpy(metin," adet kurus");
		strcat(ekran2,metin);
		Lcd_Puts(ekran2);
}
