#include "mystylesheet.h"

QString myStyleSheet::buttonStyle(QString background_color)
{
    QString buttonStyle = "QToolButton {"
                          "border: 1px solid " + background_color + ";"
                          "border-radius: 5px;"
                          "padding: 5px;"
                          "background-color: " + background_color + ";"
                          "font-weight: bold;"
                          "}"
                          "QToolButton:pressed {"
                          "background-color: #d0d0d0;"
                          "}";
    return buttonStyle;
}

QString myStyleSheet::comboBoxStyle()
{
    QString comboBoxStyleSheet = "QComboBox {"
                    "   border: 1px solid lightgray;"
                    "   border-radius: 3px;"
                    "   padding: 1px 18px 1px 3px;"
                    "   min-width: 6em;"
                    "}"
                    "QComboBox:editable {"
                    "   background: white;"
                    "}"
                    "QComboBox:!editable, QComboBox::drop-down:editable {"
                    "   background: white;"
                    "}"
                    "QComboBox:!editable:on, QComboBox::drop-down:editable:on {"
                    "   background: white;"
                    "}"
                    "QComboBox::drop-down {"
                    "   subcontrol-origin: padding;"
                    "   subcontrol-position: top right;"
                    "   width: 15px;"
                    "   border-left-width: 1px;"
                    "   border-left-color: darkgray;"
                    "   border-left-style: solid;"
                    "   border-top-right-radius: 3px;"
                    "   border-bottom-right-radius: 3px;"
                    "}"
                    "QComboBox::down-arrow {"
                    "   image: url(../Microchip/image/down-arrow.png);"
                    "}"
                    "QComboBox QAbstractItemView {"
                    "   border: 1px solid lightgrey;"
                    "   selection-background-color: lightgrey;"
                    "}";
    return comboBoxStyleSheet;
}

QString myStyleSheet::radioButtonStyle()
{
    QString radioButtonStyleSheet = "QRadioButton::indicator { width: 7px; height: 7px; border-radius: 3.5px; }"
                                    "QRadioButton::indicator:unchecked { background-color: white; border: 4px solid lightgray; }"
                                    "QRadioButton::indicator:checked { background-color: blue; border: 4px solid blue; }"
                                    "QRadioButton::indicator:checked::inside { background-color: white; border-radius: 6.5px; }";
    return radioButtonStyleSheet;
}

QString myStyleSheet::checkBoxStyle()
{
    QString checkBoxStyleSheet = "QCheckBox::indicator:checked {"
                                "    border: 1px solid blue;"
                                "    background: blue;"
                                "    image: url(../Microchip/image/check_mark.png);"
                                "}"
                                "QCheckBox::indicator:unchecked {"
                                "    border: 1px solid lightgray;"
                                "    background: white;"
                                "}"
                                "QCheckBox:disabled {"
                                "    background: white;"
                                "}"
                                "QCheckBox::indicator:disabled {"
                                "    background: #87CEFA;"
                                "    border: 1px #87CEFA;"
                                "}";
    return checkBoxStyleSheet;
}
