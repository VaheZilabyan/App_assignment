#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "jsonmanager.h"

#include <QMainWindow>
#include <QCheckBox>
#include <QComboBox>
#include <QRadioButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onCheckBoxToggled(int index, bool checked);
    void on_saveButton_clicked();

private:
    void loadDataFromFile(const QString&);

private:
    QVector<QCheckBox*> checkBoxGroup1;
    QVector<QCheckBox*> checkBoxGroup2;
    QComboBox *comboBox_global_config;
    QComboBox *comboBox_1;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QComboBox *comboBox_testbench;
    QRadioButton *radioButton1;
    QRadioButton *radioButton2;
    QRadioButton *radioButton3;
};
#endif // MAINWINDOW_H
