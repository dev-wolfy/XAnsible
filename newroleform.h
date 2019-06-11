#ifndef NEWROLEFORM_H
#define NEWROLEFORM_H

#include <QDialog>
#include <QString>
#include "p_role.h"

namespace Ui {
class newRoleForm;
}

class newRoleForm : public QDialog
{
    Q_OBJECT

public:
    explicit newRoleForm(QWidget *parent = nullptr, p_role *Role = nullptr);

    p_role tempRole;
    p_role *ptrRole;

    ~newRoleForm();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::newRoleForm *ui;
};

#endif // NEWROLEFORM_H
