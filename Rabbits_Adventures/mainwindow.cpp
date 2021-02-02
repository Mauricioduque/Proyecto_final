/*
 Proyecto: Rabbit's Adventures

 Creado por: Laura Isabel Vidal - Mauricio Duque

 Informática II
 Facultad de Ingeniería
 Departamento de Electrónica y Telecomunicaciones
 Universidad de Antioquia

 Clase Mainwindow: ventana principal desde donde se adminsitra el inicio del juego,
 una vez ejecutado, permite desplegar los menus de about e instructions.

 */


#include "mainwindow.h"
#include <iostream>


MainWindow::MainWindow()
{

    createScene();
    setCentralWidget(view);
    setWindowTitle("Rabbits Adventures");
}


void MainWindow::createScene(){

    view = new View;
    title = new Inicio(view);
}

void MainWindow::setSize(){

    this->setFixedSize(1280,740);
    this->move(0, 0);
}









