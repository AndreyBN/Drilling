/* 
 * File:   main.h
 * Author: User
 *
 * Created on 29 ??????? 2020 ?., 19:07
 */
//CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
//#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
//#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config CP = ON          // Code Protection bit (Program memory code protection is enabled)
#pragma config CPD = ON         // Data Code Protection bit (Data memory code protection is enabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
//#pragma config WRT = HALF       // Flash Program Memory Self Write Enable bits (0000h to 0FFFh write protected, 1000h to 1FFFh may be modified by EECON control)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 4000000

#define  START RB1
#define  MINUS RB2
#define  PLUS  RB3
#define  TAPPING RB4
#define  REVERSE RB5
#define  FORWARD RB6
#define  STOP RB7
#define  TAP_REVERSE RC7

#define  LED_TAP_ON PORTC &=~(1<<0);
#define  LED_TAP_OFF PORTC |=(1<<0);
#define  ON PORTC &=~(1<<1); 
#define  OFF PORTC |=(1<<1);
#define  REV PORTC |=(1<<2);
#define  FORW PORTC &=~(1<<2); 
#define  INV_INC_HIGH PORTC &=~(1<<3); 
#define  INV_INC_LOW PORTC |=(1<<3);
#define  UP PORTC &=~(1<<4);
#define  DOWN PORTC |=(1<<4);
#define  BEEP_ON PORTC |=(1<<5);
#define  BEEP_OFF PORTC &=~(1<<5);
#define  LED_ON PORTC &=~(1<<6);
#define  LED_OFF PORTC |=(1<<6);

#define	LCD	PORTA				// ??????????? ?????
#define	LCD_TRIS TRISA			//
#define	E	PORTAbits.RA5					// ??????????? E
//#define	RW	PORTCbits.RC6					// ??????????? RW
#define	RS	PORTAbits.RA4					// ??????????? RS
//#define	LCD_LED	PORTCbits.RC0				// ??????????? ????? ?????????? ??????????

#define D4  PORTAbits.RA0
#define D5  PORTAbits.RA1
#define D6  PORTAbits.RA2
#define D7  PORTAbits.RA3



unsigned char CheckTAPPING(void);
unsigned char Forward(void);
unsigned char Reverse(void);
unsigned char DRIL_ON(void);
unsigned char DRIL_OFF(void);
void BEEP(void);
void BEEP1(void);

void interrupt isr(void);

void send_LCD(unsigned char RS_value, unsigned char DB4_value, unsigned char DB5_value, unsigned char DB6_value, unsigned char DB7_value);

//void interrupt int0(void);
//void __interrupt(high_priority) isr(void);
//void ON(void);
//void OFF(void);

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

