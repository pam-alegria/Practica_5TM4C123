#ifndef ADC_ADC_H_
#define ADC_ADC_H_

extern void Configura_Reg_ADC0(void);
extern void Configura_Reg_ADC1(void);
extern void ADC0_InSeq1(uint16_t *Result);
extern void ADC1_InSeq1(uint16_t *Result);
extern void ADC1_InSeq3(uint16_t *Result);
extern void ADC1_InSeq2(uint16_t *Result);
extern void read_adc(void);

#endif /* ADC_ADC_H_ */