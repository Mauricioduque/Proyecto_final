#include "mainwindow.h"
#include <iostream>


#include "mainwindow.h"
#include <iostream>


MainWindow::MainWindow(){

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




