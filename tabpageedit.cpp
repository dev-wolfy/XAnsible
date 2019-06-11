#include "tabpageedit.h"
#include "ui_tabpageedit.h"

tabPageEdit::tabPageEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tabPageEdit)
{
    ui->setupUi(this);
}

tabPageEdit::~tabPageEdit()
{
    delete ui;
}

QString tabPageEdit::getFullPathFileName() const
{
    return fullPathFileName;
}

void tabPageEdit::setFullPathFileName(const QString &value)
{
    fullPathFileName = value;
}

QString tabPageEdit::getFileContent() const
{
    return fileContent;
}

void tabPageEdit::setFileContent(const QString &value)
{
    fileContent = value;
}

void tabPageEdit::saveFile()
{
    QFile file(this->fullPathFileName);

    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        QString text = ui->plainTextEdit->toPlainText();

        out << text;

        file.flush();
        file.close();
    } else {
        QMessageBox::warning(this, "Attention", "Impossible d'enregistrer le fichier : " + file.errorString());
        return;
    }
}

void tabPageEdit::openFile()
{
    QFile file(this->fullPathFileName);

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&file);
        QString text = in.readAll();
        this->setFileContent(text);
        ui->plainTextEdit->setPlainText(text);
        file.flush();
        file.close();

    } else {
        QMessageBox::warning(this, "Attention", "Impossible d'ouvrir le fichier: " + file.errorString());
        return;
    }
}

QPlainTextEdit *tabPageEdit::plainTextEdit()
{
    return ui->plainTextEdit;
}

QString tabPageEdit::getTextFromPlainTextEdit()
{
    return ui->plainTextEdit->toPlainText();
}

void tabPageEdit::setTextFromPlainTextEdit(const QString &value)
{
    ui->plainTextEdit->setPlainText(value);
}

QString tabPageEdit::getFileName() const
{
    return fileName;
}

void tabPageEdit::setFileName(const QString &value)
{
    fileName = value;
}
