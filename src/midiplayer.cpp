#include "midiplayer.h"
#include "RtMidi.h"
#include "midiportmodel.h"
#include "../modern-midi/src/midi_file_reader.h"

MidiPlayer::MidiPlayer()
    : m_midiFile(tr("Select MIDI file")),
      m_midiFileReader(new mm::MidiFileReader)
{
    std::cout << "midiplayer constructor called" << std::endl;
    m_midiOut = std::make_unique<mm::MidiOutput>("SailMidi");
    m_midiPortModel = new MidiPortModel(m_midiOut.get(), this);
}

MidiPortModel* MidiPlayer::portModel()
{
    std::cout << "portModel called" << std::endl;
    return m_midiPortModel;
}

void MidiPlayer::setMidiFile(const QString& midiFile)
{
    if (m_midiFile != midiFile) {
        m_midiFile = midiFile;
        loadMidiFile();
        emit midiFileChanged();
    }
}

void MidiPlayer::loadMidiFile()
{
    try {
        QFile midiFile(m_midiFile);
        if (midiFile.open(QIODevice::ReadOnly)) {
            QByteArray fileContents = midiFile.readAll();
            std::vector<uint8_t> fileContentVector(fileContents.begin(),fileContents.end());
            m_midiFileReader->parse(fileContentVector);
        }
    } catch (const std::runtime_error& e) {
        emit midiError(e.what());
    }
}
