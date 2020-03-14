#include "pitches.h"

const int piezoPin = 12;
const int rPin = 5;
const int gPin = 4;
const int bPin = 3;
const int pPin = 2;

int ledState = 0;
int ledOn = false;

int melody[] = {
  NOTE_F5, NOTE_D5, NOTE_AS4, NOTE_D5, NOTE_F5, NOTE_AS5, NOTE_D6, NOTE_C6, NOTE_AS5, NOTE_D5, NOTE_E5, NOTE_F5,
  NOTE_F5, NOTE_F5, NOTE_D6, NOTE_C6, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_AS5, NOTE_AS5, NOTE_F5, NOTE_D5, NOTE_AS4,
  NOTE_D6, NOTE_D6, NOTE_D6, NOTE_DS6, NOTE_F6, NOTE_F6, NOTE_DS6, NOTE_D6, NOTE_C6, NOTE_D6, NOTE_DS6,
  0, NOTE_DS6, NOTE_D6, NOTE_C6, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_AS5, NOTE_D5, NOTE_E5, NOTE_F5,
  NOTE_F5, NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_C6, NOTE_DS6, NOTE_D6, NOTE_C6, NOTE_AS5, NOTE_AS5, NOTE_A5,
  NOTE_F5, NOTE_F5, NOTE_AS5, NOTE_C6, NOTE_D6, NOTE_DS6, NOTE_F6, NOTE_AS5, NOTE_C6, NOTE_D6, NOTE_DS6, NOTE_C6, NOTE_AS5
};

float noteDurations[] = {
  6, 12, 4, 4, 4, 2, 6, 12, 4, 4, 4, 2,
  8, 8, 8 / 2.9, 8, 4, 2, 8, 8, 4, 4, 4, 4, 4,
  6, 12, 4, 4, 4, 2, 8, 8, 4, 4, 4, 2,
  8, 8, 8 / 2.9, 8, 4, 2, 8, 8, 4, 4, 4, 2,
  4, 4, 4, 8, 8, 4, 4, 4, 4, 8, 8, 8, 8, 4, 4,
  8, 8, 8 / 2.9, 8, 8, 8, 2, 8, 8, 4, 4, 4, 2
};

int musicLength = sizeof(melody) / sizeof('NOTES_F5');

void setup() {
  // put your setup code here, to run once:
  pinMode(pPin, INPUT);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pPinState = digitalRead(pPin);
  if (pPinState == HIGH) {
    ledState = 1;
  }

  if (pPinState == LOW and ledState == 1) {
    ledState = 2;
    ledOn = not ledOn;
  }

  if (ledOn && pPinState != HIGH) {
    //if(true){
    //Use this if button control isn't working properly
    for (int thisNote = 0; thisNote < musicLength; thisNote++) {
      if (thisNote % 3 == 0) {
        digitalWrite(rPin, HIGH);
        digitalWrite(gPin, LOW);
        digitalWrite(bPin, LOW);
      }
      else if (thisNote % 3 == 1) {
        digitalWrite(rPin, LOW);
        digitalWrite(gPin, HIGH);
        digitalWrite(bPin, LOW);
      }
      else if (thisNote % 3 == 2) {
        digitalWrite(rPin, LOW);
        digitalWrite(gPin, LOW);
        digitalWrite(bPin, HIGH);
      }
      int noteDuration = 2000 / noteDurations[thisNote];
      tone(piezoPin, melody[thisNote], noteDuration);

      float pauseBetweenNotes = noteDuration * 1.30;

      delay(pauseBetweenNotes / 2);
      if (digitalRead(pPin) == HIGH) {
        break;
      }
      delay(pauseBetweenNotes / 2);
      if (digitalRead(pPin) == HIGH) {
        break;
      }
    }
  }
  else if (not ledOn) {
    digitalWrite(rPin, LOW);
    digitalWrite(gPin, LOW);
    digitalWrite(bPin, LOW);
  }
}
