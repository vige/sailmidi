#ifndef MIDIPORTMODEL_H
#define MIDIPORTMODEL_H

#include <QAbstractListModel>

namespace mm {
    class MidiOutput;
}

class MidiPortModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PortRoles {
        NameRole = Qt::UserRole + 1,
        DeviceRole,
        OpenRole
    };

    explicit MidiPortModel(mm::MidiOutput* midiOut, QObject *parent = 0);

    int rowCount(const QModelIndex&) const override { return m_ports.size(); }
    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void openPort(const int i);

private:
    typedef QPair<QString, QString> PortDef; // name, device
    QVector<PortDef> m_ports;
    mm::MidiOutput *m_midiOut;
};

#endif
