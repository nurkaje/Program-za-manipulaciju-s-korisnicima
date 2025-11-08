#ifndef GANTTDIALOG_H
#define GANTTDIALOG_H

#include <QDialog>
#include <QGraphicsScene>

namespace Ui {
class GanttDialog;
}

class GanttDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GanttDialog(QWidget *parent = 0);
    ~GanttDialog();

    void nacrtajDijagram();

private:
    Ui::GanttDialog *ui;
    QGraphicsScene *scena;
};

#endif // GANTTDIALOG_H
