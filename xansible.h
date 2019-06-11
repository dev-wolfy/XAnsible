#ifndef XANSIBLE_H
#define XANSIBLE_H

#include <QMainWindow>
#include <QFileDialog>
#include <QInputDialog>
#include <QFileSystemModel>
#include <QListView>
#include <QMessageBox>
#include <QString>
#include <QList>
#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QVBoxLayout>
#include <QLayout>
#include <QPlainTextEdit>
#include <QToolBar>
#include <QtXml/QtXml>
#include <QtXml/QXmlReader>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

#include "hostgroup.h"
#include "newhostform.h"
#include "newplaybookform.h"
#include "newroleform.h"
#include "newtaskform.h"
#include "playbook.h"
#include "tabpageedit.h"
#include "p_role.h"
#include "apropos.h"

namespace Ui {
class xansible;
}

class xansible : public QMainWindow
{
    Q_OBJECT

public:
    explicit xansible(QWidget *parent = nullptr);
    ~xansible();

    playbook Playbook;

    QList<hostGroup> hostsArray;
    QList<hostGroup> getHostsArray() const;
    QList<tabPageEdit*> EditList;
    void setHostsArray(const QList<hostGroup> &value);
    void writeAnsibleProjectFile();

private slots:
    void newHost();
    void newPlaybook();
    void openPlaybook();
    void newRole();
    void newTask();
    void aProposF();
    void exit();

    void saveFile();

private:    
    Ui::xansible *ui;
    QList<tabPageEdit*> pages;

    QString defaultFolderForPlaybook; // /home/ansible

    QString currentFile;
    QString currentPlaybook; // wolf
    QString currentPlaybookFolder; // /home/wolf/Documents/wolf

    QList<QString> playbooksElement;

    QFileSystemModel arboModel;
    void renderFileSystem();
    void readEtcAnsibleHosts();
    void writeEtcAnsibleHosts();
    void populateListOfHost();
};

#endif // XANSIBLE_H
