#ifndef DIALOGBRISANJEID_H
#define DIALOGBRISANJEID_H

#include <QDialog>

namespace Ui {
class DialogBrisanjeID;
}

class DialogBrisanjeID : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBrisanjeID(QWidget *parent = 0);
    ~DialogBrisanjeID();

private:
    Ui::DialogBrisanjeID *ui;

private slots:
    void obrisiKorisnika();

};

#endif // DIALOGBRISANJEID_H
