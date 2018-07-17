#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);

    QString status("Current directory: ");
    QDir dir("./");
    status += dir.absolutePath();
    statusBar()->addWidget(new QLabel(status));

    connect(ui->mainToolBar->actions().at(0), SIGNAL(triggered(bool)), this, SLOT(readClicked()));
    connect(ui->mainToolBar->actions().at(1), SIGNAL(triggered(bool)), this, SLOT(saveClicked()));
    connect(ui->mainToolBar->actions().at(3), SIGNAL(triggered(bool)), this, SLOT(printDirClicked()));

    setWindowTitle("Super-duper notepad v1.0");
}

void MainWindow::readClicked()
{
    Dialog *d = new Dialog(this);

    connect(d, SIGNAL(sentFilePath(QString)), this, SLOT(receivePathToReading(QString)));
    statusBar()->showMessage("Open a file", 0);
    d->show();
    connect(d, SIGNAL(rejected()), statusBar(), SLOT(clearMessage()));
}

void MainWindow::saveClicked()
{
    statusBar()->showMessage("Set file name to saving");
    Dialog d;
    connect(&d, SIGNAL(sentFilePath(QString)), this, SLOT(receivePathToWriting(QString)));
    connect(&d, SIGNAL(rejected()), statusBar(), SLOT(clearMessage()));
    d.exec();
}

void MainWindow::receivePathToReading(QString path)
{
    statusBar()->showMessage("A file saving", 5000);

    QFile file(path, this);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information (this, "Error", "Can't open a file to read");
        ui->statusBar->showMessage("Can't open a file to read", 5000);
        return;
    }

    QTextStream stream(&file);

    QString buff = stream.readAll();
    ui->textEdit->setText(buff);

    ui->statusBar->showMessage("A file read", 5000);
    file.close();
}

void MainWindow::receivePathToWriting(QString path)
{

    QFile file(path, this);

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::information (this, "Error", "Can't open a file to write");
        ui->statusBar->showMessage("Can't open a file to wrote", 5000);
        return;
    }

    QTextStream stream(&file);

    stream << ui->textEdit->toPlainText();

    file.close();
}

void MainWindow::printDirClicked()
{
    statusBar()->showMessage("Set path to print elements");
    Dialog dialog;
    connect(&dialog,SIGNAL(sentFilePath(QString)), this, SLOT(receivePathToDirPrinting(QString)));
    connect(&dialog,SIGNAL(finished(int)), statusBar(), SLOT(clearMessage()));
    dialog.exec();
}

#include <QHBoxLayout>

void MainWindow::receivePathToDirPrinting(QString path)
{
    DirViewer tree;
    QDir *dir = new QDir(path);
    QTreeWidgetItem *root = new QTreeWidgetItem;
    root->setText(0, dir->dirName());
    recursiveDirPrint(new QDir(path), root);
    tree.getTreeWidget()->addTopLevelItem(root);
    tree.getTreeWidget()->expandAll();
    tree.exec();
}

void MainWindow::recursiveDirPrint(QDir *dir, QTreeWidgetItem *item)
{
    if(!dir->exists())
    {
        QMessageBox::information(this, "Error", "This directory is not exists");
        return;
    }

    QFileInfoList list = dir->entryInfoList();
    auto iter = list.begin();

    ++iter; ++iter;
    for(; iter != list.end(); ++iter)
    {
//        buffer += QString(nSpace, ' ');
//        buffer += iter->baseName() +'\n';
        QTreeWidgetItem *chd = new QTreeWidgetItem;
        chd->setText(0, iter->baseName());
        item->addChild(chd);

        if(iter->isDir())
            recursiveDirPrint(new QDir(iter->absoluteFilePath()), chd);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionClear_triggered()
{
   statusBar()->showMessage("The window cleared", 2000);
}
