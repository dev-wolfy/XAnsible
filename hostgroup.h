#ifndef HOSTGROUP_H
#define HOSTGROUP_H

#include <QObject>
#include <QList>
#include <QString>
#include <QMap>

class hostGroup
{
private:
    QString groupName;
    QList<QString> hosts;
    QList<QMap<QString, QString>> vars;
    bool disableGroup;

public:
    hostGroup();

    QString getGroupName() const;
    void setGroupName(const QString &value);

    QList<QString> getHosts() const;
    void setHosts(const QList<QString> &value);
    void appendHosts(const QString value);
    void removeHosts(int hostId);
    void removeAllHosts();

    bool getDisableGroup() const;
    void setDisableGroup(bool value);
};

#endif // HOSTGROUP_H
