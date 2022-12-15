import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import tictactoe

Item {
    id: root
    required property var model
    property color backgroundColor

    RowLayout {
        anchors.fill: parent

        BusyIndicator {
            running: root.model.gameStatus === GameModel.CpuPlays
        }

        Rectangle {
            Layout.fillWidth: true
            Text {
                anchors.centerIn: parent
                text: "Wins: " + root.model.gameStats.Wins
                fontSizeMode: Text.Fit; font.pixelSize: 30; font.family: "Comic Sans MS"
                color: "white"
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Text {
                anchors.centerIn: parent
                text: "Ties: " + root.model.gameStats.Ties
                fontSizeMode: Text.Fit; font.pixelSize: 30; font.family: "Comic Sans MS"
                color: "white"
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Text {
                anchors.centerIn: parent
                text: "Losses: " + root.model.gameStats.Losses
                fontSizeMode: Text.Fit; font.pixelSize: 30; font.family: "Comic Sans MS"
                color: "white"
            }
        }
        Rectangle{
            Layout.fillWidth: true

            LevelComboBox{
                anchors.centerIn: parent
                font.pixelSize: 30; font.family: "Comic Sans MS"
                currentIndex: 2

                backgroundColor: root.backgroundColor
                textColor: "white"

                model: ListModel {
                    id: difficultyItems
                    ListElement {text: "Easy"; level: GameModel.Easy}
                    ListElement {text: "Medium"; level: GameModel.Medium}
                    ListElement {text: "Impossible"; level: GameModel.Impossible}
                }

                onCurrentIndexChanged: root.model.difficulty = difficultyItems.get(currentIndex).level
            }
        }
    }
}
