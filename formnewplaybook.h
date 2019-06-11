#ifndef FORMNEWPLAYBOOK_H
#define FORMNEWPLAYBOOK_H

#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include <QList>
#include <QVariant>
#include <QComboBox>

#include "hostgroup.h"
#include "playbook.h"

namespace Ui {
class FormNewPlaybook;
}

class FormNewPlaybook : public QWidget
{
    Q_OBJECT

public:
    explicit FormNewPlaybook(QWidget *parent = nullptr, playbook *Playbook = nullptr);
    void getHostGroup(const QList<hostGroup> &value);
    ~FormNewPlaybook();

private slots:
    void selectPath();

    void on_user_name_field_textEdited(const QString &arg1);

    void on_pathField_textChanged(const QString &arg1);

    void on_playbook_name_field_textChanged(const QString &arg1);

    void on_comboBox_activated(int index);

    void on_dialog_button_box_accepted();

    void on_dialog_button_box_rejected();

private:
    Ui::FormNewPlaybook *ui;
    QList<hostGroup> hostsGroups;
    playbook *Playbook;
};

#endif // FORMNEWPLAYBOOK_H
