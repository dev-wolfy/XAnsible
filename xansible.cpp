#include "xansible.h"
#include "ui_xansible.h"

xansible::xansible(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::xansible)
{
    ui->setupUi(this);

    readEtcAnsibleHosts();
    populateListOfHost();
    defaultFolderForPlaybook = "~/playbooks/";

    connect(ui->actionNewHost, &QAction::triggered, this, &xansible::newHost);
    connect(ui->actionNewPlaybook, &QAction::triggered, this, &xansible::newPlaybook);
    connect(ui->actionOpenPlaybook, &QAction::triggered, this, &xansible::openPlaybook);
    connect(ui->actionNewRole, &QAction::triggered, this, &xansible::newRole);
    connect(ui->actionNewTask, &QAction::triggered, this, &xansible::newTask);
    connect(ui->actionSave, &QAction::triggered, this, &xansible::saveFile);

    connect(ui->action_apropos, &QAction::triggered, this, &xansible::aProposF);
    connect(ui->actionQuitter, &QAction::triggered, this, &xansible::exit);

}

void xansible::newHost()
{
    newHostForm *NewHostForm = new newHostForm(nullptr, &hostsArray);
    NewHostForm->exec();
    populateListOfHost();
    writeEtcAnsibleHosts();
}

void xansible::newPlaybook()
{
    // création de 2 variable pour vérifier la création du playbook
    QString actualPlaybook = this->Playbook.getNom();
    QString newPlaybookOrNot = "";

    // new page edit pour le futur fichier à éditer
    tabPageEdit *newTab = nullptr;

    newPlaybookForm *NewPlaybookForm = new newPlaybookForm(nullptr, &Playbook);
    NewPlaybookForm->getHostsGroups(this->getHostsArray());
    NewPlaybookForm->exec(); // -> lancement de la fenêtre bloquante

    newPlaybookOrNot = this->Playbook.getNom();

    if (actualPlaybook != newPlaybookOrNot) { // Si un nouveau playbook est renseigné

        this->Playbook.setIs_Defined(true);
        QDir().mkpath(this->Playbook.getChemin()); // Création du doss /home/ansible/project/Xansible
        QDir().mkpath(this->Playbook.getChemin() + "/roles/");

        QString fileName = this->Playbook.getChemin() + "/" + this->Playbook.getNom() + ".yml";
        QString projectFileName = this->Playbook.getChemin() + "/" + this->Playbook.getNom() + ".pro";
        QFile file(fileName); // Création du fichier playbook
        QFile fileProject(projectFileName);

        if (fileProject.open(QFile::WriteOnly | QFile::Text)) {
            fileProject.close();
        } else {
            QMessageBox::warning(this, "Attention", "Impossible de créer le fichier de description du projet : " + fileProject.errorString());
        }

        if (file.open(QFile::WriteOnly | QFile::Text)) { // Init du remplissage du playbook

            QTextStream out(&file);
            out << this->Playbook.initPlaybookFile(); // Remplissage avec base
            file.flush();
            file.close();

        } else {
            QMessageBox::warning(this, "Attention", "Impossible d'ouvrir le fichier: " + file.errorString());
            return;
        }

        newTab = new tabPageEdit;
        EditList.append(newTab);
        newTab->setFullPathFileName(this->Playbook.getChemin() + "/" + this->Playbook.getNom() + ".yml");
        newTab->setFileName(this->Playbook.getNom() + ".yml");
        newTab->openFile();
        this->pages.append(newTab);
        ui->tab_edit_structure->addTab(newTab, newTab->getFileName());

        QFileSystemModel *model = new QFileSystemModel;
        model->setRootPath(QDir::currentPath());
        ui->treeView->setModel(model);

        writeAnsibleProjectFile();
    }
}

