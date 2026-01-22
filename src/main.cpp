#include <Arduino.h>
#include "../lib/smartplant/src/SmartPlant.h"

int licht = 0;
int wasser = 0;

const int TROCKEN = 600;
const int NASS = 200;

const int HELL = 800;
const int DUNKEL = 50;

void setup()
{
  initialisiereSmartPlant();
  aktiviereMesswerteAufDisplay();

  setzeLEDFarbe(AUS);
}

void loop()
{
  licht = leseLichtInProzent(DUNKEL, HELL);
  wasser = leseFeuchtigkeitswertInProzent(NASS, TROCKEN);

  setzeEmotion(SCHLAEFT);

  aktualisiereDisplay();
  delay(100);
}
