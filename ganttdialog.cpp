#include "ganttdialog.h"
#include "ui_ganttdialog.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QDebug>

GanttDialog::GanttDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GanttDialog),
    scena(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scena);
    this->setFixedSize(800,600);
    nacrtajDijagram();
}

GanttDialog::~GanttDialog()
{
    delete ui;
}

void GanttDialog::nacrtajDijagram()
{
    scena->clear();

    QSqlQuery query;
    query.prepare("SELECT korisnici.ime, korisnici.prezime, procesi.naziv_procesa, procesi.trajanje "
                  "FROM korisnici "
                  "JOIN procesi ON korisnici.proces_id = procesi.id");

    if (!query.exec()) {
        qDebug() << "Greška kod SELECT-a za Gantt:" << query.lastError().text();
        return;
    }

    // Prvo: skupiti trajanja zbog ukupnog trajanja
    QList<QPair<QString, int> > procesi;
    while (query.next()) {
        QString tekst = query.value(0).toString() + " " + query.value(1).toString() + ": " + query.value(2).toString();
        int trajanje = query.value(3).toInt();
        procesi.append(qMakePair(tekst, trajanje));
    }

    int ukupnoTrajanje = 0;
    for (int i = 0; i < procesi.size(); ++i) {
        ukupnoTrajanje += procesi[i].second;
    }

    int scenaSirina = 800;
    int scenaVisina = 400;
    int redVisina = 50;
    double skala = ukupnoTrajanje > 0 ? static_cast<double>(scenaSirina) / ukupnoTrajanje : 50;

    int xOffset = 0;
    int y = 0;

    for (int i = 0; i < procesi.size(); ++i) {
        QString labela = procesi[i].first;
        int trajanje = procesi[i].second;

        QGraphicsTextItem *text = scena->addText(labela);
        text->setPos(0, y);

        QGraphicsRectItem *rect = scena->addRect(xOffset, y + 20, trajanje * skala, redVisina - 30);
        rect->setBrush(Qt::blue);

        // Iscrtavanje isprekidane linije između procesa
        if (i < procesi.size() - 1) {
            QPen pen(Qt::DashLine);
            pen.setColor(Qt::darkGray);
            pen.setWidth(1);
            scena->addLine(xOffset + trajanje * skala, 0, xOffset + trajanje * skala, scenaVisina, pen);
        }

        xOffset += trajanje * skala;
        y += redVisina;
    }

    ui->graphicsView->setSceneRect(scena->itemsBoundingRect());
}
