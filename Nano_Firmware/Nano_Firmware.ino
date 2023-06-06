#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define white SH110X_WHITE



// I/O pins for controlling everything
#define tonePin 11
#define selfActivationPin 12
#define knobPin 5

#define cell1Pin A0
#define cell2Pin A1
#define cell3Pin A2
#define cell4Pin A3
#define cell5Pin A6
#define cell6Pin A7

#define ALL_CELLS 7

int cellPins[6] = {cell1Pin, cell2Pin, cell3Pin, cell4Pin, cell5Pin, cell6Pin};
float cellVoltages[6] = {0, 0, 0, 0, 0, 0};

unsigned long voltageUpdaterTimer = 0;
int voltageUpdaterTimerDelay = 100;

void setup() {
  pinMode(selfActivationPin, OUTPUT);
  digitalWrite(selfActivationPin, HIGH);
  pinMode(tonePin, OUTPUT);
  pinMode(knobPin, INPUT_PULLUP);
  
  pinMode(cell1Pin, INPUT);
  pinMode(cell2Pin, INPUT);
  pinMode(cell3Pin, INPUT);
  pinMode(cell4Pin, INPUT);
  pinMode(cell5Pin, INPUT);
  pinMode(cell6Pin, INPUT);

  display.begin(i2c_Address, true);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.drawPixel(10, 10, white);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();

  success_tone();
  
}

void loop() {
  update_cell_voltage();
  sanity_check();
  
  if(voltageUpdaterTimer < millis()){
    update_cell_voltage();
    voltageUpdaterTimer = millis() + voltageUpdaterTimerDelay;
  }

}

void sanity_check(){
  if(cell_delta() > 0.1){
    emergency_cutoff();
  }
  for(int il = 0; il < 6; il++){
    if(cellVoltages[il] / (il + 1) < 3.6){
      emergency_cutoff();
    }
  }
}

float cell_delta(){
  float lowest = cellVoltages[0];
  float highest = cellVoltages[0];
  for(int il = 0; il < 6; il++){
    if(lowest > cellVoltages[il]){
      lowest = cellVoltages[il];
    }
    else if(highest < cellVoltages[il]){
      highest = cellVoltages[il];
    }
  }
  return highest - lowest;
}

void emergency_cutoff(){
  digitalWrite(selfActivationPin, LOW);
}

void success_tone(){
  int arr_length = 10;
  int durations[arr_length] = {250, 250, 250, 250, 0, 0, 0, 0, 0, 0};
  int notes[arr_length] = {440, 440, 440, 1000, 0, 0, 0, 0, 0, 0};

  for(int i = 0; i < arr_length; i++){
    tone(tonePin, notes[i]);
    delay(durations[i]);
    noTone(tonePin);
  }
}

void get_cell_voltage(int cellNum){}

void update_cell_voltage(){
  for(int il = 0; il < 6; il++){
    cellVoltages[il] = analogRead(cellPins[il]) * 5.0 / 1024.0 * (il + 1.0);
  }
}