#include "newplaybookform.h"
#include "ui_newplaybookform.h"

newPlaybookForm::newPlaybookForm(QWidget *parent, playbook *Playbook) :
    QDialog(parent),
    ui(new Ui::newPlaybookForm)
{
    ui->setupUi(this);

    setPlaybook(Playbook);

    connect(ui->selectPathButton, &QPushButton::clicked, this, &newPlaybookForm::selectPath);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &newPlaybookForm::on_buttonBox_accepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &newPlaybookForm::on_buttonBox_rejected);
}

newPlaybookForm::~newPlaybookForm()
{
    delete ui;
}

void newPlaybookForm::selectPath()
{
    QString locationPath = "/home/ansible/";

    locationPath = QFileDialog::getExistingDirectory(this, "Selectionner un dossier");

    if (!locationPath.isEmpty() || !locationPath.isNull()) {
        ui->playbookPathField->setText(locationPath);
    } else {
        ui->playbookNameField->setText("/home/ansible");
    }
}

void newPlaybookForm::on_buttonBox_accepted()
{
    bool fill = false;

    if (!ui->playbookNameField->text().isNull() || !ui->playbookNameField->text().isEmpty()) {
        if (!ui->playbookDescriptionField->text().isNull() || !ui->playbookDescriptionField->text().isEmpty()) {
            if (!ui->playbookPathField->text().isNull() || !ui->playbookPathField->text().isEmpty()) {
                if (!ui->userField->text().isNull() || !ui->userField->text().isEmpty()) {
                    fill = true;
                }
            }
        }
    }

    if (fill) {

        playbook tempPlaybook;
        tempPlaybook.setNom(ui->playbookNameField->text());
        tempPlaybook.setDescription(ui->playbookDescriptionField->text());
        tempPlaybook.setChemin(ui->playbookPathField->text() + "/" + ui->playbookNameField->text());
        tempPlaybook.setHostGroup(ui->groupeOfHostField->currentText());
        tempPlaybook.setUser(ui->userField->text());
        if (!ui->becomeUserCheckBox->checkState()) {
            tempPlaybook.setBecomeUser(false);
        } else {
            tempPlaybook.setBecomeUser(true);
        }

        *Playbook = tempPlaybook;
        this->setResult(QDialog::Accepted);
    }

    this->~newPlaybookForm();
}

void newPlaybookForm::on_buttonBox_rejected()
{
    this->setResult(QDialog::Rejected);
    this->~newPlaybookForm();
}

void newPlaybookForm::getHostsGroups(const QList<hostGroup> &value)
{
    int nb_group = value.length();

    for (int i = 0; i < nb_group; ++i) {
        ui->groupeOfHostField->addItem(value[i].getGroupName(), QVariant(i));
    }
}

playbook *newPlaybookForm::getPlaybook() const
{
    return Playbook;
}

void newPlaybookForm::setPlaybook(playbook *value)
{
    Playbook = value;
}
