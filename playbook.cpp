#include "playbook.h"

QString playbook::getNom() const
{
    return nom;
}

void playbook::setNom(const QString &value)
{
    nom = value;
}

QString playbook::getChemin() const
{
    return chemin;
}

void playbook::setChemin(const QString &value)
{
    chemin = value;
}

QString playbook::getHostGroup() const
{
    return hostGroup;
}

void playbook::setHostGroup(const QString &value)
{
    hostGroup = value;
}

QString playbook::getUser() const
{
    return user;
}

void playbook::setUser(const QString &value)
{
    user = value;
}

bool playbook::getBecomeUser() const
{
    return becomeUser;
}

void playbook::setBecomeUser(bool value)
{
    becomeUser = value;
}

playbook::playbook()
{
    setIs_Defined(false);
}

QString playbook::initPlaybookFile()
{
    QString contentFile = "";

    contentFile.append("---\n\n");
    contentFile.append("- name: "        + this->getDescription() + "\n");
    contentFile.append("  hosts: "       + this->getHostGroup()   + "\n");
    contentFile.append("  remote_user: " + this->getUser()        + "\n");

    contentFile.append("\n...");

    return contentFile;
}

bool playbook::isDefined() const
{
    return is_Defined;
}

void playbook::setIs_Defined(bool value)
{
    is_Defined = value;
}

QString playbook::getDescription() const
{
    return description;
}

void playbook::setDescription(const QString &value)
{
    description = value;
}
