/*
 Proyecto: Rabbit's Adventures

 Creado por: Laura Isabel Vidal - Mauricio Duque

 Informática II
 Facultad de Ingeniería
 Departamento de Electrónica y Telecomunicaciones
 Universidad de Antioquia

 Clase instructions: despliega una ventana que permite leer la instrucciones del juego

 */


#include "instructions.h"
#include "ui_instructions.h"

instructions::instructions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::instructions)
{
    ui->setupUi(this);
}

instructions::~instructions()
{
    delete ui;
}
