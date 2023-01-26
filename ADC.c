#include "lib/include.h"

/*
 * ADC.c
 *
 *  Created on: 04/01/2023
 *      Author: Pamela Alegria Lopez
 */

uint32_t pwm_period[NUM_PWM_CHANNELS];
uint32_t pwm_duty_cycle[NUM_PWM_CHANNELS];

extern void Configura_Reg_ADC0(void)

{
    /*
    
     //Pag 396 para inicializar el modulo de reloj del adc RCGCADC
    SYSCTL->RCGCADC = (1<<0); 
    //Pag 382 (RGCGPIO) Puertos base habilitación del reloj
    //                     F     E      D       C      B     A
    SYSCTL->RCGCGPIO |= (1<<5)|(1<<4)|(1<<3)|(0<<2)|(0<<1)|(1<<0);
    //(GPIOAFSEL) pag.770 Enable alternate función para que el modulo analógico tenga control de esos pines
    GPIOE->AFSEL = (0<<2); 
    GPIOD->AFSEL = (0<<0);
    GPIOB->AFSEL = (0<<4);
    GPIOE->AFSEL =  (1<<1);
    GPIOD->AFSEL =  (1<<3) | (1<<1);
    //Pag 760 (GPIODIR) Habilta los pines como I/O un cero para entrada y un uno para salida
    GPIOE->DIR = (0<<1); //PE5 y PE4
    GPIOD->DIR = (0<<3) | (0<<1);
    GPIOE->DIR = (0<<2); 
    GPIOD->DIR = (0<<0);
    GPIOB->DIR = (0<<4);
    //(GPIODEN) pag.781 desabilita el modo digital
    GPIOE->DEN = (0<<1);
    GPIOD->DEN = (0<<3) | (0<<1);
    GPIOE->DEN = (0<<2); 
    GPIOD->DEN = (0<<0);
    GPIOB->DEN = (0<<4);
    //Pag 787 GPIOPCTL registro combinado con el GPIOAFSEL y la tabla pag 1808
    GPIOE->PCTL = GPIOE->PCTL & (0xFFFFF00F);
    GPIOD->PCTL = GPIOD->PCTL & (0xFFFF0F00);
    GPIOB->PCTL = GPIOB->PCTL & (0xFFF0FFFF);
    //(GPIOAMSEL) pag.786 habilitar analogico
    GPIOE->AMSEL = (1<<1);
    GPIOD->AMSEL = (1<<3) | (1<<1);
    GPIOE->AMSEL = (1<<2); 
    GPIOD->AMSEL = (1<<0);
    GPIOB->AMSEL = (1<<4);
    //Pag 1159 El registro (ADCPC) establece la velocidad de conversión por segundo
    ADC0->PC = 0x7;//1Mksps
    //Pag 1099 Este registro (ADCSSPRI) configura la prioridad de los secuenciadores
    ADC0->SSPRI = 0x1203;
    //Pag 1077 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS  =   (0<<3) | (0<<2) | (0<<1) | (0<<0);
    //Pag 1091 Este registro (ADCEMUX) selecciona el evento que activa la conversión (trigger)
    ADC0->EMUX  = (0x0<<4) | (0x0<<8) | (0x0<<12);
    //Pag 1129 Este registro (ADCSSMUX2) define las entradas analógicas con el canal y secuenciador seleccionado
    ADC0->SSMUX1 = (2<<0) | (4<<4) | (6<<8) | (7<<12);
    ADC0->SSMUX3 = (10<<0);
    ADC0->SSMUX2 = (1<<0);
    //pag 868 Este registro (ADCSSCTL2), configura el bit de control de muestreo y la interrupción
    ADC0->SSCTL1 = (1<<1) | (1<<2) | (1<<5) | (1<<6) | (1<<8) | (1<<9) | (1<<13);
    ADC0->SSCTL3 = (1<<0);
    ADC0->SSCTL2 = (1<<1) | (1<<2);
    ADC0->IM |= (0<<1) | (0<<2) | (0<<3); 
    //NVIC_PRI4_R = (NVIC_PRI4_R & 0xFFFFFF00) | 0x00000020;
    //NVIC_EN0_R = 0x00010000;
    //Pag 1077 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS = (1<<3) | (1<<2) | (1<<1) | (0<<0);
    //ADC0->PSSI |= (1<<1);
    
    */

// Enable clock for ADC0
    SYSCTL->RCGCADC |= (1 << 0);

    // Enable clock for port E
    SYSCTL->RCGCGPIO |= (1 << 4);

    // Set pin E1 as ADC input
    GPIOE->AFSEL |= (1 << 1) | (1<<2) | (1<<3);
    GPIOE->DEN &= ~(1 << 1) | (1<<2) | (1<<3);

    // Configure ADC to sample on PE1
    ADC0->ACTSS &= ~(1<<3);
    ADC0->EMUX &= ~(0xF << 12);
    ADC0->SSMUX3 = (2 << 0) | (1 << 4) | (0 << 8); 
    ADC0->SSCTL3 = (1<<2) | (1<<1) | (1<<0);
    ADC0->IM |= (1<<3);
    ADC0->ACTSS |= (1<<3);

}

