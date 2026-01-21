#include <Arduino.h>
#include "../lib/smartplant/src/SmartPlant.h"

// Kalibrierung
static constexpr int TROCKEN = 600; // 0 %
static constexpr int NASS = 200;    // 100 %

static constexpr int DUNKEL = 50; // 0 %
static constexpr int HELL = 800;  // 100 %

void setup()
{
  initialisiereSmartPlant();
  //aktiviereFeuchtigkeitswertAufDisplay();

  setzeLEDFarbe(ROT);
  delay(400);
  setzeLEDFarbe(GELB);
  delay(400);
  setzeLEDFarbe(GRUEN);
  delay(400);
}

int letzter_Feuchtigkeitswert = 0;
int aktueller_Feuchtigkeitswert = 0;

void loop()
{
  letzter_Feuchtigkeitswert = aktueller_Feuchtigkeitswert;
  aktueller_Feuchtigkeitswert = leseFeuchtigkeitswertInProzent(TROCKEN, NASS);
  int licht = leseLichtInProzent(DUNKEL, HELL);

  if (licht < 30)
  {
    setzeLEDFarbe(AUS);
    setzeEmotion(SCHLAEFT);
  }
  else
  {
    if (aktueller_Feuchtigkeitswert < 10)
    {
      setzeLEDFarbe(ROT);
      setzeEmotion(TRAURIG);
    }
    if (aktueller_Feuchtigkeitswert > 10 && aktueller_Feuchtigkeitswert < 30)
    {
      setzeLEDFarbe(GELB);
      setzeEmotion(NEUTRAL);
    }
    if (aktueller_Feuchtigkeitswert > 30)
    {
      if( aktueller_Feuchtigkeitswert-5 > letzter_Feuchtigkeitswert ) {
        for(uint8_t i = 0; i < 3; i++) {
          spieleAnimation(LACHT);
        }
      }
      setzeLEDFarbe(GRUEN);
      setzeEmotion(GLUECKLICH);
    }
  }

  aktualisiereDisplay();
  delay(1000);
}
