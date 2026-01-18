#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// PINS
static constexpr uint8_t SOIL_PIN = A0;
static constexpr uint8_t SOIL_VCC = 7; // D7 schaltet den Sensor
static constexpr uint8_t LED_RED = 3;
static constexpr uint8_t LED_YELLOW = 5;

// FARBEN
static constexpr uint8_t ROT = 0;
static constexpr uint8_t GELB = 1;
static constexpr uint8_t GRUEN = 2;
static constexpr uint8_t AUS = 3;

// EMOTIONEN
static constexpr uint8_t TRAURIG = 0;
static constexpr uint8_t NEUTRAL = 1;
static constexpr uint8_t GLUECKLICH = 2;
static constexpr uint8_t LACHT = 3;

// SSD1306 settings
static constexpr int SCREEN_WIDTH = 128;
static constexpr int SCREEN_HEIGHT = 64;
static constexpr uint8_t OLED_ADDR = 0x3C;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Kalibrierung
static constexpr int SOIL_DRY = 600; // 0 %
static constexpr int SOIL_WET = 200; // 100 %

// Messwerte
int feuchtigkeit = 0;
// Statuswerte
bool zeigeFeuchtigkeit = false;
int emotion = NEUTRAL;

int soilPercentFromRaw(int raw)
{
  // Begrenzen
  raw = constrain(raw, SOIL_WET, SOIL_DRY);

  // Umrechnen
  return map(raw, SOIL_DRY, SOIL_WET, 0, 100);
}

void setup()
{
  Serial.begin(115200);

  pinMode(SOIL_VCC, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR))
  {
    for (;;)
    {
      delay(1000);
    }
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(F("Start"));
  display.display();
  delay(800);
}

void setzeLedFarbe(uint8_t farbe)
{
  if (farbe == ROT)
  {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, LOW);
  }
  if (farbe == GELB)
  {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, HIGH);
  }
  if (farbe == AUS)
  {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
  }
}

int leseFeuchtigkeitswertInProzent()
{
  // Sensor einschalten
  digitalWrite(SOIL_VCC, HIGH);
  delay(10); // kurz stabilisieren lassen
  int raw = analogRead(SOIL_PIN);
  // Sensor wieder ausschalten
  digitalWrite(SOIL_VCC, LOW);

  return soilPercentFromRaw(raw);
}

void aktiviereFeuchtigkeitswertAufDisplay()
{
  zeigeFeuchtigkeit = true;
}

void setzeEmotion(int emotion)
{
  emotion = emotion;
}

void aktualisiereDisplay()
{
  display.clearDisplay();

  if (zeigeFeuchtigkeit)
  {
    display.setTextSize(1);
    display.setCursor(100, 0);
    display.println(feuchtigkeit);
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

void loop()
{
  feuchtigkeit = leseFeuchtigkeitswertInProzent();
  aktiviereFeuchtigkeitswertAufDisplay();

  if (feuchtigkeit < 10)
  {
    setzeLedFarbe(ROT);
    setzeEmotion(TRAURIG);
  }
  if (feuchtigkeit > 10 && feuchtigkeit < 50)
  {
    setzeLedFarbe(GELB);
    setzeEmotion(NEUTRAL);
  }
  if (feuchtigkeit > 50)
  {
    setzeLedFarbe(GRUEN);
    setzeEmotion(GLUECKLICH);
  }

  aktualisiereDisplay();
  delay(1000);
}
