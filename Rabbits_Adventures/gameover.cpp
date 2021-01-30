/*
 Proyecto: Rabbit's Adventures

 Creado por: Laura Isabel Vidal - Mauricio Duque

 Informática II
 Facultad de Ingeniería
 Departamento de Electrónica y Telecomunicaciones
 Universidad de Antioquia

 Clase Game over: ventana ue despliega el mensaje de que ha perdido
 y presenta la opción de reiniciar el juego o cerrarlo

 */

#include "gameover.h"
#include "ui_gameover.h"

GameOver::GameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);
}

GameOver::~GameOver()
{
    delete ui;
}

void GameOver::on_iniciar_clicked()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void GameOver::on_pushButton_2_clicked()
{
    qApp->quit();
}
