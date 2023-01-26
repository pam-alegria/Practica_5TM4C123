#include "lib/include.h"

extern void Configura_Reg_PWM1(void)
{/*

    SYSCTL->RCGCPWM |= (1<<0); 
    SYSCTL->RCGCGPIO |= (1<<5); 
   // GPIOF->AFSEL |= (1<<3)|(1<<2)|(1<<1); 
    GPIOF_AHB->AFSEL |= 0x0E;
    GPIOF_AHB->PCTL |= (GPIOF_AHB->PCTL&0xFFFF000F) | 0x00006660; 
    GPIOF_AHB->DEN |= (1<<3)|(1<<2)|(1<<1);
    //PWM0->CC &= ~(1<<8);  
    PWM0->_0_CTL = (0<<0);
    PWM0->_1_CTL = (0<<0); 
    PWM0->_1_GENB = 0x0000080C; 
    PWM0->_1_GENA = 0x0000008C; 
    PWM0->_0_GENB = 0x0000008C;//PWM5
    PWM0->_1_LOAD = (int)(5000/freq); 
    PWM0->_0_LOAD = (int)(5000/freq); //50M/10k=5000
    PWM0->_1_CMPB = 15000;
    PWM0->_1_CMPA = 15000;
    PWM0->_0_CMPA = 15000;
    PWM0->_1_CTL = (1<<0);// Se activa el generador 3
    PWM0->_0_CTL = (1<<0);// Se activa el generador 2
    PWM0->ENABLE = (1<<3) | (1<<2) | (1<<1); 

    */

SYSCTL->RCGCPWM |= (1 << 1);

    // Enable clock for port F
    SYSCTL->RCGCGPIO |= (1 << 5);

    // Set pin F5 as PWM output 
    GPIOF->AFSEL |= (1<<5) | (1<<4) | (1<<3);
    GPIOF->PCTL &= ~(0xFF << (5 * 4));
    GPIOF->PCTL |= (0x54 << (5 * 4));
    GPIOF->DIR |= (1<<5) | (1<<4) | (1<<3);
    GPIOF->DEN |= (1<<5) | (1<<4) | (1<<3);

    // Configure PWM clock to be system clock divided by 64
    SYSCTL->RCC |= (1<<20);
    SYSCTL->RCC &= ~(0X1F << 17);
    SYSCTL->RCC |= (0x05 << 17);

    // Set PWM period to 400,000 clock cycles (50 Hz)
    PWM1->_3_LOAD = PWM_PERIOD;

    // Enable PWM output
    PWM1->ENABLE |= (1<<3) | (1 << 2) | (1<<1);

    // Set initial duty cycle to 10%
    PWM1->_3_CMPA = PWM_PERIOD / 10;
    PWM1->_2_CMPA = PWM_PERIOD / 10;
    PWM1->_1_CMPA = PWM_PERIOD / 10;

     // Configure PWM Generator
    PWM1->_3_CTL = 0x00000000;
    PWM1->_3_GENA = (0x8C << 16) | 0x80;
    PWM1->_2_CTL = 0x00000000;
    PWM1->_2_GENA = (0x8C << 16) | 0x80;
    PWM1->_1_CTL = 0x00000000;
    PWM1->_1_GENA = (0x8C << 16) | 0x80;

    //Start PWM 
    PWM1 -> ENABLE |= (1<<3) | (1<<2) | (1<<1);
}
