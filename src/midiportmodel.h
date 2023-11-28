#ifndef MIDIPORTMODEL_H
#define MIDIPORTMODEL_H

#include <QAbstractListModel>

class RtMidiOut;

class MidiPortModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PortRoles {
        NameRole = Qt::UserRole + 1,
    };

    explicit MidiPortModel(RtMidiOut* midiOut, QObject *parent = 0);

    int rowCount(const QModelIndex&) const override { return m_ports.size(); }
    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<QString> m_ports;
};

#endif
