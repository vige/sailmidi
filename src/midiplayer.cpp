#include "midiplayer.h"
#include "RtMidi.h"
#include "midiportmodel.h"

MidiPlayer::MidiPlayer()
{
    std::cout << "midiplayer constructor called" << std::endl;
    m_midiOut = new RtMidiOut();
    m_midiPortModel = new MidiPortModel(m_midiOut);
}

MidiPortModel* MidiPlayer::portModel()
{
    std::cout << "portModel called" << std::endl;
    return m_midiPortModel;
}
