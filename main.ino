#include <arduino.h>
#include "include/IRSensor.h"
#include "include/IRsensorArray.h"

constexpr auto pins_size = 5;
uint16_t pins[pins_size] = {A4, A3, A2, A1, A0};
IRsensorArray ir_sensor_array = make_IRsensorArray(pins, pins_size);

void setup() {
  Serial.begin(9600);
}

void loop() {
  for(uint16_t i = 0; i < ir_sensor_array.size(); ++i){
    Serial.print(pins[i]);
    Serial.print(":");
    Serial.print(ir_sensor_array[i].get_status()?"true":"false");
    Serial.print(" ");
    ir_sensor_array[i].update();
  }
  Serial.println();
}