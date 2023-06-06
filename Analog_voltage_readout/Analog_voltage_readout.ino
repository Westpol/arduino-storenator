#define cell1Pin A0
#define cell2Pin A1
#define cell3Pin A2
#define cell4Pin A3
#define cell5Pin A6
#define cell6Pin A7

int cellPins[6] = {cell1Pin, cell2Pin, cell3Pin, cell4Pin, cell5Pin, cell6Pin};
float cellVoltages[6] = {0, 0, 0, 0, 0, 0};

void setup() {
  pinMode(cell1Pin, INPUT);
  pinMode(cell2Pin, INPUT);
  pinMode(cell3Pin, INPUT);
  pinMode(cell4Pin, INPUT);
  pinMode(cell5Pin, INPUT);
  pinMode(cell6Pin, INPUT);
  Serial.begin(9600);

}

void loop() {
  update_cell_voltage();
  for(int i = 0; i < 6; i++){
    Serial.print(cellVoltages[i]);
    Serial.print("\t");
  }
  Serial.println("");

}


void update_cell_voltage(){
  for(int il = 0; il < 6; il++){
    cellVoltages[il] = (analogRead(cellPins[il]) * 4.7 / 1024.0) * (il + 1.0);
  }
}