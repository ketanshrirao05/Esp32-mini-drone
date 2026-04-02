#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define LED_PIN 2
RF24 radio(4, 5); // CE, CSN pins
const byte address[6] = "DRN01"; 

struct Data_Package {
  byte throttle; // Left Stick Y
  byte yaw;      // Left Stick X
  byte pitch;    // Right Stick Y
  byte roll;     // Right Stick X
};
Data_Package data;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  radio.begin();
  radio.openWritingPipe(address);
  
  // RELIABILITY SETTINGS
  radio.setDataRate(RF24_250KBPS); // Max punch for range
  radio.setPALevel(RF24_PA_MAX);   // Highest power level
  radio.setChannel(110);           // Away from 2.4GHz WiFi noise
  radio.setRetries(15, 15);        // 15 retries with 4ms delay
  
  radio.stopListening();
}

void loop() {
  // Read Joysticks (ESP32 ADC 0-4095 mapped to 0-255)
  data.throttle = map(analogRead(34), 0, 4095, 0, 255);
  data.yaw      = map(analogRead(35), 0, 4095, 0, 255);
  data.pitch    = map(analogRead(32), 0, 4095, 0, 255);
  data.roll     = map(analogRead(33), 0, 4095, 0, 255);

  // Send data; success is true only if Receiver confirms receipt (ACK)
  bool success = radio.write(&data, sizeof(Data_Package));
  
  if (success) digitalWrite(LED_PIN, HIGH); 
  else digitalWrite(LED_PIN, LOW);
  
  delay(10); // ~100Hz refresh rate
}
