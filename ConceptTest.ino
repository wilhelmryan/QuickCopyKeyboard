/*********************************************************
This is a library for the MPR121 12-channel Capacitive touch sensor

Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/

These sensors use I2C communicate, at least 2 pins are required 
to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
**********************************************************/

#include <Wire.h>
#include "Adafruit_MPR121.h"

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

char user[]="189";
char prefix[]="PRO-";

unsigned long prevprint=0;
unsigned long debounce=200;

unsigned long timer=0;
unsigned long period=5000;
const int heartbeat=9;
int value;

int totals[9];


void setup() {
  pinMode(heartbeat,OUTPUT);
  
  delay(1000);
  cap.begin(0x5A);
  Keyboard.begin();

  delay(1000);

}

void loop() {

for(int i=0;i<12;i++)
{
  if(cap.touched() & (1 << i)){processPrint(i);}
}

timer=millis();
if(timer-prevprint<1000){analogWrite(heartbeat,255);}

else {
value =abs(50*cos(2*PI/period*timer));
analogWrite(heartbeat, value);
}

}

void processPrint(int printNumber)
{
  unsigned long current=millis();

  if(current-prevprint>=debounce)
  {
    switch(printNumber){
      case 8:
      {
        char use[]="FF-";
        for(int i=0;i<sizeof(prefix);i++)
        {
          prefix[i]='\0';
        }
        for(int i=0;i<sizeof(prefix)&&i<sizeof(use);i++)
        {
          prefix[i]=use[i];
        }
          break;
      }
      case 4:
       {
        char use[]="KK-";
        for(int i=0;i<sizeof(prefix);i++)
        {
          prefix[i]='\0';
        }
        for(int i=0;i<sizeof(prefix)&&i<sizeof(use);i++)
        {
          prefix[i]=use[i];
        }
          break;
       }
       case 0:
        {
          char use[]="PRO-";
          for(int i=0;i<sizeof(prefix);i++)
          {
            prefix[i]='\0';
          }
          for(int i=0;i<sizeof(prefix)&&i<sizeof(use);i++)
          {
            prefix[i]=use[i];
          }
            break;
        }
        case 9:
        {
          char userno[]="189";
          for(int i=0;i<sizeof(user);i++)
          {
            user[i]=userno[i];
          }
          Keyboard.print(prefix);
          Keyboard.println(user);
          totals[0]+=1;
            break;
        }
        case 5:
        {
          char userno[]="021";
          for(int i=0;i<sizeof(user);i++)
          {
            user[i]=userno[i];
          }
          Keyboard.print(prefix);
          Keyboard.println(user);
          totals[1]+=1;
            break;
        }
        case 1:
        {
          char userno[]="053";
          for(int i=0;i<sizeof(user);i++)
          {
            user[i]=userno[i];
          }
          Keyboard.print(prefix);
          Keyboard.println(user);
          totals[2]+=1;
            break;
        }

        case 10:
        {
          char userno[]="RYA";
          for(int i=0;i<sizeof(user);i++)
          {
            user[i]=userno[i];
          }
          Keyboard.print(prefix);
          Keyboard.println(user);
          totals[3]+=1;
            break;
        }
        case 6:
        {
          char userno[]="JJJ";
          for(int i=0;i<sizeof(user);i++)
          {
            user[i]=userno[i];
          }
          Keyboard.print(prefix);
          Keyboard.println(user);
          totals[4]+=1;
            break;
        }
        case 3:
        {
          printTotals();
            break;
        }
    }
    prevprint=current;
  }
  else {prevprint=current;}
}

void printTotals()
{
  char userno[]="123";
  
  for(int i=0;i<9;i++){
    if(totals[i])
    {
      switch(i)
      {
        case 0:
        {
          char usertotal[]="189";
          for(int i=0;i<sizeof(userno);i++)
          {
            userno[i]=usertotal[i];
          }
          break;
        }
        case 1:
        {
          char usertotal[]="021";
          for(int i=0;i<sizeof(userno);i++)
          {
            userno[i]=usertotal[i];
          }
          break;
        }
        case 2:
        {
          char usertotal[]="053";
          for(int i=0;i<sizeof(userno);i++)
          {
            userno[i]=usertotal[i];
          }
          break;
        }
        case 3:
        {
          char usertotal[]="RYA";
          for(int i=0;i<sizeof(userno);i++)
          {
            userno[i]=usertotal[i];
          }
          break;
        }
        case 4:
        {
          char usertotal[]="JJJ";
          for(int i=0;i<sizeof(userno);i++)
          {
            userno[i]=usertotal[i];
          }
          break;
        }
      }
      Keyboard.print(userno);
      Keyboard.print(" packed ");
      Keyboard.print(totals[i]);
      Keyboard.println(" packages");
    }
  }
}

