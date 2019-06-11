#ifndef TABPAGEEDIT_H
#define TABPAGEEDIT_H

#include <QWidget>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QPlainTextEdit>

namespace Ui {
class tabPageEdit;
}

class tabPageEdit : public QWidget
{
    Q_OBJECT

public:
    explicit tabPageEdit(QWidget *parent = nullptr);

    QString getFullPathFileName() const;
    void setFullPathFileName(const QString &value);

    QString getFileContent() const;
    void setFileContent(const QString &value);

    QString getFileName() const;
    void setFileName(const QString &value);

    void saveFile();
    void openFile();

    QPlainTextEdit *plainTextEdit();

    QString getTextFromPlainTextEdit();
    void setTextFromPlainTextEdit(const QString &value);

    ~tabPageEdit();

private:
    Ui::tabPageEdit *ui;
    QString fullPathFileName;
    QString fileName;
    QString fileContent;
};

#endif // TABPAGEEDIT_H