void xansible::openPlaybook()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Selectionner un fichier projet XAnsible"),
                                                    "/home/ansible/project",
                                                    tr("Text files (*.pro)"));
    QDomDocument document;
    QString becomeUser = "0";

    tabPageEdit *newTab = nullptr;
    tabPageEdit *newTab2 = nullptr;
    tabPageEdit *newTab3 = nullptr;

    QString nbRolesString = "";

    if (fileName.indexOf(".pro")) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Attention", "Impossible d'ouvrir le fichier projet .pro");
            return;
        } else {
            document.setContent(&file);
            file.close();

            QDomElement root = document.documentElement();
            if (root.tagName() != "playbook") {
                qDebug() << "erreur dans la structure du fichier - root element non playbook";
                return;
            }
            if (!root.hasAttribute("Name")) {
                qDebug() << "erreur dans la structure du fichier - pas de nom au playbook";
                return;
            }
            this->Playbook.setNom(root.attribute("Name", "erreur"));

            QDomElement child = root.firstChild().toElement();

            while (!child.isNull()) {
                if (child.tagName() == "dataPath") {
                    this->Playbook.setChemin(child.attribute("Path", "erreur"));
                    this->Playbook.setIs_Defined(true);
                } else if (child.tagName() == "dataName") {
                    this->Playbook.setNom(child.attribute("Name", "erreur"));
                } else if (child.tagName() == "dataDesc") {
                    this->Playbook.setDescription(child.attribute("Description", "erreur"));
                } else if (child.tagName() == "dataHostGroup") {
                    this->Playbook.setHostGroup(child.attribute("HostGroup", "erreur"));
                } else if (child.tagName() == "dataUser") {
                    this->Playbook.setUser(child.attribute("User", "erreur"));
                    becomeUser = child.attribute("BecomeUser", "0");

                    if (becomeUser == "1") {
                        this->Playbook.setBecomeUser(true);
                    } else {
                        this->Playbook.setBecomeUser(false);
                    }

                    newTab = new tabPageEdit;
                    EditList.append(newTab);
                    newTab->setFullPathFileName(this->Playbook.getChemin() + "/" + this->Playbook.getNom() + ".yml");
                    newTab->setFileName(this->Playbook.getNom() + ".yml");
                    newTab->openFile();
                    this->pages.append(newTab);
                    ui->tab_edit_structure->addTab(newTab, newTab->getFileName());

                } else if (child.tagName() == "roles") {

                    QDomElement rolesChild = child.firstChild().toElement();
                    while (!rolesChild.isNull()) {

                        p_role newRole;
                        newRole.setRoleName(rolesChild.attribute("Nom", "erreur"));
                        newRole.setRolePath(rolesChild.attribute("Path", "erreur"));

                        newTab2 = new tabPageEdit;
                        EditList.append(newTab2);
                        newTab2->setFullPathFileName(newRole.getRolePath() + "/tasks/main.yml");
                        newTab2->setFileName(newRole.getRoleName() + "/tasks/main.yml");
                        newTab2->openFile();
                        this->pages.append(newTab2);
                        ui->tab_edit_structure->addTab(newTab2, newTab2->getFileName());

                        QDomElement roleElement = rolesChild.firstChild().toElement();
                        while (!roleElement.isNull()) {

                            if (roleElement.tagName() == "handlers") {
                                if (roleElement.attribute("Usage", "KO") == "OK") {
                                    newRole.setHandlersUse(true);

                                    newTab3 = new tabPageEdit;
                                    EditList.append(newTab3);
                                    newTab3->setFullPathFileName(newRole.getRolePath() + "/handlers/main.yml");
                                    newTab3->setFileName(newRole.getRoleName() + "/handlers/main.yml");
                                    newTab3->openFile();
                                    this->pages.append(newTab3);
                                    ui->tab_edit_structure->addTab(newTab3, newTab3->getFileName());

                                } else {
                                    newRole.setHandlersUse(false);
                                }
                            } else if (roleElement.tagName() == "templates") {
                                if (roleElement.attribute("Usage", "KO") == "OK") {
                                    newRole.setTemplatesUse(true);
                                } else {
                                    newRole.setTemplatesUse(false);
                                }
                            }

                            roleElement = roleElement.nextSibling().toElement();
                        }

                        this->Playbook.roles.append(newRole);
                        rolesChild = rolesChild.nextSibling().toElement();
                    }
                }
                child = child.nextSibling().toElement();
            }
        }
    }
}

