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
    LACHT,
    SCHLAEFT
};

struct Animation {
    const uint8_t* const* frames; // Array von Frame-Pointern
    uint8_t frameCount;           // Anzahl Frames
    uint16_t frameDelayMs;        // Wie lange ein Frame angezeigt wird
    uint8_t width;                // z.B. 20
    uint8_t height;               // z.B. 20
};

void initialisiereSmartPlant();
void zeigeLadebildschirm();

void setzeLEDFarbe(LED_Farbe farbe);
void setzeEmotion(Emotion emotion);
void spieleAnimation(Emotion emotion);
void aktiviereFeuchtigkeitswertAufDisplay();
int leseFeuchtigkeitswertInProzent(int messwert_nass, int messwert_trocken);
int leseLichtInProzent(int messwert_hell, int messwert_dunkel);
void aktualisiereDisplay();

#endif