#ifndef DIRVIEWER_H
#define DIRVIEWER_H

#include <QDialog>
#include <QTreeWidget>

namespace Ui {
class DirViewer;
}

class DirViewer : public QDialog
{
    Q_OBJECT

public:
    explicit DirViewer(QWidget *parent = 0);
    QTreeWidget* getTreeWidget();
    ~DirViewer();

private:
    Ui::DirViewer *ui;
};

#endif // DIRVIEWER_H
