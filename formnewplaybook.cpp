#include "formnewplaybook.h"
#include "ui_formnewplaybook.h"

FormNewPlaybook::FormNewPlaybook(QWidget *parent, playbook *Playbook) :
    QWidget(parent),
    ui(new Ui::FormNewPlaybook)
{
    ui->setupUi(this);

    this->Playbook = Playbook;

    connect(ui->locationButton, &QPushButton::clicked, this, &FormNewPlaybook::selectPath);

    connect(ui->playbook_name_field, &QLineEdit::textEdited, this, &FormNewPlaybook::on_playbook_name_field_textChanged);
    connect(ui->pathField, &QLineEdit::textEdited, this, &FormNewPlaybook::on_pathField_textChanged);
    connect(ui->comboBox, SIGNAL(QComboBox::currentIndexChanged(int index)), this, SLOT(FormNewPlaybook::on_comboBox_activated(int index)));
    connect(ui->user_name_field, &QLineEdit::textEdited, this, &FormNewPlaybook::on_user_name_field_textEdited);
    connect(ui->dialog_button_box, &QDialogButtonBox::accepted, this, &FormNewPlaybook::on_dialog_button_box_accepted);
    connect(ui->dialog_button_box, &QDialogButtonBox::rejected, this, &FormNewPlaybook::on_dialog_button_box_rejected);
}

FormNewPlaybook::~FormNewPlaybook()
{
    delete ui;
}

void FormNewPlaybook::selectPath()
{
    QString locationPath = "/home/ansible";
    locationPath = QFileDialog::getExistingDirectory(this, "Selectionnner un dossier");
    if (!locationPath.isEmpty() || !locationPath.isNull()) {
        ui->pathField->setText(locationPath);
    } else {
        ui->pathField->setText("/home/ansible");
    }
}

void FormNewPlaybook::getHostGroup(const QList<hostGroup> &value)
{
    int nb_group = value.length();

    for (int i = 0; i < nb_group; ++i) {
        ui->comboBox->addItem(value[i].getGroupName(), QVariant(i));
    }
}

void FormNewPlaybook::on_user_name_field_textEdited(const QString &arg1)
{
    qDebug() << arg1;
}

void FormNewPlaybook::on_pathField_textChanged(const QString &arg1)
{
    qDebug() << arg1;
}

void FormNewPlaybook::on_playbook_name_field_textChanged(const QString &arg1)
{
    qDebug() << arg1;
}

void FormNewPlaybook::on_comboBox_activated(int index)
{
    qDebug() << index;
}

void FormNewPlaybook::on_dialog_button_box_accepted()
{
    bool fill = false;

    if (!ui->playbook_name_field->text().isNull() || !ui->playbook_name_field->text().isEmpty()) {
        if (!ui->pathField->text().isNull() || !ui->pathField->text().isEmpty()) {
            if (!ui->user_name_field->text().isNull() || !ui->user_name_field->text().isEmpty()) {
                fill = true;
            }
        }
    }

    if (fill) {

        Playbook->setNom(ui->playbook_name_field->text());
        Playbook->setChemin(ui->pathField->text());
        Playbook->setHostGroup(ui->comboBox->currentText());
        Playbook->setUser(ui->user_name_field->text());
        if (ui->become_user_box->checkState() == 2) {
            Playbook->setBecomeUser(true);
        } else {
            Playbook->setBecomeUser(false);
        }
    }

    this->~FormNewPlaybook();

}

void FormNewPlaybook::on_dialog_button_box_rejected()
{
    this->~FormNewPlaybook();
}
