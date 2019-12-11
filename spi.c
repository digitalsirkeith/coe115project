#include "xc.h"
#define CLK_POL_ACTIVE_HIGH 0x0000
#define SPI_CKE_ON 0x0100
#define SLAVE_ENABLE_ON 0x0080
#define SPI_MODE8_ON 0x0000 /* Communication is byte wide */
#define MASTER_ENABLE_OFF 0x0000 /* Slave Mode */
#define SLAVE_READY _LATB2
 
 

void config_slave_ready(){
_TRISB2 =0;
_PCFG4 =1;
// _CN6PUE =1;
_LATB2=1;
}
void config_SPI1(void){
SPI1CON1 = CLK_POL_ACTIVE_HIGH | //pri_prescale 4:1 sec prescale 1:1 clk pol active high
SPI_CKE_ON |
SLAVE_ENABLE_ON |
SPI_MODE8_ON |
MASTER_ENABLE_OFF ;
_SDI1R = 5;                                                        //config SDI to RP5
_RP6R =7;                                                      //config serial data out to RP6
_SCK1R= 7;                                                 //serial clock in from master to RP7
_SS1R = 3;                                                      //slave select in to RP3
config_slave_ready();
SLAVE_READY =0;
int index =0;
_SPI1IF =0;
_SPI1IP =3;
_SPI1IE =0;
SPI1STATbits.SPIEN =1;
}
 
void doHeartBeat()
{
long b;
_LATB15 = 1;
for(b=0;b<3255;b++);                                                         // __delay_ms(1000);
_LATB15 = 0;
}
volatile int u16_index;
void _ISR _SPI1Interrupt (void) {

                                                                             //character arrived, place in buffer
sz_1[u16_index] = SPI1BUF;
u16_index++;


_SPI1IF = 0;                                               //clear interrupt flag
}
 

int main(void) {
config_SPI1();
while(1){
do {
for(j=0;j<22;j++)
sz_1[j]= SPI1BUF;
}while(j<22);
if(j>22){
doHeartBeat();
for(j=0;j<3255;j++);
_LATB2=0;

for(j=0;j<22;j++);
{
SPI1BUF = sz_1[22-j];
}
_LATB2=1;
}
}

doHeartBeat();
}