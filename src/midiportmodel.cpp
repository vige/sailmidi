#include "midiportmodel.h"
#include "RtMidi.h"

MidiPortModel::MidiPortModel(RtMidiOut* midiOut, QObject* parent)
{
    std::cout << "MidiPortModel constructor called" << std::endl;
    if (midiOut) {
        std::cout << "midiOut defined" << std::endl;
        for (unsigned int i=0; i < midiOut->getPortCount(); i++)
            m_ports.append(QString::fromStdString(midiOut->getPortName(i)));
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
