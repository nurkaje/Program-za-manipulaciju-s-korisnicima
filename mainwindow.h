#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionInfo_triggered();

    void on_actionHelp_triggered();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    void testInsert();
    void dodajKorisnika();
    void ponistiUnos();
    void prikaziInfo();
    void ucitajKorisnike();
    void otvoriDialogBrisanje();
    void ucitajProcese();
};

#endif // MAINWINDOW_H
