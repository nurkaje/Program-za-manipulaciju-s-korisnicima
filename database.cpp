#include "database.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

bool connectToDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("qt_odbc"); // DSN ime iz ODBC

    if (!db.open()) {
        qDebug() << "Greška pri povezivanju:" << db.lastError().text();
        return false;
    } else {
        qDebug() << "Povezivanje uspješno!";
        return true;
    }
}
