#ifndef PLAYBOOK_H
#define PLAYBOOK_H

#include <QString>
#include <QList>
#include <QMap>
#include "p_role.h"

class playbook
{

public:
    playbook();
    QString getNom() const;
    void setNom(const QString &value);
    QString getChemin() const;
    void setChemin(const QString &value);
    QString getHostGroup() const;
    void setHostGroup(const QString &value);
    QString getUser() const;
    void setUser(const QString &value);
    bool getBecomeUser() const;
    void setBecomeUser(bool value);
    QString getDescription() const;
    void setDescription(const QString &value);

    QString initPlaybookFile();

    QList<p_role> roles;
    //QList<QMap<QString, QString>> vars;

    bool isDefined() const;
    void setIs_Defined(bool value);

private:
    QString nom;
    QString description;
    QString chemin;
    QString hostGroup;
    QString user;
    bool becomeUser;
    bool is_Defined;
};

#endif // PLAYBOOK_H
