#include "newroleform.h"
#include "ui_newroleform.h"

newRoleForm::newRoleForm(QWidget *parent, p_role *Role) :
    QDialog(parent),
    ui(new Ui::newRoleForm)
{
    ui->setupUi(this);

    this->ptrRole = Role;

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &newRoleForm::on_buttonBox_accepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &newRoleForm::on_buttonBox_rejected);
}

void newRoleForm::on_buttonBox_accepted()
{
    bool fill = false;

    if (!this->ui->roleNameField->text().isNull() || !this->ui->roleNameField->text().isEmpty()) {
        fill = true;
    }

    if (fill) {
        tempRole.setRoleName(ui->roleNameField->text());
        if (!ui->checkBoxHandlers->checkState()) {
            tempRole.setHandlersUse(false);
        } else {
            tempRole.setHandlersUse(true);
        }
        if (!ui->checkBoxTemplateUse->checkState()) {
            tempRole.setTemplatesUse(false);
        } else {
            tempRole.setTemplatesUse(true);
        }

        *ptrRole = tempRole;
        this->setResult(QDialog::Accepted);

        this->~newRoleForm();
    }
}

void newRoleForm::on_buttonBox_rejected()
{
    this->setResult(QDialog::Rejected);
    this->~newRoleForm();
}

newRoleForm::~newRoleForm()
{
    delete ui;
}
