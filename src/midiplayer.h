#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H

#include <QQuickItem>

class MidiPortModel;
class RtMidiOut;

class MidiPlayer : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(MidiPortModel * portModel READ portModel)
public:
    MidiPlayer();

    MidiPortModel* portModel();

signals:

private:
    MidiPortModel* m_midiPortModel;
    RtMidiOut* m_midiOut;

};

#endif // MIDIPLAYER_H
