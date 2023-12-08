#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H

#include <QQuickItem>
#include <memory>
#include "../modern-midi/src/midi_output.h"
#include "../modern-midi/src/sequence_player.h"

class MidiPortModel;

namespace mm {
    class MidiFileReader;
}

class MidiPlayer : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(MidiPortModel * portModel READ portModel CONSTANT)
    Q_PROPERTY(QString midiFile READ midiFile WRITE setMidiFile NOTIFY midiFileChanged)
    Q_PROPERTY(bool playing READ playing NOTIFY playingChanged);
    Q_PROPERTY(QString sailmidiVersion READ sailmidiVersion CONSTANT)
public:
    MidiPlayer();

    MidiPortModel* portModel();

    QString midiFile() {return m_midiFile;}
    void setMidiFile(const QString& midiFile);

    Q_INVOKABLE void play();
    Q_INVOKABLE void stop();

    bool playing() {return m_playing;}
    QString sailmidiVersion() {return m_sailmidiVersion;}
    
signals:
    void midiFileChanged();
    void midiFileLoaded();
    void midiError(QString errorString);
    void playingChanged();

private:
    void loadMidiFile();

    MidiPortModel* m_midiPortModel;
    std::unique_ptr<mm::MidiOutput> m_midiOut;
    std::unique_ptr<mm::MidiSequencePlayer> m_sequencePlayer;
    QString m_midiFile;
    mm::MidiFileReader* m_midiFileReader;
    bool m_playing;
    QString m_sailmidiVersion;
};

#endif // MIDIPLAYER_H
