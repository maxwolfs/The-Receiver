#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

void setup()
{
    MIDI.begin(4);                      // Launch MIDI and listen to channel 4
}

void loop()
{
        MIDI.sendNoteOn(42, 127, 1);    // Send a Note (pitch 42, velo 127 on channel 1)
        delay(1000);                // Wait for a second
        MIDI.sendNoteOff(42, 0, 1);     // Stop the note
         delay(1000);                // Wait for a second
}
