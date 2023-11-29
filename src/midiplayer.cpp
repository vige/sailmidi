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
    m_sequencePlayer = std::make_unique<mm::MidiSequencePlayer>(*m_midiOut.get());
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

void MidiPlayer::play()
{
    m_sequencePlayer->loadSingleTrack(m_midiFileReader->tracks[0]);
            // Started Event
    m_sequencePlayer->startedEvent = [&]()
    {
        std::cout << "Notification that the MidiSequencePlayer has started…" << std::endl;
    };
        
    // Stopped Event Callback
    m_sequencePlayer->stoppedEvent = [&]()
        {
            std::cout << "Notification that the MidiSequencePlayer has stopped…" << std::endl;
        };
        
    m_sequencePlayer->start();
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
