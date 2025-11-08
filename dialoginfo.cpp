#include "dialoginfo.h"
#include "ui_dialoginfo.h"

DialogInfo::DialogInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInfo)
{
    ui->setupUi(this);
    this->setFixedSize(600, 480);  // početna veličina, ali može se mijenjati
    this->setWindowTitle("Info");
}

DialogInfo::~DialogInfo()
{
    delete ui;
}
