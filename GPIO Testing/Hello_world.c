/*
===============================================================================
 Name        : Hello_world.c
 Author      : Utsav Savaliya
 Version     : 1
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include <stdio.h>
#include <stdbool.h>



void GPIOinitOut(uint8_t portNum, uint32_t pinNum)
{
	if (portNum == 0)
	{
		LPC_GPIO0->FIODIR |= (1 << pinNum);
	}
	else if (portNum == 1)
	{
		LPC_GPIO1->FIODIR |= (1 << pinNum);
	}
	else if (portNum == 2)
	{
		LPC_GPIO2->FIODIR |= (1 << pinNum);
	}
	else
	{
		puts("Not a valid port!\n");
	}
}
void GPIOinitIn(uint8_t portNum, uint32_t pinNum)
{
	if (portNum == 0)
	{
		LPC_GPIO0->FIODIR &= ~(1 << pinNum);
	}
	else if (portNum == 1)
	{
		LPC_GPIO1->FIODIR &= ~ (1 << pinNum);
	}
	else if (portNum == 2)
	{
		LPC_GPIO2->FIODIR &= ~ (1 << pinNum);
	}
	else
	{
		puts("Not a valid port!\n");
	}
}

void setGPIO(uint8_t portNum, uint32_t pinNum)
{
	if (portNum == 0)
	{
		LPC_GPIO0->FIOSET = (1 << pinNum);
		printf("Pin 0.%d has been set.\n",pinNum);
	}
	//Can be used to set pins on other ports for future modification
	else
	{
		puts("Only port 0 is used, try again!\n");
	}
}


void clearGPIO(uint8_t portNum, uint32_t pinNum)
{
	if (portNum == 0)
	{
		LPC_GPIO0->FIOCLR = (1 << pinNum);
		printf("Pin 0.%d has been cleared.\n", pinNum);
	}
	//Can be used to clear pins on other ports for future modification
	else
	{
		puts("Only port 0 is used, try again!\n");
	}
}

bool readGPIOswitch(uint8_t portNum, uint32_t pinNum) {
	if (portNum == 0)
		return (LPC_GPIO0->FIOPIN & (1 << pinNum));
	else if (portNum == 1)
		return (LPC_GPIO1->FIOPIN & (1 << pinNum));
	else if (portNum == 2)
		return (LPC_GPIO2->FIOPIN & (1 << pinNum));
	else
		return 0;
}


int main(void)
{
    //Set pin 0.21 as output
    GPIOinitOut(0,21);
	//Set pin 2.13 as input
	GPIOinitIn(2,13);

    while(1)
    {
    	bool status=readGPIOswitch(2,13);
		if (status)
		{
			printf("Button press Detected, LED On\n");
			printf("STATUS=%d\n",status);
			//Activate pin 0.21(SET it high)
			setGPIO(0,21);
		}
		else{
			printf("STATUS=%d\n",status);\
			printf("Button is not press, LED OFF\n");
			//for (int c = 1; c <= 6000000; c++);
			clearGPIO(0,21);   //(SET it low)
			//for (int c = 1; c <= 6000000; c++);
			}

    }
    //0 should never be returned, due to infinite while loop
    return 0;
}
