#include "pitches.h""

#define WEB_OUT D4
#define TONE_OUT D0
#define TI_IN D6

int notes[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5,
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  
  NOTE_D5, NOTE_D5, NOTE_CS5, NOTE_B4, 0, NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_A4, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_D5,
  NOTE_D5, NOTE_D5, NOTE_CS5, NOTE_B4, 0, NOTE_B4, NOTE_CS5, NOTE_D5, NOTE_CS5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_CS5, NOTE_B4, NOTE_A4,
  0, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5, 0, 0, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_GS4, NOTE_GS4, NOTE_FS4, NOTE_FS4,
  
  NOTE_A3, NOTE_GS4, NOTE_A4, NOTE_E6, NOTE_FS6, NOTE_E6,
  NOTE_A4, NOTE_E5, NOTE_FS5, NOTE_E6, NOTE_FS6, NOTE_E6,
  NOTE_CS5, NOTE_GS5, NOTE_A5, 0, NOTE_B5, NOTE_CS6, NOTE_B5, NOTE_A5, NOTE_E6
  };

float beats[] = {
  8, 8, 8, 4, 4, 4, 4, 8, 8, 8, 8, 8,
  8, 8, 8, 4, 4, 4, 4, 8, 8, 8, 8, 8,
  8, 8, 8, 4, 4, 4, 4, 8, 8, 8, 8, 8,
  8, 8, 8, 4, 4, 4, 4, 8, 8, 8, 8, 8,
  
  3, 4, 8, 1.5, 2, 8, 4, 4, 2, 4, 8, 4, 8, 8,
  3, 4, 8, 4, 1.25, 8, 4, 8, 4, 4, 4, 4, 8, 4, 4,
  4, 4, 4, 8, 8, 1, 4, 8, 8, 8, 8, 8, 4, 8, 8, 1.75,
  
  1, 1, 1, 3, 3, 4,
  1, 1, 1, 3, 3, 4,
  1, 1, 1, 4, 8, 4, 4, 3, 1
};

void setup() {
    pinMode(WEB_OUT, OUTPUT);
    pinMode(TI_IN, INPUT);
    Particle.function("drive",drive);
    digitalWrite(WEB_OUT, LOW);
    //digitalWrite(TI_IN, LOW);

}

void loop() {
    if (digitalRead(TI_IN) == HIGH) {
        playSound();
    }
}

int drive(String args) {
    digitalWrite(WEB_OUT, HIGH);
    delay(500);
    digitalWrite(WEB_OUT, LOW);
    return 1;
}

void playSound() {
    for (int thisNote = 0; thisNote < sizeof(notes)/sizeof(notes[0]); thisNote++) {
        int noteDuration = 1000 / (beats[thisNote] * 174/60) * 3;
        tone(TONE_OUT, notes[thisNote], noteDuration);
        
        int pause = noteDuration;
        delay(pause);
        // stop the tone playing:
        noTone(TONE_OUT);
    }
}
