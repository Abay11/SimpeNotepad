#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(okClicked()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(lineEditChanged(QString)));
}

void Dialog::okClicked()
{
    emit sentFilePath(ui->lineEdit->text());
    close();
}

void Dialog::lineEditChanged(QString)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!ui->lineEdit->text().isEmpty());
}

Dialog::~Dialog()
{
    delete ui;
}