void xansible::newRole()
{
    p_role newRole;
    int nbTab = 0;
    int indexOfRole = 0;
    int indexOfPoints = 0;
    QString playbookFileContent = "";

    tabPageEdit *newTab = nullptr;
    tabPageEdit *newTab2 = nullptr;


    newRoleForm *NewRoleForm = new newRoleForm(nullptr, &newRole);
    NewRoleForm->exec();

    if (!newRole.getRoleName().isEmpty()) {
        if (this->Playbook.isDefined()) {

            // /home/ansible/projet/XAnsible/roles/apache2
            newRole.setRolePath(this->Playbook.getChemin() + "/roles/" + newRole.getRoleName());
            // /home/ansible/projet/XAnsible/roles/apache2/tasks/
            QDir().mkpath(newRole.getRolePath() + "/tasks/");

            if (QDir().exists(newRole.getRolePath() + "/tasks/")) {
                // /home/ansible/projet/XAnsible/roles/apache2/tasks/main.yml
                newRole.setMainTasksFile(newRole.getRolePath() + "/tasks/main.yml");

                newTab = new tabPageEdit;
                EditList.append(newTab);
                newTab->setFullPathFileName(newRole.getRolePath() + "/tasks/main.yml");
                newTab->setFileName(newRole.getRoleName() + "/tasks/main.yml");
                newTab->openFile();
                this->pages.append(newTab);
                ui->tab_edit_structure->addTab(newTab, newTab->getFileName());


            } else {
                QMessageBox::warning(this, "Attention", "Le dossier des tasks du nouveau rôle n'est pas créé...");
            }

            if (newRole.getHandlersUse()) {
                QDir().mkpath(newRole.getRolePath() + "/handlers/");
                if (QDir().exists(newRole.getRolePath() + "/handlers/")) {
                    newRole.setHandlersFile(newRole.getRolePath() + "/handlers/main.yml");

                    newTab2 = new tabPageEdit;
                    EditList.append(newTab2);
                    newTab2->setFullPathFileName(newRole.getRolePath() + "/handlers/main.yml");
                    newTab2->setFileName(newRole.getRoleName() + "/handlers/main.yml");
                    newTab2->openFile();
                    this->pages.append(newTab2);
                    ui->tab_edit_structure->addTab(newTab2, newTab2->getFileName());

                }
            }

            if (newRole.getTemplatesUse()) {
                QDir().mkpath(newRole.getRolePath() + "/templates/");
            }

            nbTab = EditList.length();
            for (int i = 0; i < nbTab; ++i) {
                if (EditList[i]->getFileName() == this->Playbook.getNom() + ".yml") {
                    playbookFileContent = EditList[i]->getTextFromPlainTextEdit();
                    i = nbTab + 1;
                }
            }

            if (playbookFileContent.indexOf("roles:") == -1) {
                if(playbookFileContent.indexOf("..."))
                {
                    playbookFileContent = EditList[0]->getTextFromPlainTextEdit();
                    indexOfPoints = playbookFileContent.indexOf("...");
                    playbookFileContent.insert(indexOfPoints, "  roles:\n");
                    EditList[0]->setTextFromPlainTextEdit(playbookFileContent);
                    EditList[0]->saveFile();
                } else {
                    playbookFileContent = EditList[0]->getTextFromPlainTextEdit();
                    playbookFileContent.append("\n...");
                    EditList[0]->setTextFromPlainTextEdit(playbookFileContent);
                    EditList[0]->saveFile();
                }
            }
            indexOfRole = playbookFileContent.indexOf("...");
            playbookFileContent = EditList[0]->plainTextEdit()->toPlainText();
            playbookFileContent.insert(indexOfRole, "   - " + newRole.getRoleName() + "\n");
            EditList[0]->setTextFromPlainTextEdit(playbookFileContent);
            EditList[0]->saveFile();


            this->Playbook.roles.append(newRole);
        } else {
            QMessageBox::warning(this, "Attention", "Playbook de défini!");
        }

    }
    writeAnsibleProjectFile();

}

void xansible::newTask()
{
    newTaskForm *newtaskform = new newTaskForm;
    newtaskform->exec();
}

void xansible::aProposF()
{
    aPropos *apropos = new aPropos;
    apropos->exec();
}

void xansible::exit()
{
    QCoreApplication::quit();
}

QList<hostGroup> xansible::getHostsArray() const
{
    return hostsArray;
}

void xansible::setHostsArray(const QList<hostGroup> &value)
{
    hostsArray = value;
}

void xansible::writeAnsibleProjectFile()
{
    QDomDocument document;
    int nbRole = this->Playbook.roles.count();
    int i = 0;

    QDomElement root = document.createElement("playbook");
    root.setAttribute("Name", this->Playbook.getNom());
    document.appendChild(root);

    QDomElement dataPath = document.createElement("dataPath");
    dataPath.setAttribute("Path", this->Playbook.getChemin());
    root.appendChild(dataPath);

    QDomElement dataName = document.createElement("dataName");
    dataName.setAttribute("Name", this->Playbook.getNom());
    root.appendChild(dataName);

    QDomElement dataDesc = document.createElement("dataDesc");
    dataDesc.setAttribute("Description", this->Playbook.getDescription());
    root.appendChild(dataDesc);

    QDomElement dataHostGroup = document.createElement("dataHostGroup");
    dataHostGroup.setAttribute("HostGroup", this->Playbook.getHostGroup());
    root.appendChild(dataHostGroup);

    QDomElement dataUser = document.createElement("dataUser");
    dataUser.setAttribute("User", this->Playbook.getUser());
    dataUser.setAttribute("BecomeUser", this->Playbook.getBecomeUser());
    root.appendChild(dataUser);

    QDomElement roles = document.createElement("roles");
    roles.setAttribute("Nb", this->Playbook.roles.count());
    root.appendChild(roles);

    for (i = 0; i < nbRole; ++i) {
        QDomElement role = document.createElement("role" + QString::number(i));
        role.setAttribute("Nom", this->Playbook.roles[i].getRoleName());
        role.setAttribute("Path", this->Playbook.roles[i].getRolePath());
        roles.appendChild(role);

        if (this->Playbook.roles[i].getHandlersUse()) {
            QDomElement handlers = document.createElement("handlers");
            handlers.setAttribute("Usage", "OK");
            role.appendChild(handlers);
        }
        if (this->Playbook.roles[i].getTemplatesUse()) {
            QDomElement templates = document.createElement("templates");
            templates.setAttribute("Usage", "OK");
            role.appendChild(templates);
        }
        if (!this->Playbook.roles[i].getTemplateName().isEmpty() | !this->Playbook.roles[i].getTemplateName().isNull()) {
            QDomElement templateName = document.createElement("templateName");
            templateName.setAttribute("Name", this->Playbook.roles[i].getTemplateName());
            role.appendChild(templateName);
        }

    }

    // Ecriture du fichier
    QFile file(this->Playbook.getChemin() + "/" + this->Playbook.getNom() + ".pro");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << document.toString();
        file.close();
    } else {
        QMessageBox::warning(this, "Attention", "Impossible d'écrire le fichier projet .pro");
    }
}

