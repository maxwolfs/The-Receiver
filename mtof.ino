#include <MIDI.h>
#include <elapsedMillis.h>

elapsedMicros timeElapsed;
MIDI_CREATE_DEFAULT_INSTANCE();

#define SOL 3

boolean solState = LOW;
boolean isPlaying = false;
byte pitch;
float midival;
float intvl;
float freq;

float mtof(float pitch)
{
  // http://en.wikipedia.org/wiki/Note
  // f = pow(2,(p-69/12) * 440Hz
  // return pow(2.0,(midival-69.0/12.0) * 440.0;

  // code from AF_precision_synthesis sketch, copyright 2009, Adrian Freed.
  float f = 0.0;
  if (pitch) f = 8.1757989156 * pow(2.0, pitch / 12.0);
  return f;
}

float inter(float freq)
{
  float f = 1 / freq * 1000000.0 / 2.0;
  return f;
}

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  freq = mtof(float(pitch));
  intvl = inter(freq);
  timeElapsed = 0;
  isPlaying = true;
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  digitalWrite(SOL, solState);
  isPlaying = false;
}

void playNote()
{
  if (isPlaying) {
    if (timeElapsed >= intvl) {
      timeElapsed = 0;
      solState = !solState;
      digitalWrite(SOL, solState);
    }
  } else digitalWrite(SOL, LOW);
}

void setup()
{
  pinMode(SOL, OUTPUT);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.begin();
}

void loop()
{
  MIDI.read();
  playNote();
}

