#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QJsonObject>
#include <QComboBox>
#include <QRadioButton>
#include <QCheckBox>

class JsonManager
{
public:
    static bool fileExist(const QString&);
    static QJsonObject createJsonFromWidgets(const QVector<QComboBox *> &, const QVector<QRadioButton*> &
                                      ,const QVector<QCheckBox*>&, const QVector<QCheckBox*>& );
    static void saveJsonToFile(const QJsonObject&, const QString&);
};

#endif // JSONMANAGER_H
