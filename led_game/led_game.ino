/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
const byte interruptPin = 2;
volatile byte state = LOW;

#include "pitches.h"
#include <LiquidCrystal.h>
 
#define ENC_A 6 //these need to be digital input pins
#define ENC_B 7

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

bool gameStarted = false;

int melody[] = {
  NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,NOTE_A5,NOTE_B5,NOTE_C6,
  NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,NOTE_A5,NOTE_B5,NOTE_C6, 0};
 
int noteDurations[] = {16,16,16,16,16,16,16,16, 16,16,16,16,16,16,16,16,16};

int melodyLose[]={NOTE_C2};
int noteDurationLose[] ={1};

int period = 120;
int previousMillis = 0;
int toggleLED = 0;
int prevGames = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  
  lcd.begin(16, 2);
  lcd.print("Set The Timer!");
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(1, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
}

// the loop function runs over and over again forever
void loop() {
  lcd.setCursor(0, 1);
  static unsigned int counter4x = 0;      //the SparkFun encoders jump by 4 states from detent to detent
  static unsigned int counter = 0;
  static unsigned int prevCounter = 0;
  int tmpdata;
  tmpdata = read_encoder();
  if(tmpdata) {
    counter4x += tmpdata;
    counter = counter4x/4;
    if (prevCounter != counter){
       if(gameStarted == false && counter >= 5){
         lcd.setCursor(0,0);
         lcd.print("Go!           ");
         lcd.setCursor(0,1);
         gameStarted = true; 
       }
       prevCounter = counter;
    }
  }
  if(getTime() >= counter + prevGames){
    if(gameStarted == true){
      lcd.setCursor(0,0);
      lcd.print("           ");
      lcd.setCursor(0,1);
      lcd.print("Time's Up!"); 
      playLose();
      prevGames += getTime();
      lcd.clear();
      lcd.home();
      lcd.print("Set The Timer!");
      gameStarted = false;
      state = LOW;
    } else {
      lcd.print(0);
    }
  } else {
    lcd.print(counter - getTime() + prevGames,10);
    lcd.print(' ');
  }

   unsigned long currentMillis = millis();
   if(currentMillis - previousMillis > period && toggleLED == 0) {
     previousMillis = currentMillis;
     toggleLED = 1;
     if(state == LOW){
       digitalWrite(1, HIGH);   // turn the LED on (HIGH is the voltage level)
       digitalWrite(9, LOW);   // turn the LED on (HIGH is the voltage level)
       digitalWrite(10, LOW);   // turn the LED on (HIGH is the voltage level)
      } else{
        playLose();
        state = LOW;
      }
   }

  currentMillis = millis();
  if(currentMillis - previousMillis > period && toggleLED == 1) {
     previousMillis = currentMillis;
     toggleLED = 2;
     if(state == LOW){
        digitalWrite(1, LOW);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(9, LOW);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
      } else {
        playLose();
        state = LOW;
      }
  }
 

  currentMillis = millis();
  if(currentMillis - previousMillis > period && toggleLED == 2) {
    previousMillis = currentMillis;
    toggleLED = 0;
    if(state == LOW){
      digitalWrite(1, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(9, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(10, LOW);   // turn the LED on (HIGH is the voltage level)
    } else {
      lcd.setCursor(0,0);
      lcd.print("               ");
      lcd.setCursor(0,1);
      lcd.print("You Win!"); 
      playWin();
      prevGames += getTime();
      lcd.clear();
      lcd.home();
      lcd.print("Set The Timer!");
      gameStarted = false;
      state = LOW;
    }
  }
}

void playWin(){
   for (int thisNote = 0; thisNote < 18; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void playLose(){
   for (int thisNote = 0; thisNote < 1; thisNote++) {
    int noteDuration = 1000 / noteDurationLose[thisNote];
    tone(8, melodyLose[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void blink() {
  state = !state;
}


int getTime(){
  return millis() / 1000;
}
 
/* returns change in encoder state (-1,0,1) */
int read_encoder()
{
  static int enc_states[] = {
    0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0  };
  static byte ABab = 0;
  ABab *= 4;                   //shift the old values over 2 bits
  ABab = ABab%16;      //keeps only bits 0-3
  ABab += 2*digitalRead(ENC_A)+digitalRead(ENC_B); //adds enc_a and enc_b values to bits 1 and 0
  return ( enc_states[ABab]);
 
 
}
