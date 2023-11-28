import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.Pickers 1.0
import sailmidi 1.0

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    property string selectedFile

    MidiPlayer {
        id: player
    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

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

            delegate: BackgroundItem {
                Label {
                    x: Theme.horizontalPageMargin
                    text: name
                }
            }
        }


        ValueButton {
              anchors.centerIn: parent
              label: "File"
              value: selectedFile ? selectedFile : "None"
              onClicked: pageStack.push(filePickerPage)
        }

        Component {
              id: filePickerPage
              FilePickerPage {
                  nameFilters: [ '*.mid', '*.MID' ]
                      onSelectedContentPropertiesChanged: {
                      page.selectedFile = selectedContentProperties.filePath
                  }
              }
         }
    }
}
