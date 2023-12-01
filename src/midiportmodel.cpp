#include "midiportmodel.h"
#include <filesystem>

#include "../modern-midi/src/midi_output.h"
#include "../tinymidi/include/rawmidi.h"

MidiPortModel::MidiPortModel(mm::MidiOutput* midiOut, QObject* parent)
    : m_midiOut(midiOut)
{
    for (const auto& entry : std::filesystem::directory_iterator("/dev/snd")) {
        if(entry.path().filename().string().rfind("midi", 0) == 0) {
            std::cout << "found midi device: " << entry.path().filename().string() << std::endl;
            snd_rawmidi_info_t info;
            int fd, fmode; 

            fmode = O_RDWR;
            fd = rawmidi_open_device(entry.path().c_str(), fmode);
            if (fd < 0) {
                continue;
            }

            memset(&info, 0, sizeof(info));
            ioctl(fd, SNDRV_RAWMIDI_IOCTL_INFO, &info);
            std::cout << "device name: " << info.name << std::endl;
        }
    }
    
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
    if (role == OpenRole) {
        return QVariant(QString::fromStdString(m_midiOut->info.name) == m_ports[index.row()]);
    }
    return QVariant();
}

QHash<int, QByteArray> MidiPortModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[DeviceRole] = "device";
    roles[OpenRole] = "open";
    return roles;
}

void MidiPortModel::openPort(const int i)
{
    m_midiOut->closePort();
    m_midiOut->openPort(m_ports[i].toStdString());
    emit dataChanged(createIndex(0, 0), createIndex(m_ports.size(), 0));
}
