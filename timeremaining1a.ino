/*
 * time remaining 
 * v.1.1a - time remaining system - original sketch by Nicu FLORICA (niq_ro)
 */


// http://tronixstuff.com/2011/03/16/tutorial-your-arduinos-inbuilt-eeprom/
#include <EEPROM.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h> // https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

#include <Wire.h>
#include "RTClib.h"
#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

RTC_DS1307 rtc;

unsigned int timp, timp0, timp1, dtimp;
int zi, ora, minut, secunda;
unsigned long dzi, dora;
int dminut, dsecunda;
int clocire = 22;  // number of days

byte tip = 0;

#define START 8    // START switch
#define STOP 7    // STOP switch

void setup() {
 Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  lcd.begin();  // initialize the LCD 
  lcd.backlight();  // Turn on the blacklight and print a message.
  lcd.clear();  // clear screen

// set push buttons for menu
  pinMode(START, INPUT); 
  pinMode(STOP, INPUT);  
  digitalWrite(START, HIGH); // pull-ups on
  digitalWrite(STOP, HIGH); // pull-ups on

tip = EEPROM.read(101);

  lcd.setCursor(0,0);  
  lcd.print("original sketch"); 
  lcd.setCursor(0,1);  
  lcd.print("by niq_ro");
delay(3000);
lcd.clear(); 


}

void loop() {

if (tip == 17)
{
DateTime now = rtc.now();
zi = now.day(), DEC;
ora = now.hour(), DEC;
minut = now.minute(), DEC;
secunda = now.second(), DEC;
timp = (zi-1) * 1440 + ora * 60 + minut; 

timp1 = clocire * 1440; 
// timp1 = 3600;

if (timp > timp1)
{
  tip = 0;
  lcd.clear();
  EEPROM.write(101,tip);
  lcd.setCursor(0,0);  
  lcd.print("original sketch");  
}


dtimp = timp1 - timp;
Serial.println(dtimp);
dzi = dtimp/1440;
dtimp = dtimp%1440;
dora = dtimp/60;
dminut = dtimp%60;

  lcd.setCursor(0,0);  
  lcd.print("Time Remaining:"); 
  lcd.setCursor(0,1); 
  if (dzi < 10) lcd.print(" ");  
  lcd.print(dzi); 
  lcd.print("d:");
  if (dora < 10) lcd.print(" ");  
  lcd.print(dora); 
  lcd.print("h:");  
  if (dminut < 10) lcd.print(" ");  
  lcd.print(dminut); 
  lcd.print("m ");  

  byte secundar = secunda;
  if (secundar%4 == 0) lcd.print(" | ");  
  else
  if (secundar%4 == 1) lcd.print(" < ");
  else
  if (secundar%4 == 2) lcd.print(" | "); 
  else   
  if (secundar%4 == 3) lcd.print(" > "); 
}

if (digitalRead(START) == LOW)
{
  tip = 17;
  EEPROM.write(101,tip);
// January 1, 1973 at 0am you would call:
rtc.adjust(DateTime(1973, 1, 1, 0, 0, 0));
timp0 = 0*24*60*60;  // initial time
}
  
if (digitalRead(STOP) == LOW)
{
  tip = 0;
  lcd.clear();
  EEPROM.write(101,tip);
// January 1, 1973 at 0am you would call:
rtc.adjust(DateTime(1973, 1, 1, 0, 0, 0));
timp0 = 0*24*60*60;  // initial time
}

  delay(50); 
}
