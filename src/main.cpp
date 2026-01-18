#include <Arduino.h>
#include "../lib/smartplant/src/SmartPlant.h"

// Kalibrierung
static constexpr int TROCKEN = 600; // 0 %
static constexpr int NASS = 200; // 100 %

void setup()
{
  initialisiereSmartPlant();
  aktiviereFeuchtigkeitswertAufDisplay();
}

void loop()
{
  int feuchtigkeit = leseFeuchtigkeitswertInProzent(NASS, TROCKEN);

  if (feuchtigkeit < 10)
  {
    setzeLEDFarbe(ROT);
    setzeEmotion(TRAURIG);
  }
  if (feuchtigkeit > 10 && feuchtigkeit < 50)
  {
    setzeLEDFarbe(GELB);
    setzeEmotion(NEUTRAL);
  }
  if (feuchtigkeit > 50)
  {
    setzeLEDFarbe(GRUEN);
    setzeEmotion(GLUECKLICH);
  }

  aktualisiereDisplay();
  delay(1000);
}
