#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <RF24.h>

// Pins for ST7735 (HSPI)
#define TFT_CS 15
#define TFT_DC 21
#define TFT_RST 22
#define TFT_MOSI 13
#define TFT_SCLK 14
#define LED_PIN 2

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
RF24 radio(4, 5); // nRF24L01 on VSPI (Pins 18, 19, 23)
const byte address[6] = "DRN01";

struct Data_Package {
  byte throttle; byte yaw; byte pitch; byte roll;
};
Data_Package data;
unsigned long lastReceiveTime = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);
  
  radio.begin();
  radio.openReadingPipe(1, address);
  
  // MUST MATCH TRANSMITTER EXACTLY
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(110);
  
  radio.startListening();
  
  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
  tft.setCursor(10, 10);
  tft.print("LINK: READY");
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package));
    lastReceiveTime = millis(); // Reset Failsafe timer
    digitalWrite(LED_PIN, HIGH);
    updateDisplay(false); 
  }

  // FAILSAFE: Trigger if no data for > 500ms
  if (millis() - lastReceiveTime > 500) {
    digitalWrite(LED_PIN, LOW);
    
    // Safety values: Cut power, center controls
    data.throttle = 0; 
    data.yaw = 127; data.pitch = 127; data.roll = 127;
    
    updateDisplay(true); 
  }
}

void updateDisplay(bool isFailsafe) {
  tft.setTextSize(1);
  // Color code: Red for Signal Lost, Green for Stable
  tft.setTextColor(isFailsafe ? ST7735_RED : ST7735_GREEN, ST7735_BLACK);
  
  tft.setCursor(10, 110);
  if(isFailsafe) tft.print("!!! SIGNAL LOST !!!");
  else           tft.print("SIGNAL: STABLE     ");

  // Display raw values
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  tft.setCursor(10, 40); tft.printf("THROTTLE: %3d ", data.throttle);
  tft.setCursor(10, 55); tft.printf("YAW:      %3d ", data.yaw);
  tft.setCursor(10, 70); tft.printf("PITCH:    %3d ", data.pitch);
  tft.setCursor(10, 85); tft.printf("ROLL:     %3d ", data.roll);
}
