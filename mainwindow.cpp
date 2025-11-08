#include "mainwindow.h"
#include "ui_mainwindow.h"
//headeri od baze, dialoga za brisanje,
#include "database.h"
#include "dialogbrisanjeid.h"
#include "dialoginfo.h"
#include "dialoghelp.h"
#include "ganttdialog.h"

//QT biblioteke
#include <QMessageBox>
#include <QDebug>
#include <QFile>

// include za bazu podataka
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>


MainWindow::~MainWindow()
{
    delete ui;
}

//glavna mainWindow f-ja
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(800, 600);  //ako je potrebno, staviti resize da se moze mjenjati velicina
    this->setWindowTitle("Program za manipulaciju korisnicima");

    //za bazu podataka
    if (connectToDatabase()) {
        qDebug() << "Spreman za rad sa bazom!";
    }
    ucitajProcese();

    //funkcija za dodavanje u bazu kada se klikne OK
    connect(ui->pushButtonOK, &QPushButton::clicked, this, &MainWindow::dodajKorisnika);
    //funkcija za ponistavanje unosa
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &MainWindow::ponistiUnos);
    //za prikaz svih korisnika
    connect(ui->pushButtonPrikazi, &QPushButton::clicked, this, &MainWindow::ucitajKorisnike);
    //za otvaranje dialoga za brisanje
    connect(ui->pushButtonOtvoriBrisanje, &QPushButton::clicked, this, &MainWindow::otvoriDialogBrisanje);
}

//funkcija za dodavanje u BP
void MainWindow::dodajKorisnika() {
    QString ime = ui->lineEditIme->text().trimmed();
    QString prezime = ui->lineEditPrezime->text().trimmed();

    if (ime.isEmpty() || prezime.isEmpty()) {
        QMessageBox::warning(this, "Greška", "Unesite i ime i prezime!");
        return;
    }

    int idProcesa = ui->comboBoxProcesi->currentData().toInt();

    //upit za dodavanje u BP
    QSqlQuery query;
    query.prepare("INSERT INTO korisnici (ime, prezime, proces_id) VALUES (?, ?, ?)");
    query.addBindValue(ime);
    query.addBindValue(prezime);
    query.addBindValue(idProcesa);

    //provjera ako comboBox nije odabran
    if (ui->comboBoxProcesi->currentIndex() == -1) {
        QMessageBox::warning(this, "Greška", "Odaberite proces za korisnika!");
        return;
    }

    //provjera ako se ne upise u bazu
    if (!query.exec()) {
        QMessageBox::critical(this, "Greška", "Neuspješan unos u bazu: " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Uspjesno dodavanje", "Korisnik uspješno dodat!");
        ui->lineEditIme->clear();
        ui->lineEditPrezime->clear();
        ucitajKorisnike();  // Osvježi prikaz
    }
}



//funkcija za otvaranje dialoga za brisanje iz baze po ID
void MainWindow::otvoriDialogBrisanje() {
    DialogBrisanjeID dialog(this);
    dialog.exec();
}

//funkcija za ucitavanje korisnika u tabeli i za button prikazi korisnike
void MainWindow::ucitajKorisnike() {
    QSqlQueryModel *model = new QSqlQueryModel(this);

    model->setQuery("SELECT korisnici.id, ime, prezime,proces_id, naziv_procesa "
                    "FROM korisnici "
                    "LEFT JOIN procesi ON korisnici.proces_id = procesi.id");
    ui->tableView->setModel(model);
}

//funkcija za ponistavanje unosa
void MainWindow::ponistiUnos() {
    ui->lineEditIme->clear();
    ui->lineEditPrezime->clear();
}

//funkcija za ucitavanje procesa
void MainWindow::ucitajProcese() {
    QSqlQuery query("SELECT id, naziv_procesa FROM procesi");

    while (query.next()){
        int id = query.value(0).toInt();
        QString naziv = query.value(1).toString();
        ui->comboBoxProcesi->addItem(naziv, id);  // naziv se prikazuje, id se čuva kao userData
    }
}

//funkcija za otvaranje info prozora
void MainWindow::on_actionInfo_triggered()
{
    DialogInfo dialog(this);
    dialog.exec();
}

//funkcija za otvaranje help prozora
void MainWindow::on_actionHelp_triggered()
{
    DialogHelp dialog(this);
    dialog.exec();
}

//nacrtaj ganttov dijagram
void MainWindow::on_pushButton_4_clicked()
{
    GanttDialog dialog(this);
    dialog.exec();
}
