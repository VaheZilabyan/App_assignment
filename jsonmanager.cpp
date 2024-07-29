#include "jsonmanager.h"

#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

bool JsonManager::fileExist(const QString &filename)
{
    QFile file(filename);
    return file.exists();
}

QJsonObject JsonManager::createJsonFromWidgets(const QVector<QComboBox*> &comboBoxArray, const QVector<QRadioButton*> &radioButtonArray,
                                        const QVector<QCheckBox*>& checkBoxGroup1, const QVector<QCheckBox*>& checkBoxGroup2)
{
    /*for (const auto& el : comboBoxArray) {
        qDebug() << el->currentText() << " ";
    }
    for (const auto& el : radioButtonArray) {
        qDebug() << el->isChecked() << " ";
    }
    for (const auto& el : checkBoxGroup1) {
        qDebug() << el->isChecked() << " ";
    }*/

    QJsonObject jsonObject;

    jsonObject["Reset Type"] = comboBoxArray[0]->currentText();
    jsonObject["Number"] = comboBoxArray[1]->currentText();
    jsonObject["Position"] = comboBoxArray[2]->currentText();
    jsonObject["Indirect Addressing"] = comboBoxArray[3]->currentText();
    jsonObject["Testbench"] = comboBoxArray[4]->currentText();

    // Add QRadioButtons values
    QJsonObject radioButtonsObject;
    radioButtonsObject["radioButton1"] = radioButtonArray[0]->isChecked();
    radioButtonsObject["radioButton2"] = radioButtonArray[1]->isChecked();
    radioButtonsObject["radioButton3"] = radioButtonArray[2]->isChecked();
    jsonObject["APB"] = radioButtonsObject;

    // Add QCheckBoxes values
    QJsonArray checkBoxesArray1;
    QJsonArray checkBoxesArray2;
    for (int i = 0; i < 16; ++i) {
        checkBoxesArray1.append(checkBoxGroup1[i]->isChecked());
        checkBoxesArray2.append(checkBoxGroup2[i]->isChecked());
    }
    jsonObject["CheckBoxes1"] = checkBoxesArray1;
    jsonObject["CheckBoxes2"] = checkBoxesArray2;

    return jsonObject;
}

void JsonManager::saveJsonToFile(const QJsonObject &jsonObject, const QString &fileName)
{
    qDebug() << "Saving JSON to file:" << fileName;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonDocument saveDoc(jsonObject);
    //saveDoc.setObject(jsonObject);
    file.write(saveDoc.toJson(QJsonDocument::JsonFormat::Indented));
    file.close();
    qDebug() << "JSON saved successfully";
}
