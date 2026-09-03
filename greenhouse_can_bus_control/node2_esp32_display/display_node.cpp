#include <Arduino.h>

#include <ESP32-TWAI-CAN.hpp>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// CAN
#define CAN_TX 5
#define CAN_RX 4

// I2C
#define SDA_PIN 21
#define SCL_PIN 22

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    OLED_RESET
);

float temperatura = 0.0;
float humedad = 0.0;

void setup() {

  Serial.begin(115200);
  delay(1000);

  Serial.println("CAN Receiver");

  ESP32Can.setPins(CAN_TX, CAN_RX);

  if (!ESP32Can.begin(
          ESP32Can.convertSpeed(500),
          CAN_TX,
          CAN_RX,
          10,
          10)) {

    Serial.println("Starting CAN failed!");
    while (1);
  }

  Serial.println("CAN iniciado OK");

  // I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Error OLED");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);
  display.println("Protocolo CAN");
  display.display();

  delay(1000);
}

void loop() {

  CanFrame rxFrame;

  if (ESP32Can.readFrame(rxFrame, 1000)) {
    Serial.println("TRAMA RECIBIDA");

    Serial.print("Received packet with id 0x");
    Serial.println(rxFrame.identifier, HEX);

    if (rxFrame.identifier == 0x100 &&
        rxFrame.data_length_code >= 4) {

      int tempH = rxFrame.data[0];
      int tempL = rxFrame.data[1];
      int humH  = rxFrame.data[2];
      int humL  = rxFrame.data[3];

      int16_t tempRaw =
          (int16_t)((tempH << 8) | tempL);

      int16_t humRaw =
          (int16_t)((humH << 8) | humL);

      temperatura = tempRaw / 10.0;
      humedad     = humRaw / 10.0;

      Serial.print("Temperatura: ");
      Serial.println(temperatura);

      Serial.print("Humedad: ");
      Serial.println(humedad);
    }
  } else {
    Serial.println("Error al recibir mensaje");
  }

  // Actualizar OLED
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(0, 5);
  display.print(temperatura, 1);
  display.println(" C");

  display.setCursor(0, 35);
  display.print(humedad, 1);
  display.println(" %");

  display.display();
}