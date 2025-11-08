#include "dialogbrisanjeid.h"
#include "ui_dialogbrisanjeid.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

DialogBrisanjeID::DialogBrisanjeID(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBrisanjeID)
{
    ui->setupUi(this);
    this->setFixedSize(300,240);
    this->setWindowTitle("Obrisi korisnika");
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DialogBrisanjeID::obrisiKorisnika);
    //qDebug() << "Dijalog za brisanje pokrenut!";
}

DialogBrisanjeID::~DialogBrisanjeID()
{
    delete ui;
}

void DialogBrisanjeID::obrisiKorisnika()
{
    QString idText = ui->lineEditID->text().trimmed();
    bool ok;
    int id = idText.toInt(&ok);

    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Greška", "Unesite ispravan ID!");
        return;
    }

    qDebug() << "Uneseni ID za brisanje je:" << id;

    QSqlQuery provjera;
    provjera.prepare("SELECT COUNT(*) FROM korisnici WHERE id = ?");
    provjera.addBindValue(id);

    if (!provjera.exec()) {
        qDebug() << "Greška u provjeri ID-a:" << provjera.lastError().text();
        QMessageBox::critical(this, "Greška", "Greška prilikom provjere ID-a: " + provjera.lastError().text());
        return;
    }

    provjera.next();
    int broj = provjera.value(0).toInt();
    qDebug() << "Broj pronađenih korisnika sa tim ID-em:" << broj;

    if (broj == 0) {
        QMessageBox::warning(this, "Nepostojeći ID", "Korisnik sa ID-em " + QString::number(id) + " ne postoji.");
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM korisnici WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Greška u brisanju:" << query.lastError().text();
        QMessageBox::critical(this, "Greška", "Neuspješno brisanje: " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Uspješno obrisano", "Korisnik s ID-em " + QString::number(id) + " je obrisan.");
    }
}
