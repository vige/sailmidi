#include <sailfishapp.h>
#include <memory>
#include <QtQuick>
#include <QScopedPointer>
#include "midiportmodel.h"
#include "midiplayer.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> v(SailfishApp::createView());
    
    qmlRegisterUncreatableType<MidiPortModel>("sailmidi", 1, 0, "MidiPortModel", QStringLiteral("Use MidiPlayer.portModel"));
    qmlRegisterType<MidiPlayer>("sailmidi", 1, 0, "MidiPlayer");

    v->setSource(SailfishApp::pathTo("qml/sailmidi.qml"));
    v->show();
    return app->exec();
}
