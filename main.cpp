#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

/*
 * 1 Generisanje 3 buttona po zelji - imam OK CANCEL INFO i imam 2 textBoxa za unos imena i prezimena
 *
 * 2 Kreirana baza s parametrima u SQLu
 * Koristena MySQL BP
 * Prednosti: brze upravljanje, dodavanje, brisanje podataka
 * U praksi se najcesce koristi za: baze podataka
 *
 * 3 Povezivanje preko ODBC
 * Koristen je ODBC 32-bit program ( ODBC Data Source Administrator)
 * Connector/ODBC je verzije 8.0.42 32-bit - skinut sa nazivom (mysql-connector-odbc-8.0.42-win32.msi)
 * Na System DSN dodat novi source pomocu ADD pa MySQL ODBC 8.0 Unicode Driver
 * U slijedecem prozoru:
 * Data Source name (DSN): qt_odbc
 * TCP/Ip Server: localhost
 * Port: 3306
 * User: root
 * Password:password - odnosno sifra od MySQL servera
 * Database: qt_projekat - baza sa kojom se manipulise
 */
