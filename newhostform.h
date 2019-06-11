#ifndef NEWHOSTFORM_H
#define NEWHOSTFORM_H

#include <QDialog>
#include <QDebug>
#include <QList>
#include <QInputDialog>
#include <QLineEdit>
#include <QString>
#include <QMessageBox>
#include "hostgroup.h"

namespace Ui {
class newHostForm;
}

class newHostForm : public QDialog
{
    Q_OBJECT

public:
    explicit newHostForm(QWidget *parent = nullptr, QList<hostGroup>* listOfHostGroup = nullptr);

    QList<hostGroup> *hostsArray;

    void addNewGroup();
    void disableGroup();
    void deleteGroup();

    void addNewHost();
    void deleteHost();

    void setGroupOnUI();
    void setHostOnUI();

    int getIndexForGroup(const QString &value);
    int getIndexForHost(int indexGroup, const QString &value);
    ~newHostForm();

private:
    Ui::newHostForm *ui;
};

#endif // NEWHOSTFORM_H
