#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mystylesheet.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QSpacerItem>

#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QTextStream>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set the size of the main window
    this->resize(700, 600);
    this->setStyleSheet("background-color: white;");

    QToolButton *print_button = new QToolButton(this);
    QToolButton *quit_button = new QToolButton(this);
    print_button->setIcon(QIcon("../Microchip/image/printer"));
    quit_button->setIcon(QIcon("../Microchip/image/size"));

    QHBoxLayout *save_layout = new QHBoxLayout();
    save_layout->addWidget(print_button);
    save_layout->addWidget(quit_button);
    save_layout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QToolButton *toolbutton1 = new QToolButton(this);
    QToolButton *toolbutton2 = new QToolButton(this);
    QToolButton *toolbutton3 = new QToolButton(this);
    QToolButton *toolbutton4 = new QToolButton(this);
    toolbutton1->setIcon(QIcon("../Microchip/image/database"));
    toolbutton2->setIcon(QIcon("../Microchip/image/checkmark"));
    toolbutton3->setIcon(QIcon("../Microchip/image/new-tab"));
    toolbutton4->setIcon(QIcon("../Microchip/image/question"));

    QString saveButtonStyle = myStyleSheet::buttonStyle("rgb(0,5,138)");
    QString buttonStyle = myStyleSheet::buttonStyle("white");

    toolbutton1->setStyleSheet(buttonStyle);
    toolbutton2->setStyleSheet(buttonStyle);
    toolbutton3->setStyleSheet(buttonStyle);
    toolbutton4->setStyleSheet(buttonStyle);
    print_button->setStyleSheet(saveButtonStyle);
    quit_button->setStyleSheet(saveButtonStyle);

    QHBoxLayout *button_Layout = new QHBoxLayout();
    button_Layout->addWidget(toolbutton1);
    button_Layout->addWidget(toolbutton2);
    button_Layout->addWidget(toolbutton3);
    button_Layout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    button_Layout->addWidget(toolbutton4);

    QWidget *buttonContainer = new QWidget(this);
    buttonContainer->setLayout(button_Layout);

    QWidget *save_buttonContainer = new QWidget(this);
    save_buttonContainer->setLayout(save_layout);

    save_buttonContainer->setFixedHeight(40);
    save_buttonContainer->setStyleSheet("QWidget {"
                                        "border: 1px solid #cccccc;"
                                        "border-radius: 2px;"
                                        "padding: 5px;"
                                        "background-color: rgb(0,5,138);"
                                        "}");

    buttonContainer->setFixedHeight(40);
    buttonContainer->setStyleSheet("QWidget {"
                                   "border: 1px solid #cccccc;"
                                   "border-radius: 8px;"
                                   "padding: 5px;"
                                   "}");

    QWidget *tab1_widget = new QWidget(this);
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QTabWidget *tab = new QTabWidget(this);
    tab->setGeometry(10, 70, 500, 500);
    tab->addTab(tab1_widget, "Configuration");
    tab->setStyleSheet(
        "QTabWidget::pane {"
        "    border: 1px solid lightgray;"
        "}"
        "QTabBar::tab {"
        "    background: lightgray;"
        "    color: black;"
        "    padding: 10px;"
        "}"
        "QTabBar::tab:selected {"
        "    background: white;"
        "    color: blue;"
        "    border-bottom: 2px solid blue;"
        "}"
        "QWidget {"
        "    background-color: white;"
        "}"
        );

    QLabel *name_label = new QLabel("COREAPB3:5.0.104", this);
    name_label->setStyleSheet("QLabel { font-weight: bold; }");

    mainLayout->addWidget(save_buttonContainer);
    mainLayout->addWidget(name_label);
    mainLayout->addWidget(buttonContainer);
    mainLayout->addWidget(tab);

    setCentralWidget(centralWidget);

    // main layout for tab 1
    QVBoxLayout *tab1_layout = new QVBoxLayout(tab1_widget);

    // ----------------------------------- 1 -----------------------------------
    QLabel *label_global_config = new QLabel("GLOBAL CONFIGURATION:", tab1_widget);
    label_global_config->setStyleSheet("QLabel { font-weight: bold; background-color: rgb(238, 238, 238); }");
    label_global_config->setFixedHeight(30);

    comboBox_global_config = new QComboBox(tab1_widget);
    comboBox_global_config->addItem("Asynchronous");
    comboBox_global_config->addItem("Asynchronous_2");
    comboBox_global_config->addItem("Asynchronous_3");
    comboBox_global_config->setStyleSheet(myStyleSheet::comboBoxStyle());

    QHBoxLayout *layout_gc = new QHBoxLayout();
    layout_gc->addWidget(new QLabel("Reset Type: ", tab1_widget));
    layout_gc->addWidget(comboBox_global_config);
    layout_gc->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QVBoxLayout *layout_global_config = new QVBoxLayout();
    layout_global_config->addWidget(label_global_config);
    layout_global_config->addLayout(layout_gc);

    // ----------------------------------- 2 -----------------------------------
    QLabel *label_data_config = new QLabel("DATA WIDTH CONFIGURATION:", tab1_widget);
    label_data_config->setStyleSheet("QLabel { font-weight: bold; background-color: rgb(238, 238, 238); }");
    label_data_config->setFixedHeight(30);

    radioButton1 = new QRadioButton("8-bit", tab1_widget);
    radioButton2 = new QRadioButton("16-bit", tab1_widget);
    radioButton3 = new QRadioButton("32-bit", tab1_widget);

    QString radioButtonStyleSheet = myStyleSheet::radioButtonStyle();
    radioButton1->setStyleSheet(radioButtonStyleSheet);
    radioButton2->setStyleSheet(radioButtonStyleSheet);
    radioButton3->setStyleSheet(radioButtonStyleSheet);

    QHBoxLayout *layout_dc = new QHBoxLayout();
    layout_dc->addWidget(new QLabel("APB Initiator Data Bus Width: ", tab1_widget));
    layout_dc->addWidget(radioButton1);
    layout_dc->addWidget(radioButton2);
    layout_dc->addWidget(radioButton3);
    layout_dc->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QVBoxLayout *layout_data_config = new QVBoxLayout();
    layout_data_config->addWidget(label_data_config);
    layout_data_config->addLayout(layout_dc);

    // ----------------------------------- 3 -----------------------------------
    QLabel *label_address_config = new QLabel("ADDRESS CONFIGURATION:", tab1_widget);
    label_address_config->setStyleSheet("QLabel { font-weight: bold; background-color: rgb(238, 238, 238); }");
    label_address_config->setFixedHeight(30);

    comboBox_1 = new QComboBox(tab1_widget);
    comboBox_1->setStyleSheet(myStyleSheet::comboBoxStyle());
    comboBox_1->addItem("16");
    comboBox_1->addItem("32");
    comboBox_1->addItem("64");
    comboBox_1->addItem("128");
    comboBox_2 = new QComboBox(tab1_widget);
    comboBox_2->setStyleSheet(myStyleSheet::comboBoxStyle());
    comboBox_2->addItem("[27:24](Ignored if initiator address width >= 32 bits)");
    comboBox_2->addItem("[34:31](Ignored if initiator address width >= 64 bits)");
    comboBox_2->addItem("[45:41](Ignored if initiator address width >= 128 bits)");
    comboBox_3 = new QComboBox(tab1_widget);
    comboBox_3->setStyleSheet(myStyleSheet::comboBoxStyle());
    comboBox_3->addItem("Not in use");
    comboBox_3->addItem("Use");

    QHBoxLayout *layout_1 = new QHBoxLayout();
    QHBoxLayout *layout_2 = new QHBoxLayout();
    QHBoxLayout *layout_3 = new QHBoxLayout();
    layout_1->addWidget(new QLabel("Number of address bits driven by initiatior: ", tab1_widget));
    layout_1->addWidget(comboBox_1);
    layout_2->addWidget(new QLabel("Position in Target address of upper 4 bits of initiator address: ", tab1_widget));
    layout_2->addWidget(comboBox_2);
    layout_3->addWidget(new QLabel("Indirect Addressing: ", tab1_widget));
    layout_3->addWidget(comboBox_3);

    QVBoxLayout *layout_address_config = new QVBoxLayout();
    layout_address_config->addWidget(label_address_config);
    layout_address_config->addLayout(layout_1);
    layout_address_config->addLayout(layout_2);
    layout_address_config->addLayout(layout_3);

    // ----------------------------------- 4, 5 -----------------------------------
    QLabel *label_allocate = new QLabel("ALLOCATE MEMORY:", tab1_widget);
    label_allocate->setStyleSheet("QLabel { font-weight: bold; background-color: rgb(238, 238, 238); }");
    label_allocate->setFixedHeight(30);

    QGridLayout *grid1 = new QGridLayout();
    QGridLayout *grid2 = new QGridLayout();

    QString checkBoxStyleSheet = myStyleSheet::checkBoxStyle();

    checkBoxGroup1.resize(16);
    checkBoxGroup2.resize(16);

    // loop for creating second group checkboxes
    int k = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            checkBoxGroup2[k] = new QCheckBox("Slot " + QString::number(k) + ":", this);
            checkBoxGroup2[k]->setStyleSheet(checkBoxStyleSheet);
            checkBoxGroup2[k]->setChecked(true);
            grid2->addWidget(checkBoxGroup2[k], i, j);
            ++k;
        }
    }

    // loop for creating second group checkboxes and connect
    k = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            checkBoxGroup1[k] = new QCheckBox("Slot " + QString::number(k) + ":", this);
            checkBoxGroup1[k]->setStyleSheet(checkBoxStyleSheet);
            grid1->addWidget(checkBoxGroup1[k], i, j);

            connect(checkBoxGroup1[k], &QCheckBox::toggled, this, [=](bool checked) {
                onCheckBoxToggled(k, checked);
            });
            ++k;
        }
    }
    QVBoxLayout *allocate_slots_layout = new QVBoxLayout();
    allocate_slots_layout->addWidget(label_allocate);
    allocate_slots_layout->addLayout(grid1);

    QLabel *label_enabled = new QLabel("ENABLED APB:", tab1_widget);
    label_enabled->setStyleSheet("QLabel { font-weight: bold; background-color: rgb(238, 238, 238); }");
    label_enabled->setFixedHeight(30);

    QVBoxLayout *enabled_layout = new QVBoxLayout();
    enabled_layout->addWidget(label_enabled);
    enabled_layout->addLayout(grid2);

    // ----------------------------------- 6 -----------------------------------
    comboBox_testbench = new QComboBox(tab1_widget);
    comboBox_testbench->setStyleSheet(myStyleSheet::comboBoxStyle());
    comboBox_testbench->addItem("User");
    comboBox_testbench->addItem("Option 2");
    comboBox_testbench->addItem("Option 3");

    QHBoxLayout *layout_testbanch = new QHBoxLayout();
    layout_testbanch->addWidget(new QLabel("Testbench: ", tab1_widget));
    layout_testbanch->addWidget(comboBox_testbench);
    layout_testbanch->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    tab1_layout->addLayout(layout_global_config);
    tab1_layout->addLayout(layout_data_config);
    tab1_layout->addLayout(layout_address_config);
    tab1_layout->addLayout(allocate_slots_layout);
    tab1_layout->addLayout(enabled_layout);
    tab1_layout->addLayout(layout_testbanch);

    if (JsonManager::fileExist("data.json")) {
        loadDataFromFile("data.json");
    } else {
        qDebug() << "file doesn't exist (default values)";
    }

    connect(toolbutton1, &QToolButton::clicked, this, &MainWindow::on_saveButton_clicked);
}

