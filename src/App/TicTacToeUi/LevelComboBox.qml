import QtQuick
import QtQuick.Controls

ComboBox {
    property color textColor
    property color backgroundColor

    id: control

    textRole: "text"
    valueRole: "level"

    background: Rectangle {
        color: backgroundColor
    }

    delegate: ItemDelegate {
        width: control.width
        contentItem: Text {
            text: model[control.textRole]
            color: backgroundColor
            font: control.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
        highlighted: control.highlightedIndex === index
    }

    contentItem: Text {
        text: parent.displayText
        font: parent.font
        color: textColor
        elide: Text.ElideRight
    }
}
