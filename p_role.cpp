#include "p_role.h"

p_role::p_role()
{

}

QString p_role::getRoleName() const
{
    return roleName;
}

void p_role::setRoleName(const QString &value)
{
    roleName = value;
}

QString p_role::getRolePath() const
{
    return rolePath;
}

void p_role::setRolePath(const QString &value)
{
    rolePath = value;
}

void p_role::setMainTasksFile(const QString &value)
{
    mainTasksFile = new QFile(value);
    if (mainTasksFile->open(QFile::WriteOnly | QFile::Text)) {
        mainTasksFile->close();
    } else {
        // error
    }

}

void p_role::setHandlersFile(const QString &value)
{
    handlersFile = new QFile(value);
    if (handlersFile->open(QFile::WriteOnly | QFile::Text)) {
        handlersFile->close();
    } else {
        // error
    }
}

bool p_role::getHandlersUse() const
{
    return handlersUse;
}

void p_role::setHandlersUse(bool value)
{
    handlersUse = value;
}

bool p_role::getTemplatesUse() const
{
    return templatesUse;
}

void p_role::setTemplatesUse(bool value)
{
    templatesUse = value;
}

QString p_role::getTemplateName() const
{
    return templateName;
}

void p_role::setTemplateName(const QString &value)
{
    templateName = value;
}
