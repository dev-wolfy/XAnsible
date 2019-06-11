#ifndef NEWTASKFORM_H
#define NEWTASKFORM_H

#include <QDialog>
#include <QList>
#include <QTextEdit>
#include <QTextDocument>
#include <QTextBrowser>
#include <QFile>
#include <QResource>
#include <QCompleter>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStringListModel>

#include "tabpageedit.h"

namespace Ui {
class newTaskForm;
}

class newTaskForm : public QDialog
{
    Q_OBJECT

public:
    explicit newTaskForm(QWidget *parent = nullptr, QList<tabPageEdit*> *EditList = nullptr);
    ~newTaskForm();

    QList<tabPageEdit*> *ptr_EditList;

    QString getTaskName() const;
    void setTaskName(const QString &value);

private:
    Ui::newTaskForm *ui;
    QCompleter *completer;

    QString taskName;

    void setUpModuleFamily();
    void setUpModuleName();
    void setUpDescription();
    void setUpTaskScript();
    QString formatHtmlSourceCode(const QString &sourceToInsert);
    //QAbstractItemModel *modelFromFile(const QString &fileName);
};

#endif // NEWTASKFORM_H
