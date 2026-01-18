#ifndef SMART_PLANT_H
#define PINSSMART_PLANT_H_H

enum LED_Farbe {
    AUS,
    ROT,
    GELB,
    GRUEN
};

enum Emotion {
    TRAURIG,
    NEUTRAL,
    GLUECKLICH,
    LACHT
};

void initialisiereSmartPlant();

void setzeLEDFarbe(LED_Farbe farbe);
void setzeEmotion(Emotion emotion);
void aktiviereFeuchtigkeitswertAufDisplay();
int leseFeuchtigkeitswertInProzent(int messwert_nass, int messwert_trocken);
void aktualisiereDisplay();

#endif