#include <MIDI.h>
#include <elapsedMillis.h>

elapsedMillis timeElapsed;
elapsedMillis totalTime;

MIDI_CREATE_DEFAULT_INSTANCE();

const int channel = 1;
const int velocity = 100;
int note1;
int note2;
int note3;
int note4;
int note5;
int note6;
int note7;
int note8;
int intvl;
int chord;
int noteLength;
unsigned long runtime = 120000;
unsigned long pause = 120000;


void setup()
{
  MIDI.begin();
}


void noteRandomizer() {
  chord = random(0, 3);
  switch (chord) {
    case 1:
      note1 = random(30, 50);
      note2 = note1 + 3;
      note3 = note1 + 7;
      note4 = note1 - 12;
      break;
    case 2:
      note1 = random(30, 50);
      note2 = note1 + 4;
      note3 = note1 + 8;
      note4 = note1 + 12;
      break;
    case 3:
      note1 = random(30, 50);
      note2 = note1 + 5;
      note3 = note1 + 9;
      note4 = note1 - 7;
      break;
  }
}

void noteLengthRandomizer() {
  if (totalTime > random(65000, 70000) && totalTime < random(80000, 85000)) {
    noteLength = random(400, 800);
  } else {
    noteLength = 0;
  }
}

void intvlRandomizer() {
  intvl = random(100, 200);
}

void loop()
{
  if (totalTime <= runtime) {
    noteLengthRandomizer();
    noteRandomizer();
    intvlRandomizer();
    if (timeElapsed >= intvl) {
      timeElapsed = 0;
      MIDI.sendNoteOn(note1, velocity, channel);
      MIDI.sendNoteOn(note2, velocity, channel);
      MIDI.sendNoteOn(note3, velocity, channel);
      MIDI.sendNoteOn(note4, velocity, channel);
      delay(noteLength);
    } else {
      MIDI.sendNoteOff(note1, velocity, channel);
      MIDI.sendNoteOff(note2, velocity, channel);
      MIDI.sendNoteOff(note3, velocity, channel);
      MIDI.sendNoteOff(note4, velocity, channel);
    }
  } else {
    delay(pause);
    totalTime = 0;
  }
}
