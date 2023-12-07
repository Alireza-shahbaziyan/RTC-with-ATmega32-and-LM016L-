#include <mega8.h>
#include <stdio.h>
#include <delay.h>

// Alphanumeric LCD functions
#include <alcd.h>

#define ADC_VREF_TYPE 0x00

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;
}

// Declare your global variables here
float _temperature;
char buff[20];
void main(void)
{
int s=0,m=0,h=0,x=0,temperature=0;
char b[16];
char c[16];
DDRD.0=1;
// ADC initialization
// ADC Clock frequency: 500.000 kHz
// ADC Voltage Reference: AREF pin
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x81;

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTB Bit 0
// RD - PORTB Bit 1
// EN - PORTB Bit 2
// D4 - PORTB Bit 4
// D5 - PORTB Bit 5
// D6 - PORTB Bit 6
// D7 - PORTB Bit 7
// Characters/line: 16
lcd_init(16);
lcd_clear();
lcd_putsf("The Name Of GOD");
delay_ms(1000);
lcd_clear();
while (1)
      { 
          s++;
          delay_ms(977);
          if(s>59){m++;s=0;}
          if(m>59){h++;m=0;}
          if(h>23){h=0;m=0;s=0;x=x+1;}
          sprintf(b,"%d:%d:%d   ",h,m,s);
          lcd_gotoxy(0,0);
          lcd_puts(b);
          sprintf(c,"Day: %d    ",x);
          lcd_gotoxy(0,1);
          lcd_puts(c);
           
          _temperature=read_adc(0)*0.48875855327468;
         temperature=_temperature;
          lcd_gotoxy(9,1);
          sprintf(buff,"Temp:%d    ",temperature);
          lcd_puts(buff);
          
          if(temperature>=40){PORTD.0=1;}
          
          if(temperature<40){PORTD.0=0;}
          
          if(PIND.0==1){
          lcd_gotoxy(9,0);
          lcd_putsf("Fan ON ");
          }
          
          if(PIND.0==0){
          lcd_gotoxy(9,0);
          lcd_putsf("Fan OFF");
          }
          
                }
}
