import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"
import sailmidi 1.0

ApplicationWindow {
    id: application
    initialPage: Component { MainPage { } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations

    property string errorString: ""

    MidiPlayer {
        id: player

        onMidiError: {
            application.errorString = errorString
        }
    }

}