void xansible::renderFileSystem()
{
    QFileSystemModel *arbo = new QFileSystemModel;
    QDir path = QDir::currentPath();
    path.setPath("/home");
    arbo->setRootPath(path.path());
    ui->treeView->setModel(arbo);
}

void xansible::readEtcAnsibleHosts()
{
    //QString text = "";
    QString line = "";
    int nbGroupe = 0;
    QFile file("/etc/ansible/hosts");
    hostGroup* newGroupOfHost = new hostGroup;
    int i = 0;

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            line = in.readLine();

            if (line[0] == "#") {
                //qDebug() << "#";
            } else if (line[0] == "[") {

                if (nbGroupe) {
                    hostsArray.append(*newGroupOfHost);
                }
                ++nbGroupe;
                newGroupOfHost = new hostGroup;
                newGroupOfHost->setGroupName(line.remove("[").remove("]"));

            } else if (line == "") {
                //qDebug() << "ola empty";
            } else {
                newGroupOfHost->appendHosts(line);
            }
            ++i;

        }
        if (nbGroupe > 0) {
            hostsArray.append(*newGroupOfHost);
        }
        file.close();
    }
}

void xansible::writeEtcAnsibleHosts()
{
    QFile file("/etc/ansible/hosts");
    int nbGroup = hostsArray.length();

    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        for (int i = 0; i < nbGroup; ++i) {
            out << "[" << hostsArray[i].getGroupName() << "]\n";
            int nbHosts = hostsArray[i].getHosts().length();
            if (nbHosts) {
                QList<QString> hosts = hostsArray[i].getHosts();
                for (int j = 0; j < nbHosts; ++j) {
                    out << hosts.at(j) << "\n";
                }
            }
            out << "\n";
        }
        file.close();
    } else {
        QMessageBox::critical(this, "Probleme!", "Impossible d'ouvrir le fichier /etc/ansible/hosts");
    }
}

void xansible::populateListOfHost()
{
    int nbGroup = hostsArray.length();
    QString groupeName;

    int nbHosts = 0;
    QList<QString> hostsForGroup;

    ui->listWidget->clear();

    if (nbGroup) {
        for (int i = 0; i < nbGroup; ++i) {
            groupeName = hostsArray[i].getGroupName();
            ui->listWidget->addItem("[" + groupeName + "]");

            hostsForGroup = hostsArray[i].getHosts();
            nbHosts = hostsForGroup.length();
            if (nbHosts) {
                for (int j = 0; j < nbHosts; ++j) {
                    ui->listWidget->addItem(hostsForGroup[j]);
                }
            }
        }
    } else {
        ui->listWidget->addItem("Pas d'hôtes");
    }


}

void xansible::saveFile()
{
    QString fileName = ui->tab_edit_structure->tabText(ui->tab_edit_structure->currentIndex());
    QString fileContent = "";
    int nbTab = EditList.length();

    for (int i = 0; i < nbTab; ++i) {
        if (EditList[i]->getFileName() == fileName) {
            if (fileName.indexOf("/") != -1) {
                fileName = "roles/" + fileName;
            }
            QFile fileToSave(this->Playbook.getChemin() + "/" + fileName);
            if (fileToSave.open(QFile::WriteOnly | QFile::Text)) {
                QTextStream out(&fileToSave);
                fileContent = EditList[i]->getTextFromPlainTextEdit();
                out << fileContent;
                fileToSave.close();
            }
            i = nbTab + 1;
        }
    }
}



xansible::~xansible()
{
    delete ui;
}
