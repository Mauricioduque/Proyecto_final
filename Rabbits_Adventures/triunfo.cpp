#include "triunfo.h"
#include "ui_triunfo.h"

Triunfo::Triunfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Triunfo)
{
    ui->setupUi(this);
}

Triunfo::~Triunfo()
{
    delete ui;
}


void Triunfo::on_iniciar_clicked()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void Triunfo::on_pushButton_2_clicked()
{
    qApp->quit();
}
