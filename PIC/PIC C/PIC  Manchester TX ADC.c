#include <16F676.h>
#device adc=8
#FUSES NOWDT
#FUSES INTRC_IO
#FUSES NOPROTECT
#FUSES NOBROWNOUT
#FUSES NOMCLR
#FUSES NOCPD
#FUSES NOPUT
#use delay(int=4000000)
#use rs232(baud=1200,parity=N,xmit=PIN_C4,rcv=PIN_C5,bits=8)
#define LED PIN_A0
//Manchester IEEE 802.3
void enviaMan(BYTE data){
   int i,j,nibble;
   for(i=0;i<2;i++){
      nibble=0;
      for(j=0;j<4;j++){
         nibble=nibble>>2;
         if(bit_test(data,0))
            nibble=nibble|0x40;
         else
            nibble=nibble|0x80;
         data=data>>1;
      }
      putc(nibble);
      delay_ms(300);
   }
}
void main(){
   setup_adc_ports(sAN0|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_2);
   while(true){
      set_adc_channel(0);
      delay_us(10);
      enviaMan(read_adc());
      delay_ms(1000);
   }
}