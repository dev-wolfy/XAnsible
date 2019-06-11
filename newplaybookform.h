#ifndef NEWPLAYBOOKFORM_H
#define NEWPLAYBOOKFORM_H

#include <QDialog>
#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include <QList>
#include <QVariant>
#include <QComboBox>

#include "hostgroup.h"
#include "playbook.h"

namespace Ui {
class newPlaybookForm;
}

class newPlaybookForm : public QDialog
{
    Q_OBJECT

public:
    explicit newPlaybookForm(QWidget *parent = nullptr, playbook *Playbook = nullptr);

    playbook *getPlaybook() const;
    void setPlaybook(playbook *value);
    void getHostsGroups(const QList<hostGroup> &value);

    ~newPlaybookForm();

private slots:
    void selectPath();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::newPlaybookForm *ui;
    QList<hostGroup> hostsGroups;
    playbook *Playbook;
};

#endif // NEWPLAYBOOKFORM_H
