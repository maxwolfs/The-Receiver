/*  Polyphonic Pin Printer Synthesizer by Maximilian Wolfs. (c) Copyright 2017
    Midi Input -> Midi to Frequency Interval -> Output
*/

#include <MIDI.h>
#include <elapsedMillis.h>

elapsedMicros timeElapsed1;
elapsedMicros timeElapsed2;
elapsedMicros timeElapsed3;
elapsedMicros timeElapsed4;
/*elapsedMicros timeElapsed5;
elapsedMicros timeElapsed6;
elapsedMicros timeElapsed7;
elapsedMicros timeElapsed8;*/
elapsedMicros timerArray[] = {&timeElapsed1,&timeElapsed2,&timeElapsed3,&timeElapsed4};

MIDI_CREATE_DEFAULT_INSTANCE();

int solPin[] = {5, 8, 10, 4}; // Solenoid Pins
#define solCnt 4 // total of active Solenoids

int intvlArray[solCnt]; // array to save pitches
byte rawPitch[solCnt];

int counter = 0; // counter that increments per handleNoteOn
boolean solState[] = {LOW, LOW, LOW, LOW};  // init state of Solenoids
boolean isPlaying[] = {false, false, false, false}; // init state of Solenoids
byte pitch; //
float midival;
float intvl;
float freq;

float mtof(float pitch)
{
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
  rawPitch[counter % solCnt] = pitch;
  freq = mtof(float(pitch));
  intvl = inter(freq);
  intvlArray[counter % solCnt] = intvl;
  timerArray[counter % solCnt] = 0;
  isPlaying[counter % solCnt] = true;
  counter++;
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  for (int i = 0; i < solCnt; i++) {
    if (rawPitch[i] == pitch) {
      digitalWrite(solPin[i], solState[i]);
      isPlaying[i] = false;
    }
  }
}

void playNote()
{
  for (int i = 0; i < solCnt; i++)
  {
    if (isPlaying[i]) {
      if (timerArray[i] >= intvlArray[i]) {
        timerArray[i] = 0;
        solState[i] = !solState[i];
        digitalWrite(solPin[i], solState[i]);
      }
    } else digitalWrite(solPin[i], LOW);
  }
}

void setup()
{
  for (int i = 0; i < solCnt; i++)
  {
    pinMode(solPin[i], OUTPUT);
  }
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.begin();
}

void loop()
{
  MIDI.read();
  playNote();
}

