#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SmartPlant.h"

// PINS
static constexpr uint8_t SENSOR = A0;
static constexpr uint8_t SENSOR_STROMVERSORGUNG = 7;
static constexpr uint8_t LED_ROT = 3;
static constexpr uint8_t LED_GELB = 5;

// DISPLAY EINSTELLUNGEN
static constexpr int SCREEN_WIDTH = 128;
static constexpr int SCREEN_HEIGHT = 64;
static constexpr uint8_t OLED_ADDR = 0x3C;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Messwerte
int prozent_feuchtigkeit = 0;
int messwert_feuchtigkeit = 0;
// Statuswerte
bool zeigeFeuchtigkeit = false;
Emotion emotion = NEUTRAL;

// #######################################################################################################

void initialisiereSmartPlant()
{
    Serial.begin(115200);

    pinMode(SENSOR_STROMVERSORGUNG, OUTPUT);
    pinMode(LED_ROT, OUTPUT);
    pinMode(LED_GELB, OUTPUT);

    Wire.begin();

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR))
    {
        boolean ledBlink = false;
        for (;;)
        {
            setzeLEDFarbe(ledBlink ? ROT : AUS);
            ledBlink = !ledBlink;
            delay(200);
        }
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.drawRect(10,10,10,10,WHITE);
    display.display();
}

// #######################################################################################################

void setzeLEDFarbe(LED_Farbe farbe)
{
  if (farbe == ROT)
  {
    digitalWrite(LED_ROT, HIGH);
    digitalWrite(LED_GELB, LOW);
  }
  if (farbe == GELB)
  {
    digitalWrite(LED_ROT, LOW);
    digitalWrite(LED_GELB, HIGH);
  }
  if (farbe == AUS)
  {
    digitalWrite(LED_ROT, LOW);
    digitalWrite(LED_GELB, LOW);
  }
}

int rechneMesswertInProzentUm(int raw, int messwert_nass, int messwert_trocken)
{
  raw = constrain(raw, messwert_nass, messwert_trocken);
  return map(raw, messwert_trocken, messwert_nass, 0, 100);
}

int leseFeuchtigkeitswertInProzent(int messwert_nass, int messwert_trocken)
{
  digitalWrite(SENSOR_STROMVERSORGUNG, HIGH);
  delay(10);
  messwert_feuchtigkeit = analogRead(SENSOR);
  digitalWrite(SENSOR_STROMVERSORGUNG, LOW);
  prozent_feuchtigkeit = rechneMesswertInProzentUm(messwert_feuchtigkeit, messwert_nass, messwert_trocken);
  return prozent_feuchtigkeit;
}

void aktiviereFeuchtigkeitswertAufDisplay()
{
  zeigeFeuchtigkeit = true;
}

void setzeEmotion(Emotion neueEmotion)
{
  emotion = neueEmotion;
}

void aktualisiereDisplay()
{
  display.clearDisplay();

  if (zeigeFeuchtigkeit)
  {
    display.setTextSize(1);
    display.setCursor(100, 0);
    display.println(messwert_feuchtigkeit);
    display.setCursor(100, 9);
    display.println(String(prozent_feuchtigkeit) + "%");
  }

  if (emotion == NEUTRAL)
  {
    display.setTextSize(4);
    display.setCursor(5, 20);
    display.println(":|");
  }
  else if (emotion == TRAURIG) {
    display.setTextSize(4);
    display.setCursor(5, 20);
    display.println(":(");
  }
  else if (emotion == GLUECKLICH) {
    display.setTextSize(4);
    display.setCursor(5, 20);
    display.println(":)");
  }
  else if (emotion == LACHT) {
    display.setTextSize(4);
    display.setCursor(5, 20);
    display.println(":D");
  }

  display.display();
}