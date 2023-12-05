import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    SilicaFlickable {
        contentHeight: column.height
        anchors.fill: parent

        Column {
            id: column
            anchors.fill: parent

            PageHeader {
                title: "About"
            }

            Item {
                width: parent.width
                height: Theme.paddingLarge
            }

            Image {
                source: "harbour-sailmidi.png"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Label {
                text: "Sailmidi v" + player.sailmidiVersion
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize:    Theme.fontSizeLarge
            }

            Item {
                width: parent.width
                height: Theme.paddingLarge
            }

            Label {
                text: "Copyright (c) 2023, Ville Nummela"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Label {
                text: "Sources available at:"
                anchors.horizontalCenter: parent.horizontalCenter

            }

            LinkedLabel {
                anchors.horizontalCenter: parent.horizontalCenter
                plainText: "https://github.com/vige/sailmidi"
            }

            Item {
                width: parent.width
                height: Theme.paddingLarge
            }

            Label {
                text: "Licensed under GPLv3"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Item {
                width: parent.width
                height: Theme.paddingLarge
            }

            Label {
                text: "ModernMIDI Copyright (c) 2015\nDimitri Diakopoulos"
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
