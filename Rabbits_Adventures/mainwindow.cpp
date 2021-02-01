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
    createActions();
    createMenus();
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
    int x = ((screenGeometry.width() - this->width()) / 2);
    int y = ((screenGeometry.height() - this->height()) / 2);
    this->move(x, y);
}

void MainWindow::createActions()
{
    aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));
    InstructionAction= new QAction(tr("&Intructions"),this);
    connect(InstructionAction, SIGNAL(triggered()), this, SLOT(showinstruction()));
}

void MainWindow::showAbout()
{
    aboutt = new about;
    aboutt->exec();
}

void MainWindow::createMenus()
{

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->setToolTip("Developer Info");
    helpMenu->addAction(aboutAction);

    instruction = menuBar()->addMenu(tr("&Instructions"));
    instruction->setToolTip("Intrucciones del juego");
    instruction->addAction(InstructionAction);
}

void MainWindow::showinstruction()
{
    Instruction = new instructions;
    Instruction->exec();
}



