#include "hostgroup.h"

hostGroup::hostGroup()
{
    disableGroup = false;
}

QList<QString> hostGroup::getHosts() const
{
    return hosts;
}

void hostGroup::setHosts(const QList<QString> &value)
{
    hosts = value;
}

void hostGroup::removeHosts(int hostId)
{
    hosts.removeAt(hostId);
}

void hostGroup::removeAllHosts()
{
    hosts.clear();
}

void hostGroup::appendHosts(const QString value)
{
    hosts.append(value);
}

QString hostGroup::getGroupName() const
{
    return groupName;
}

void hostGroup::setGroupName(const QString &value)
{
    groupName = value;
}

bool hostGroup::getDisableGroup() const
{
    return disableGroup;
}

void hostGroup::setDisableGroup(bool value)
{
    disableGroup = value;
}
