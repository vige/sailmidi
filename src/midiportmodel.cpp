#include "midiportmodel.h"
#include "RtMidi.h"
#include "../modern-midi/src/midi_output.h"

MidiPortModel::MidiPortModel(mm::MidiOutput* midiOut, QObject* parent)
    : m_midiOut(midiOut)
{
    if (midiOut) {
        RtMidiOut* pOutputDevice = midiOut->getOutputDevice();
        for (unsigned int i=0; i < pOutputDevice->getPortCount(); i++)
            m_ports.append(QString::fromStdString(pOutputDevice->getPortName(i)));
    }
}

QVariant MidiPortModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    if (role == NameRole) {
        return QVariant(m_ports[index.row()]);
    }
    return QVariant();
}

QHash<int, QByteArray> MidiPortModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}
