#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// I/O pins for controlling everything
#define tonePin 11
#define selfActivationPin 1
#define knobPin 5

#define cell1Pin A0
#define cell2Pin A1
#define cell3Pin A2
#define cell4Pin A3
#define cell5Pin A6
#define cell6Pin A7


void setup() {
  pinMode(selfActivationPin, OUTPUT);
  pinMode(tonePin, OUTPUT);
  pinMode(knobPin, INPUT_PULLUP);
  success_tone();
  
}

void loop() {
  

}


void success_tone(){
  int arr_length = 10;
  int durations[arr_length] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int notes[arr_length] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  for(int i = 0; i < arr_length; i++){
    tone(tonePin, notes[i], durations[i]);
  }
}