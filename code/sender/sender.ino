#include <MIDI.h>
#include <elapsedMillis.h>

elapsedMillis timeElapsed;

MIDI_CREATE_DEFAULT_INSTANCE();

const int channel = 1;
const int velocity = 100;
int note1;
int note2;
int note3;
int intvl;


void setup()
{
  MIDI.begin();
}

void noteRandomizer() {
  note1 = random(30, 50);
  note2 = note1 + 4;
  note3 = note1 + 8;
}

void intvlRandomizer() {
  intvl = random(100,200);
}

void loop()
{
  noteRandomizer();
  intvlRandomizer();
  if (timeElapsed >= intvl) {
    timeElapsed = 0;
    MIDI.sendNoteOn(note1, velocity, channel);
    MIDI.sendNoteOn(note2, velocity, channel);
    MIDI.sendNoteOn(note3, velocity, channel);
  } else {
    MIDI.sendNoteOff(note1, velocity, channel);
    MIDI.sendNoteOff(note2, velocity, channel);
    MIDI.sendNoteOff(note3, velocity, channel);
  }

  //MIDI.sendControlChange(123, 0, 1);
}
