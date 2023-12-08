import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0
import "pages"
import sailmidi 1.0

ApplicationWindow {
    id: application
    initialPage: Component { MainPage { } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations

    property string errorString: ""

    ConfigurationValue {
        id: selectedMidiFile
        key: "/apps/harbour-sailmidi/selectedMidiFile"
    }

    MidiPlayer {
        id: player

        midiFile: selectedMidiFile.value

        onMidiError: application.errorString = errorString

        onMidiFileLoaded: errorString = ""
    }

}
