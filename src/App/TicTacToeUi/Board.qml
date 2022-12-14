import QtQml
import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import tictactoe

TableView {
    id: board

    property color textColor
    property color backgroundColor

    rowSpacing: 10
    columnSpacing: 10

    columnWidthProvider: function (column) { return width / model.columnCount() }
    onWidthChanged: board.forceLayout()

    rowHeightProvider: function (row) { return height / model.rowCount() }
    onHeightChanged: board.forceLayout()

    clip: true

    delegate: Rectangle {
        id: cell
        implicitWidth: board.columnWidthProvider(column)
        implicitHeight: board.rowHeightProvider(column)

        required property var model

        color: backgroundColor

        Text {
            anchors.fill: parent
            text: model.value
            font.family: "Comic Sans MS"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 240
            minimumPointSize: 2
            fontSizeMode: Text.Fit
            color: textColor
        }

        MouseArea {
            anchors.fill: parent
            onClicked: parent.model.value = 0 // Note that model does not care about value
        }
    }

    model: GameModel {}
}
