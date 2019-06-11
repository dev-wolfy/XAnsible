#ifndef P_ROLE_H
#define P_ROLE_H

#include <QString>
#include <QFile>
#include <QMessageBox>

class p_role
{
public:

    p_role();
    QString getRoleName() const;
    void setRoleName(const QString &value);

    QFile *handlersFile;
    QFile *mainTasksFile;

    QString getRolePath() const;
    void setRolePath(const QString &value);

    void setMainTasksFile(const QString &value);
    void setHandlersFile(const QString &value);

    bool getHandlersUse() const;
    void setHandlersUse(bool value);

    bool getTemplatesUse() const;
    void setTemplatesUse(bool value);

    QString getTemplateName() const;
    void setTemplateName(const QString &value);

private:
    QString roleName;
    QString rolePath;
    bool handlersUse;
    bool templatesUse;
    QString templateName;
};

#endif // P_ROLE_H
