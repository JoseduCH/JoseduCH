#include <Arduino.h>

#include <ESP32-TWAI-CAN.hpp>
#include <DHTesp.h>

#define DHTPIN 15
#define CAN_TX 5
#define CAN_RX 4

DHTesp dht;

bool leerDHT();
void enviarCAN();

float temperatura, humedad;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
  delay(1000);
  dht.setup(DHTPIN, DHTesp::DHT11);

  Serial.println("CAN sender");

  ESP32Can.setPins(CAN_TX, CAN_RX);

  // Velocidad, pines, y tamaño de colas TX/RX
  if (!ESP32Can.begin(ESP32Can.convertSpeed(500), CAN_TX, CAN_RX, 10, 10)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  Serial.println("Lectura de Temperatura y Humedad con DHT11");
  delay(100);
}

void enviarCAN() {
  Serial.print("\nEnviando paquete... ");
  // Escalamos x10 para conservar un decimal (ej. 23.5 -> 235) y no truncar el valor real
  int16_t tempEnviar = (int16_t)round(temperatura * 10);
  int16_t humEnviar  = (int16_t)round(humedad * 10);

  CanFrame frame         = {0};
  frame.identifier       = 0x100;
  frame.extd             = 0;      // ID estándar (11 bits)
  frame.data_length_code = 4;
  frame.data[0] = (tempEnviar >> 8) & 0xFF; // byte alto temperatura
  frame.data[1] = tempEnviar & 0xFF;        // byte bajo temperatura
  frame.data[2] = (humEnviar >> 8) & 0xFF;  // byte alto humedad
  frame.data[3] = humEnviar & 0xFF;         // byte bajo humedad

  if (ESP32Can.writeFrame(frame)) {
    Serial.println("Mensaje enviado");
  } else {
    Serial.println("Error al enviar");
  }
}

bool leerDHT() {
  temperatura = dht.getTemperature();
  humedad = dht.getHumidity();

  if (isnan(temperatura) || isnan(humedad)) {
    Serial.println("Error al leer el DHT11");
    return false;
  } else {
    return true;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (leerDHT()) {
    enviarCAN();
    Serial.print("Temperatura: ");
    Serial.println(temperatura);

    Serial.print("Humedad: ");
    Serial.println(humedad);
  }
  delay(1000);
}
