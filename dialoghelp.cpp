#include "dialoghelp.h"
#include "ui_dialoghelp.h"

DialogHelp::DialogHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHelp)
{
    ui->setupUi(this);
    this->setFixedSize(600, 480);  // početna veličina, ali može se mijenjati
    this->setWindowTitle("Help");
}

DialogHelp::~DialogHelp()
{
    delete ui;
}
