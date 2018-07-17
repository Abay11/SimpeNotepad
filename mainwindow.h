#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialog.h"
#include "dirviewer.h"

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
#include <QLabel>
#include <QTreeWidgetItem>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void recursiveDirPrint(QDir *path, QTreeWidgetItem *item);

public slots:
    void readClicked();
    void saveClicked();
    void printDirClicked();
    void receivePathToReading(QString);
    void receivePathToWriting(QString);
    void receivePathToDirPrinting(QString);

signals:
private slots:
    void on_actionClear_triggered();
};

#endif // MAINWINDOW_H
