#include "dirviewer.h"
#include "ui_dirviewer.h"

DirViewer::DirViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DirViewer)
{
    ui->setupUi(this);

    setWindowTitle("Directories");
    ui->treeWidget->setHeaderLabel("Name");
}

QTreeWidget *DirViewer::getTreeWidget()
{
    return ui->treeWidget;
}

DirViewer::~DirViewer()
{
    delete ui;
}