extern void ADC0_InSeq1(uint16_t *Result){

    //ADC Processor Sample Sequence Initiate (ADCPSSI)
       ADC0->PSSI = (1<<1);
       while((ADC0->RIS & (1<<1))==0){}; // espera al convertidor
       Result[0] = ADC0->SSFIFO1&0xFFF; //  Leer  el resultado almacenado en la pila2
       Result[1] = ADC0->SSFIFO1&0xFFF;
       Result[2] = ADC0->SSFIFO1&0xFFF;
       Result[3] = ADC0->SSFIFO1&0xFFF;
       //printChar('A');
       ADC0->ISC = 0x0002;  //Conversion finalizada

}

extern void ADC0_InSeq3(uint16_t *Result){

    //ADC Processor Sample Sequence Initiate (ADCPSSI)
       ADC0->PSSI = (1<<3);
       while((ADC0->RIS&(1<<3))==0){}; // espera al convertidor
       Result[4] = ADC0->SSFIFO1&0xFFF;
       //printChar('A');
       ADC0->ISC = 0x0008;  //Conversion finalizada

}

extern void ADC0_InSeq2(uint16_t *Result){

    //ADC Processor Sample Sequence Initiate (ADCPSSI)
       ADC0->PSSI = (1<<2);
       while((ADC0->RIS&(1<<2))==0){}; // espera al convertidor
       Result[5] = ADC0->SSFIFO2&0xFFF;
       //printChar('A');
       ADC0->ISC = 0x0004;  //Conversion finalizada
}

extern void read_adc(void) {
   uint32_t adc_value[NUM_ADC_CHANNELS];
    // Start ADC conversion
    ADC0->PSSI = (1 << 3);
    // Wait for conversion to complete
    while ((ADC0->RIS & (1 << 3)) == 0){};
    // Clear conversion complete flag
    ADC0->ISC = (1 << 3);
     // Read ADC value
    adc_value[0] = ADC0->SSFIFO3 >> 4;
    adc_value[1] = ADC0->SSFIFO3 & 0xF;
    adc_value[2] = ADC0->SSFIFO3 & 0xF;

    for (int i = 0; i < NUM_PWM_CHANNELS; i++){
      // Limit the duty cycle to the range of 10% to 20%
      if (pwm_duty_cycle[i] < (PWM_PERIOD * 0.1)) {
         pwm_duty_cycle[i] = PWM_PERIOD * 0.1;
      } else if (pwm_duty_cycle[i] > (PWM_PERIOD * 0.2)) {
         pwm_duty_cycle[i] = PWM_PERIOD * 0.2;
      }
    }
 PWM1->_3_CMPA = pwm_duty_cycle[0];
    PWM1->_2_CMPA = pwm_duty_cycle[1];
    PWM1->_1_CMPA = pwm_duty_cycle[2];

}