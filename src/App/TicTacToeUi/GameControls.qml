import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import tictactoe

Item {
    id: root
    required property var model
    property color textColor
    property color backgroundColor
    property font font

    component GameText : Text {
        font: root.font
        color: root.textColor
    }

    RowLayout {
        anchors.fill: parent

        BusyIndicator {
            running: root.model.gameStatus === GameModel.CpuPlays
        }

        Rectangle {
            Layout.fillWidth: true
            GameText {
                anchors.centerIn: parent
                text: "Wins: " + root.model.gameStats.Wins
            }
        }
        Rectangle {
            Layout.fillWidth: true
            GameText {
                anchors.centerIn: parent
                text: "Ties: " + root.model.gameStats.Ties
            }
        }
        Rectangle {
            Layout.fillWidth: true
            GameText {
                anchors.centerIn: parent
                text: "Losses: " + root.model.gameStats.Losses
            }
        }
        Rectangle{
            Layout.fillWidth: true

            LevelComboBox{
                anchors.centerIn: parent
                font: root.font
                currentIndex: 2

                backgroundColor: root.backgroundColor
                textColor: root.textColor

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
