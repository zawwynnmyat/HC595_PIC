

// PIC16F877A Configuration Bit Settings

// 'C' source line config statements
#define _XTAL_FREQ 4000000
// CONFIG
// CONFIG1
#pragma config FOSC = HS// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>

#define DS_SER PORTCbits.RC1
#define SHCP_SRCLK PORTCbits.RC0
#define STCP_RCLK PORTCbits.RC2

void sendData(uint8_t data){
    for(int i=0;i<8;i++){
        DS_SER = (data >> i) & 0x01;
        SHCP_SRCLK = 1;
        __delay_us(500);
        SHCP_SRCLK = 0;
        __delay_us(500);
    }
    STCP_RCLK = 1;
    __delay_us(500);
    STCP_RCLK = 0;
}
void main(void){
    TRISC = 0x00;
    PORTC = 0x00;
    
    uint8_t led[8]={0b10000000, 0b11000000,0b11100000,0b11110000,0b11111000, 0b11111100, 0b11111110, 0b11111111};
    
    while(1){
         for(int i=0;i<8;i++)   {
             sendData(led[i]);
             __delay_ms(500);
         }
    }
}