#include "hid_midi.h"

using namespace daisy;

// Masks to check for message type, and byte content
const uint8_t kStatusByteMask = 0x80;
const uint8_t kMessageMask      = 0x70;
const uint8_t kDataByteMask = 0x7F;
const uint8_t kSystemCommonMask = 0xF0;
const uint8_t kChannelMask = 0x0F;
const uint8_t kRealTimeMask = 0xF8;

// TODO:
// - provide an input interface so USB or UART data can be passed in.
//     this could even be as simple as a buffer/new flag.
void MidiHandler::Init()
{

}

// TODO: 
// double check for packet size...
// right now I'm only handling one message
// I have a feeling a packet can contain many
MidiEvent MidiHandler::Parse(uint8_t *buffer, size_t size)
{

    // check first byte
    uint8_t sb, *db, channel;
    size_t expected_packet_size;
    bool valid;
    // Get bytes in place

    sb      = (buffer[0] & kMessageMask) >> 4;
    channel = (buffer[0] & kChannelMask);
    db = buffer + 1;
    // Check Validity
    // TODO: Check number of size for valid MIDI Message
    valid = sb < MessageLast ? true : false;
    // Vars for data.
    // TODO: Move this to a MidiEvent class of some sort that can be passed
    //         out of the parser.
    uint8_t note, velocity; // For note messages
    uint8_t cc, val;
    int16_t pitch_bend;
    MidiEvent event;
    event.note_ = -1;
    event.vel_ = -1;
    event.cc_ = -1;
    event.val_ = -1;
    switch (sb)
    {
        case NoteOn:
        case NoteOff:
        case PolyphonicKeyPressure:
            if (size <= 3)
            {
                event.note_ = db[0];
                event.vel_ = db[1];
            }
            break;
        case ControlChange:
            if(size <= 3)
            {
                event.cc_  = db[0];
                event.val_ = db[1];
            }
            break;
        case ProgramChange:
            break;
        case ChannelPressure:
            break;
        case PitchBend:
            break;
        default:
            break;
    }
    // TODO add output..
    return event;
}
