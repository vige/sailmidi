#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H

#include <QQuickItem>

class MidiPortModel;
class RtMidiOut;

namespace mm {
    class MidiFileReader;
}

class MidiPlayer : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(MidiPortModel * portModel READ portModel)
    Q_PROPERTY(QString midiFile READ midiFile WRITE setMidiFile NOTIFY midiFileChanged)
public:
    MidiPlayer();

    MidiPortModel* portModel();

    QString midiFile() {return m_midiFile;}
    void setMidiFile(const QString& midiFile);

signals:
    void midiFileChanged();
    void midiError(QString errorString);

private:
    void loadMidiFile();

    MidiPortModel* m_midiPortModel;
    RtMidiOut* m_midiOut;
    QString m_midiFile;
    mm::MidiFileReader* m_midiFileReader;
};

#endif // MIDIPLAYER_H
