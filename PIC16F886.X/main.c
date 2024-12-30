/*
 * File:   main.c
 * Author: Andrey Bui 
 *
 * Created on 28 10 2020
 */

#include <xc.h>
#include "main.h"
#include "lcd_hd44780_pic16.h"

const char Forward_[] = "FORWARD";
const char Reverse_[] = "REVERSE";
const char Tapping[] = "TAP";
const char ON_[]= " ON";
const char OFF_[] = "OFF";
const unsigned char Magn_count = 8;
const unsigned char minute = 60;
const unsigned char count_Hz = 2; // sampling frequency 2 Hz


unsigned char TIM0_count = 0;
unsigned char flag_delay = 0;
unsigned char keypressed = 0;
unsigned char delay_beep = 0;
unsigned char percent = 0;
unsigned int flag_timer1 = 0;
unsigned int count = 0;
unsigned int count2 = 0;

void main(void) {
    
  unsigned char ON_FLAG = 0;  
  unsigned char DIRECTION = 0;
  unsigned char flag_tapping = 0;
  unsigned int RPM_count = 0; 
  
  TRISA = 0b11000000;        // port A is output  
  ANSEL = 0x00;
  
  TRISB |= 0xFF;         // port B is input  
  // TRISB = 0b11111111; // port B is input  
  PORTB |= 0xFF; //
  
  TRISC &= ~0x7F;        //   port C0...C6 is output, C7 is input 
  //TRISC = 0b10000000;   
  
  ANSELH &= ~0x3F; //0b11000000;
  
  
  //PORTC = 0x9F;
  //PORTC &= ~0x60;
  PORTC |= 0xDF;
  //PORTC = 0b11011111; //
  
  OPTION_REG=0b00000111; // 
  // RBPU = 1;     // bit 7 PORTB pull-ups are disabled
  // RBPU = 0;     // bit 7 PORTB pull-ups are enables
  //INTEDG = 0;   // bit 6 Interrupt on falling edge of INT pin
  //T0CS = 0;      // bit 5 Internal instruction cycle clock (FOSC/4)
  //T0SE = 0;      // bit 4 IIncrement on low-to-high transition on T0CKI pin
  //PSA = 0;       // bit 5 Prescaler is assigned to the Timer0 module
  //PS0 = 1;       // 1 : 256 Prescaler Rate
  //PS1 = 1;       // ??????? ?? 256 ???
  //PS2 = 1;
  WPUB |=0xFF; //pull-up enables
  INTCON = 0b11110000;
  //GIE = 1;  //bit 7 Enables all unmasked interrupts
  //PEIE = 1; //bit 6 Enables all peripheral interrupts
  //T0IE = 1; //bit 5 Enables the Timer0 interrupt
  //INTE = 1; //bit 4 Enables the INT external interrupt
  //RBIE = 0;
  TMR0 = 0;
  
  TMR1IE = 1; //bit 0 PIE1 Enables the timer1 overflow interrupt
  //bity T1CON
  TMR1GE = 0;   //bit 6 timer 1 is always counting
  T1CKPS1 = 1;  // bit 5 Prescaler 8 (1000000/62500/8 = 2 Hz)
  T1CKPS0 = 1;  // bit 4
  
  //T1CKPS1 = 1;  // bit 5 Prescaler 4 (1000000/50000/4 = 5 Hz)
  //T1CKPS0 = 0;  // bit 4
  
  //T1CKPS1 = 0;  // bit 5 Prescaler 2 (1000000/50000/2 = 10 Hz)
  //T1CKPS0 = 1;  // bit 4
  
  //T1CKPS1 = 0;  // bit 5 Prescaler 1 (1000000/50000/1 = 20 Hz)
  //T1CKPS0 = 0;  // bit 4
  
  T1OSCEN = 0;  // bit 3 LP oscilator is off
  TMR1CS = 0;   // bit 1 Internal clock
  TMR1ON = 1;   // bit 0 Enables timer 1
  
  TMR1IF = 0;
  //Initialize the LCD Module
  TMR1L=0xDC;
  TMR1H=0xB; // 65536 - 62500 = 3036 = 0xBDC
  
  __delay_ms(200);   
  BEEP_OFF;
  __delay_ms(200);   
  BEEP_ON;
  __delay_ms(200); 
  BEEP_OFF;
  __delay_ms(200);
  BEEP_ON;
  __delay_ms(200);
  LCDInit(LS_NONE);

  //Clear the display
  LCDClear();
  __delay_ms(10);
  
  DIRECTION = Forward();
  
  LCDGotoXY(8,0);
  LCDWriteString(OFF_);
  //Write a string
  LCDGotoXY(0,1);
  LCDWriteString("Speed");
  LCDGotoXY(13,1);
  LCDWriteString("rpm");
 
  INV_INC_HIGH;
  __delay_ms(10);
  BEEP_OFF;
  while(1)

  {
 
      
  if (!REVERSE) 
  {
      __delay_ms(30);
      if (!REVERSE) 
      {
        //keypressed = 1;
        //BEEP();
        
        if (!ON_FLAG) DIRECTION = Reverse();
        BEEP();
        //BEEP();
        /*
         if (DIRECTION == 1)
        {
          LCDGotoXY(0,1);
          LCDWriteString("REVERSE");
          if (ON_FLAG == 1)
                {
                OFF;
                LED_OFF;
                REV;
                ON_FLAG = 0;
                LCDGotoXY(8,1);
                LCDWriteString("OFF");
                __delay_ms(1000);
                ON;
                LED_ON;
                ON_FLAG = 1;
                LCDGotoXY(8,1);
                LCDWriteString(" ON");
                }
          else REV;
          DIRECTION = 0;     
        } 
        */ 
         
        
       
      }
  }
  



  if (!FORWARD) 
  {
      __delay_ms(30);
      if (!FORWARD) 
      {
        //keypressed = 1;
        
        if (!ON_FLAG) DIRECTION = Forward();
        BEEP();
        //BEEP();
        /*
         if (DIRECTION == 0)
        {
          LCDGotoXY(0,1);
          LCDWriteString("FORWARD");
          if (ON_FLAG == 1)
                {
                OFF;
                LED_OFF;
                ON_FLAG = 0;
                LCDGotoXY(8,1);
                LCDWriteString("OFF");
                __delay_ms(1000);
                FORW;
                ON;
                LED_ON;
                ON_FLAG = 1;
                LCDGotoXY(8,1);
                LCDWriteString(" ON");
                }
          else FORW;
          DIRECTION = 1;
        }
         */
        
           
        
      }
  }
  
  if (!START) 
  {
      __delay_ms(30);
      if (!START) 
      {
          //keypressed = 1;
          BEEP();
          LED_ON;
          __delay_ms(1000);
          ON_FLAG = DRIL_ON();
          
      }
  }
  
  if (!STOP) 
  {
      __delay_ms(30);
      if (!STOP) 
      {
          //keypressed = 1;
          
          ON_FLAG = DRIL_OFF();
          BEEP();
          //BEEP1();
          
          
      }
  }
  if (!PLUS) 
  {
      __delay_ms(50);
      if (!PLUS) 
      {
         UP;
         BEEP();
         //keypressed = 1;
         __delay_ms(100);
         INV_INC_LOW;
           
         __delay_ms(25);
         INV_INC_HIGH;
         __delay_ms(25);
            
         if (percent<100) 
         {
            percent++;
         }
         
      }
  }
  if (!MINUS) 
  {
      __delay_ms(50);
      if (!MINUS) 
      {
          DOWN;
          BEEP();
          //keypressed = 1;
          __delay_ms(100);
          INV_INC_LOW;
          __delay_ms(25);
          INV_INC_HIGH;
          __delay_ms(25);
            
          if (percent>0) 
         {
            
            percent--;
         }
          
      }
  }
  if ((CheckTAPPING())&&(!ON_FLAG)) 
  {
    BEEP();
    //BEEP1();
    LCDGotoXY(13,1);
    if (flag_tapping == 0) 
        {
            LCDWriteString(Tapping);
            LED_TAP_ON;
            flag_tapping = 1;
        }
    else
        {
            LCDWriteString("rpm");
            //__delay_ms(100);
            LED_TAP_OFF;
            flag_tapping = 0;
        }     
    
     
  }
          
  
  if ((flag_tapping)&&(!TAP_REVERSE)&&(ON_FLAG)) 
  {
    //DIRECTION=REV_FOR(DIRECTION)//,ON_FLAG);
    
    //BEEP();
    BEEP();  
    //keypressed = 1;
    ON_FLAG = DRIL_OFF();
    __delay_ms(2700);
    BEEP1();
    __delay_ms(200);
    if (DIRECTION == 0) DIRECTION = Reverse();
    else DIRECTION = Forward();
    __delay_ms(100);
    ON_FLAG = DRIL_ON();
    
  }
  
  
  LCDGotoXY(13,0);
  
   if (percent < 10)
  {
    LCDWriteString("  ");
    LCDWriteInt(percent,1); 
  }
  else if (percent < 100)
  {
    LCDWriteString(" ");
    LCDWriteInt(percent,2); 
  }
  else  LCDWriteInt(percent,3); 
      
    
  LCDGotoXY(7,1);
  
  if (flag_timer1)
  {
  RPM_count = (count*count_Hz*minute)/Magn_count;
  
  if (RPM_count < 10)
  {
    
    LCDWriteString("   ");
    LCDGotoXY(10,1);
    LCDWriteInt(RPM_count,1);
  }
  else if (RPM_count < 100)
  {
    
    LCDWriteString("  ");
    LCDGotoXY(9,1);
    LCDWriteInt(RPM_count,2);
  }
  else if (RPM_count < 1000)
    {
    
    LCDWriteString(" ");
    LCDGotoXY(8,1);   
    LCDWriteInt(RPM_count,3);
  }
  else
  {
    
    LCDWriteInt(RPM_count,4);
  }
  
  flag_timer1 = 0;
  count = 0;
  TMR1L=0xDC;
  TMR1H=0xB; // 65536 - 62500 = 3036 = 0xBDC    
  //TMR1IF=0;
  }
       

  }
    return;
}
unsigned char CheckTAPPING(void)
{
  unsigned char result=0;
  unsigned int butcount=0;
  while(!TAPPING)
  {
    if(butcount < 15000)
    {
      butcount++;
    }
    else
    {
      result = 1;
      //keypressed = 1;
      break;
    }
  }
  return result;
}


