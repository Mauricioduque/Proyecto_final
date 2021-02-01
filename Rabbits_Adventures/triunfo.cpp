/*
 Proyecto: Rabbit's Adventures

 Creado por: Laura Isabel Vidal - Mauricio Duque

 Informática II
 Facultad de Ingeniería
 Departamento de Electrónica y Telecomunicaciones
 Universidad de Antioquia

 Clase Triunfo: ventana gráfica que se ejecuta luego de obtener la victoria
 (se colisiona con la zanahoria dorada)posee los botones de volver
 a inciar el juego o cerrarlo

 */

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
