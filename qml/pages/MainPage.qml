import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.Pickers 1.0
import sailmidi 1.0

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    MidiPlayer {
        id: player

        onMidiError: {
            errorLabel.text = errorString
        }
    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent
        contentHeight: midiColumn.height

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Show Page 2")
                onClicked: pageStack.animatorPush(Qt.resolvedUrl("SecondPage.qml"))
            }
        }

        SilicaListView {

            anchors.fill: parent

            model: player.portModel

            header: PageHeader {
                id: header
                title: "MIDI ports"
            }

            delegate: ListItem {
                Label {
                    x: Theme.horizontalPageMargin
                    text: name
                    highlighted: open
                }

                menu: ContextMenu {
                    MenuItem {
                        text: qsTr("Open")
                        onClicked: player.portModel.openPort(index)
                    }
                }
            }
        }


        ValueButton {
              anchors.centerIn: parent
              label: "File"
              value: player.midiFile;
              onClicked: {
                  pageStack.push(filePickerPage)
              }
        }

        Component {
              id: filePickerPage
              FilePickerPage {
                  nameFilters: [ '*.mid', '*.MID' ]
                      onSelectedContentPropertiesChanged: {
                      player.midiFile = selectedContentProperties.filePath
                  }
              }
         }

        IconButton {
            anchors.bottom: parent.bottom
            id: playButton
            icon.source: "image://theme/icon-l-play"
            visible: !player.playing
            onClicked: player.play()
        }

        IconButton {
            anchors.bottom: parent.bottom
            id: stopButton
            icon.source: "image://theme/icon-m-stop"
            visible: player.playing
            onClicked: player.stop()
        }


        Label {
            id: errorLabel
        }
    }
}
