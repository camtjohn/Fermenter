#ifndef ADC_TOOLS
#define ADC_TOOLS

//ADC1 Channels
#define ADC1_CHAN0          ADC_CHANNEL_4
#define ADC_ATTEN           ADC_ATTEN_DB_11

void adc_init(void);
int read_adc(void);
void adc_teardown(void);

#endif