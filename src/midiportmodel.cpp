#include "midiportmodel.h"
#include <filesystem>

#include "../modern-midi/src/midi_output.h"
extern "C" {
#include "../tinymidi/include/rawmidi.h"
}
    
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
            close(fd);
            std::cout << "device name: " << info.name << ":" << info.subname << std::endl;
            QString deviceName((const char*)(info.name));
            deviceName+=":";
            deviceName+=QString((const char*)(info.subname));
            PortDef device = qMakePair(deviceName, QString::fromStdString(entry.path().string()));
            m_ports.append(device);
        }
    }
    
    // if (midiOut) {
    //     RtMidiOut* pOutputDevice = midiOut->getOutputDevice();
    //     for (unsigned int i=0; i < pOutputDevice->getPortCount(); i++)
    //         m_ports.append(QString::fromStdString(pOutputDevice->getPortName(i)));
    // }
}

QVariant MidiPortModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    if (role == NameRole) {
        return QVariant(m_ports[index.row()].first);
    }
    if (role == DeviceRole) {
        return QVariant(m_ports[index.row()].second);
    }
    if (role == OpenRole) {
        return QVariant(QString::fromStdString(m_midiOut->info.device) == m_ports[index.row()].second);
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
    m_midiOut->openDevicePort(m_ports[i].second.toStdString());
    emit dataChanged(createIndex(0, 0), createIndex(m_ports.size(), 0));
}