unsigned char Reverse(void)
{

    LCDGotoXY(0,0);
    LCDWriteString(Reverse_);
    
    REV;

return 1;
} 

unsigned char Forward(void) //unsigned char  FLAG)
{

    LCDGotoXY(0,0);
    LCDWriteString(Forward_);
    
    FORW;
return 0;
} 

unsigned char DRIL_ON(void) //unsigned char  FLAG)
{
    ON;
    LED_ON;
    LCDGotoXY(8,0);
    LCDWriteString(ON_);
return 1;
} 

unsigned char DRIL_OFF(void)
{
    OFF;
    LED_OFF;
    LCDGotoXY(8,0);
    LCDWriteString(OFF_);
return 0;
}

void BEEP(void)
{
    if (!delay_beep)
    {
    delay_beep = 1;    
    BEEP_ON;
    //T0IF=0;   // TMR0 register did not overflow
    //RC0=~RC0;
    //T0IE = 1; // Enables the Timer0 interrupt
    TMR0&=~0xFF;

    }
    
}

void BEEP1(void)
{
BEEP_ON;
__delay_ms(200);
BEEP_OFF;
}

void interrupt isr(void)
{
    if (INTF)
    {
       
       if (count<1000) 
       {
           if (!flag_timer1) count++;
           //else count2 = count;
       }
       INTF = 0;
        
    }
    
    if(TMR1IF)
    {
      //TMR1L=0xB0;
      //TMR1H=0x3C; // 65536 - 50000 = 15536 = 0x3CB0
      
      //TMR1L=0xDC;
      //TMR1H=0xB; // 65536 - 62500 = 3036 = 0xBDC
      
      TMR1IF=0;
      flag_timer1 = 1;
      //RC0=~RC0;
      
    }
    
    if (T0IF)
    {
        TIM0_count++;
        if (delay_beep) BEEP_OFF;
     
        //if(TIM0_count==3) 
        //T0IE = 0; // Disables the Timer0 interrupt
        if(TIM0_count>10)
        {
            TIM0_count=0;
            delay_beep = 0;
        //T0IE = 1; // Enables the Timer0 interrupt
        }
        //RC0=~RC0;
        T0IF=0;   // TMR0 register did not overflow
        
    }
  
    
  
    //TMR1F =
    
}


void send_LCD(unsigned char RS_value, unsigned char DB4_value, unsigned char DB5_value, unsigned char DB6_value, unsigned char DB7_value) 
{

  RS=RS_value;  
  E=0;       

  D4=DB4_value;
  D5=DB5_value; 
  D6=DB6_value; 
  D7=DB7_value; 

  E=1; 
  __delay_us(50);  
  E=0;  

};


/*

*/
