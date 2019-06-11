#include "newhostform.h"
#include "ui_newhostform.h"

newHostForm::newHostForm(QWidget *parent, QList<hostGroup>* listOfHostGroup) :
    QDialog(parent),
    ui(new Ui::newHostForm)
{
    hostsArray = listOfHostGroup;

    ui->setupUi(this);

    setGroupOnUI();

    connect(ui->addGroupHost, &QPushButton::clicked, this, &newHostForm::addNewGroup);
    connect(ui->disableGroupHost, &QPushButton::clicked, this, &newHostForm::disableGroup);
    connect(ui->deleteGroupHost, &QPushButton::clicked, this, &newHostForm::deleteGroup);
    connect(ui->listGroupHost, &QListWidget::itemClicked, this, &newHostForm::setHostOnUI);

    connect(ui->addHost, &QPushButton::clicked, this, &newHostForm::addNewHost);
    connect(ui->deleteHost, &QPushButton::clicked, this, &newHostForm::deleteHost);
}

void newHostForm::addNewGroup()
{
    bool ok = false;
    QString newGroupName = QInputDialog::getText(this, "Nouveau groupe", "Nom du groupe : ", QLineEdit::Normal, QString(), &ok);

    if (ok && !newGroupName.isEmpty()) {
        hostGroup newGroup;
        newGroup.setGroupName(newGroupName);
        hostsArray->append(newGroup);

        setGroupOnUI();
        ui->listGroupHost->setCurrentRow(hostsArray->length() - 1);
        setHostOnUI();
    }
}

void newHostForm::disableGroup()
{
    /*QListWidgetItem *newItem = ui->listGroupHost->currentItem();
    if (newItem != nullptr) {
        int groupId = getIndexForGroup(newItem->text());
        if (groupId != -1) {
            *hostsArray->at()
            //setGroupOnUI();
        }
    }

    int groupId = getIndexForGroup(ui->listGroupHost->currentItem()->text());
    if (groupId != -1) {
        bool tata = hostsArray->at(groupId).getDisableGroup();
        qDebug() << tata;
    }*/
}

void newHostForm::deleteGroup()
{
    QListWidgetItem *newItem = ui->listGroupHost->currentItem();
    if (newItem != nullptr) {
        if (!newItem->text().isEmpty() || !newItem->text().isNull()) {

            int groupId = getIndexForGroup(newItem->text());

            if (groupId != -1) {
                hostsArray->removeAt(groupId);
                setGroupOnUI();
            }
        }
    }

}

void newHostForm::addNewHost()
{
    bool ok = false;
    QListWidgetItem *selectItem = ui->listGroupHost->currentItem();

    if (selectItem != nullptr) {
        int groupId = getIndexForGroup(selectItem->text());
        if (groupId != -1) {
            QString newHostName = QInputDialog::getText(this, "Nouveau groupe", "Nom du groupe : ", QLineEdit::Normal, QString(), &ok);
            if (ok && !newHostName.isEmpty()) {
                hostsArray[0][groupId].appendHosts(newHostName);
                setHostOnUI();
            }
        }
    }
    else {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un groupe pour ajouter le nouvel host");
    }
}

void newHostForm::deleteHost()
{
    QListWidgetItem *selectItemGroup = ui->listGroupHost->currentItem();
    QListWidgetItem *selectItemHost = ui->listHosts->currentItem();

    if (selectItemGroup != nullptr) {
        if (selectItemHost != nullptr) {
            int groupId = getIndexForGroup(selectItemGroup->text());
            if (groupId != -1) {
                int hostId = getIndexForHost(groupId, selectItemHost->text());
                if (hostId != -1) {
                    hostsArray[0][groupId].removeHosts(hostId);
                    ui->listGroupHost->item(groupId)->setSelected(true);
                    setHostOnUI();
                }
            }
        } else {
            QMessageBox::warning(this, "Attention", "Veuillez sélectionner un hôte pour le supprimer");
        }

    } else {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un groupe pour selectionner un hote");
    }
}

void newHostForm::setGroupOnUI()
{
    int nbGroup = hostsArray->length();

    ui->listGroupHost->clear();
    for (int i = 0; i < nbGroup; ++i) {
        ui->listGroupHost->addItem(hostsArray->at(i).getGroupName());
    }
}

void newHostForm::setHostOnUI()
{
    int currentRow = ui->listGroupHost->currentRow();
    QList<QString> hosts = hostsArray->at(currentRow).getHosts();
    ui->listHosts->clear();
    if (hosts.length()) {
        int nbHost = hosts.length();
        for (int i = 0; i < nbHost; ++i) {
            ui->listHosts->addItem(hosts.at(i));
        }
    }
}

int newHostForm::getIndexForGroup(const QString &value)
{
    int index = -1;
    int nbGroup = hostsArray->length();

    for (int i = 0; i < nbGroup; ++i) {
        if (hostsArray->at(i).getGroupName() == value) {
            index = i;
        }
    }

    return index;
}

int newHostForm::getIndexForHost(int indexGroup, const QString &value)
{
    int index = -1;
    int nbHosts = hostsArray->at(indexGroup).getHosts().length();
    if (nbHosts > 0) {
        QList<QString> searchArrayHosts = hostsArray->at(indexGroup).getHosts();
        for (int i = 0; i < nbHosts; ++i) {
            if (hostsArray->at(indexGroup).getHosts().at(i) == value) {
                index = i;
                nbHosts = i;
            }
        }
    }

    return index;
}

newHostForm::~newHostForm()
{
    delete ui;
}
