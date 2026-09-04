#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SI4735.h>

SI4735 radio;

#define RESET_PIN   4
#define SDA_PIN     21
#define SCL_PIN     22

#define CLK         32
#define DT          33

// ======================
// OLED
// ======================
#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT   64
#define OLED_RESET     -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ======================
// VARIABLES
// ======================
uint16_t frequency = 9100;   // 91.00 MHz
int lastCLK;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 5;

unsigned long lastScreenUpdate = 0;
const unsigned long screenInterval = 300;   // ms

// ======================
// MOSTRAR EN PANTALLA
// ======================
void showScreen() {
  // ACTUALIZA RSSI Y SNR
  radio.getCurrentReceivedSignalQuality(0);

  int rssi = radio.getCurrentRSSI();
  int snr  = radio.getCurrentSNR();

  display.clearDisplay();

  // Frecuencia grande
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 5);
  display.print(frequency / 100.0, 1);
  display.println(" MHz");

  // RSSI
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("RSSI: ");
  display.print(rssi);

  // SNR
  display.setCursor(70, 35);
  display.print("SNR: ");
  display.print(snr);

  // Barra RSSI
  int barLength = map(rssi, 0, 60, 0, 120);

  if (barLength > 120) barLength = 120;
  if (barLength < 0) barLength = 0;

  display.drawRect(4, 52, 120, 8, WHITE);
  display.fillRect(4, 52, barLength, 8, WHITE);

  display.display();

  // Monitor serial
  Serial.print("Frecuencia: ");
  Serial.print(frequency / 100.0, 1);
  Serial.print(" MHz  RSSI: ");
  Serial.print(rssi);
  Serial.print("  SNR: ");
  Serial.println(snr);
}

// ======================
// SETUP
// ======================
void setup() {
  Serial.begin(115200);
  delay(1000);

  // I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  // Frecuencia I2C estable
  radio.setI2CFastModeCustom(100000);

  // Encoder
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);

  lastCLK = digitalRead(CLK);

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Error OLED");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.println("Iniciando SI4732...");
  display.display();

  Serial.println("Buscando SI4732...");

  uint8_t addr = radio.getDeviceI2CAddress(RESET_PIN);

  Serial.print("Direccion detectada: 0x");
  Serial.println(addr, HEX);

  // Inicializa radio
  radio.setup(RESET_PIN, 1);
  delay(500);

  // Configuración FM
  radio.setFM(8750, 10800, frequency, 10);
  delay(500);

  // Volumen
  radio.setVolume(63);

  // Mejor recepción
  radio.setFmSoftMuteMaxAttenuation(0);

  showScreen();
}

// ======================
// LOOP
// ======================
void loop() {
  int currentCLK = digitalRead(CLK);

  // Lectura encoder
  if ((millis() - lastDebounceTime) > debounceDelay) {

    if (currentCLK != lastCLK && currentCLK == HIGH) {

      if (digitalRead(DT) != currentCLK) {
        frequency += 10;   // +0.1 MHz
      } else {
        frequency -= 10;   // -0.1 MHz
      }

      // Límites FM
      if (frequency < 8750) frequency = 8750;
      if (frequency > 10800) frequency = 10800;

      // Cambiar estación
      radio.setFrequency(frequency);

      // Esperar estabilización
      delay(100);

      showScreen();

      lastDebounceTime = millis();
    }
  }

  // Actualización periódica de RSSI/SNR
  if (millis() - lastScreenUpdate > screenInterval) {
    showScreen();
    lastScreenUpdate = millis();
  }

  lastCLK = currentCLK;
  delay(1);
}