void MainWindow::loadDataFromFile(const QString& fileName)
{
    qDebug() << "Reading JSON from file:" << fileName;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open load file.");
        return;
    }

    QByteArray data = file.readAll();
    QJsonParseError jsonError;
    QJsonDocument loadDoc(QJsonDocument::fromJson(data, &jsonError));
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "Some Error in Json Data: " << jsonError.errorString();
        return;
    } else {
        qDebug() << "NO Error in file\n";
    }
    QJsonObject jsonObject = loadDoc.object();

    // Set QComboBox value
    QString reset_type = jsonObject["Reset Type"].toString();
    int comboBoxIndex = comboBox_global_config->findText(reset_type);
    if (comboBoxIndex != -1) {
        comboBox_global_config->setCurrentIndex(comboBoxIndex);
    } else {
        qDebug() << "Wrong value for \"Reset Type\" -> " << reset_type;
    }
    QString Number = jsonObject["Number"].toString();
    comboBoxIndex = comboBox_1->findText(Number);
    if (comboBoxIndex != -1) {
        comboBox_1->setCurrentIndex(comboBoxIndex);
    } else {
        qDebug() << "Wrong value for \"Number\"\n";
    }
    QString Position = jsonObject["Position"].toString();
    comboBoxIndex = comboBox_2->findText(Position);
    if (comboBoxIndex != -1) {
        comboBox_2->setCurrentIndex(comboBoxIndex);
    } else {
        qDebug() << "Wrong value for \"Position\"\n";
    }
    QString IndirectAddressing = jsonObject["Indirect Addressing"].toString();
    comboBoxIndex = comboBox_3->findText(IndirectAddressing);
    if (comboBoxIndex != -1) {
        comboBox_3->setCurrentIndex(comboBoxIndex);
    } else {
        qDebug() << "Wrong value for \"Indirect Addressing\"\n";
    }
    QString Testbench = jsonObject["Testbench"].toString();
    comboBoxIndex = comboBox_testbench->findText(Testbench);
    if (comboBoxIndex != -1) {
        comboBox_testbench->setCurrentIndex(comboBoxIndex);
    } else {
        qDebug() << "Wrong value for \"Testbench\"\n";
    }

    // Set QRadioButtons values
    QJsonObject radioButtonsObject = jsonObject["APB"].toObject();
    radioButton1->setChecked(radioButtonsObject["radioButton1"].toBool());
    radioButton2->setChecked(radioButtonsObject["radioButton2"].toBool());
    radioButton3->setChecked(radioButtonsObject["radioButton3"].toBool());

    // Set QCheckBoxes values
    QJsonArray checkBoxesArray1 = jsonObject["CheckBoxes1"].toArray();
    QJsonArray checkBoxesArray2 = jsonObject["CheckBoxes2"].toArray();
    for (int i = 0; i < 16; ++i) {
        checkBoxGroup1[i]->setChecked(checkBoxesArray1[i].toBool());
        checkBoxGroup2[i]->setChecked(checkBoxesArray2[i].toBool());
    }

    qDebug() << "JSON loaded successfully";
    file.close();
}

void MainWindow::on_saveButton_clicked()
{
    QVector<QComboBox*> comboBoxArray;
    comboBoxArray.append(comboBox_global_config);
    comboBoxArray.append(comboBox_1);
    comboBoxArray.append(comboBox_2);
    comboBoxArray.append(comboBox_3);
    comboBoxArray.append(comboBox_testbench);

    QVector<QRadioButton*> radioButtonArray;
    radioButtonArray.append(radioButton1);
    radioButtonArray.append(radioButton2);
    radioButtonArray.append(radioButton3);

    QJsonObject jsonObject = JsonManager::createJsonFromWidgets(comboBoxArray, radioButtonArray, checkBoxGroup1, checkBoxGroup2);
    JsonManager::saveJsonToFile(jsonObject, "data.json");
    qDebug() << "Save operation completed";
}

void MainWindow::onCheckBoxToggled(int index, bool checked)
{
    checkBoxGroup2[index]->setEnabled(!checked);
}

MainWindow::~MainWindow()
{
}
