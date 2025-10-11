#include "RF24.h"
#include <SPI.h>
#include <ezButton.h>
#include "esp_bt.h"
#include "esp_wifi.h"

// Pines HSPI
#define HSPI_CE   4
#define HSPI_CSN  15
#define HSPI_SCK  5
#define HSPI_MOSI 13
#define HSPI_MISO 12

// Pines VSPI
#define VSPI_CE   22
#define VSPI_CSN  21
#define VSPI_SCK  18
#define VSPI_MOSI 23
#define VSPI_MISO 19

SPIClass *sp = nullptr;
SPIClass *hp = nullptr;

RF24 radio(HSPI_CE, HSPI_CSN, 16000000);   // HSPI
RF24 radio1(VSPI_CE, VSPI_CSN, 16000000);  // VSPI

ezButton toggleSwitch(33);

unsigned int flag = 0;

unsigned int flagv = 0;

int ch = 45;

int ch1 = 45;

// Detección de clics
unsigned long lastPressTime = 0;
int clickCount = 0;
const int DOUBLE_CLICK_TIME = 400; // ms
bool modoActivado = false; // true=two(), false=one()

// --------------------------------------------------------------------
void two() {
if (flagv == 0) ch1 += 4; else ch1 -= 4;
if (flag == 0) ch += 2; else ch -= 2;

if ((ch1 > 79) && (flagv == 0)) flagv = 1;
else if ((ch1 < 2) && (flagv == 1)) flagv = 0;

if ((ch > 79) && (flag == 0)) flag = 1;
else if ((ch < 2) && (flag == 1)) flag = 0;

radio.setChannel(ch);
radio1.setChannel(ch1);
}

// --------------------------------------------------------------------
void one() {
radio1.setChannel(random(80));
radio.setChannel(random(80));
delayMicroseconds(random(60));
}

// --------------------------------------------------------------------
void setup() {
Serial.begin(115200);
esp_bt_controller_deinit();
esp_wifi_stop();
esp_wifi_deinit();
esp_wifi_disconnect();
toggleSwitch.setDebounceTime(50);

initHP();
initSP();
}

// --------------------------------------------------------------------
void initSP() {
sp = new SPIClass(VSPI);
sp->begin(VSPI_SCK, VSPI_MISO, VSPI_MOSI, VSPI_CSN);
if (radio1.begin(sp)) {
Serial.println("VSPI Started !!!");
radio1.setAutoAck(false);
radio1.stopListening();
radio1.setRetries(0, 0);
radio1.setPALevel(RF24_PA_MAX, true);
radio1.setDataRate(RF24_2MBPS);
radio1.setCRCLength(RF24_CRC_DISABLED);
radio1.printPrettyDetails();
radio1.startConstCarrier(RF24_PA_MAX, ch1);
} else {
Serial.println("VSPI couldn't start !!!");
}
}

// --------------------------------------------------------------------
void initHP() {
hp = new SPIClass(HSPI);
hp->begin(HSPI_SCK, HSPI_MISO, HSPI_MOSI, HSPI_CSN);
if (radio.begin(hp)) {
Serial.println("HSPI Started !!!");
radio.setAutoAck(false);
radio.stopListening();
radio.setRetries(0, 0);
radio.setPALevel(RF24_PA_MAX, true);
radio.setDataRate(RF24_2MBPS);
radio.setCRCLength(RF24_CRC_DISABLED);
radio.printPrettyDetails();
radio.startConstCarrier(RF24_PA_MAX, ch);
} else {
Serial.println("HSPI couldn't start !!!");
}
}

// --------------------------------------------------------------------
void loop() {
toggleSwitch.loop();

if (toggleSwitch.isPressed()) {
unsigned long now = millis();
if (now - lastPressTime <= DOUBLE_CLICK_TIME) {
clickCount++;
} else {
clickCount = 1;
}
lastPressTime = now;
}

// Revisa si se pasó el tiempo de doble clic
if (clickCount > 0 && millis() - lastPressTime > DOUBLE_CLICK_TIME) {
if (clickCount == 1) {
modoActivado = true;  // un clic → activado
Serial.println("✅ Activado modo controlado (two)");
} else if (clickCount >= 2) {
modoActivado = false; // doble clic → desactivado
Serial.println("❌ Desactivado modo controlado, modo aleatorio (one)");
}
clickCount = 0;
}

// Ejecutar según el modo
if (modoActivado)
two();
else
one();
}