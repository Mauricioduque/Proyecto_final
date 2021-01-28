#include "inicio.h"

#include "inicio.h"
#include <QMessageBox>

Inicio::Inicio(View *view, QWidget *parent) : QGraphicsScene(parent){

    viewer = view;
    viewer->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    scroll = new QScrollBar;
    scroll = viewer->horizontalScrollBar();


    this->setFocus();
    this->setSceneRect(0,0,1280,720);
    view->sceneSet(this);


    //Push Button for developer login
    Unjugador = new QPushButton(viewer);
    Unjugador->setText("Un jugador");
    Unjugador->setObjectName(QString("Un jugador"));
    Unjugador->setToolTip("Login as a guest");
    Unjugador->setGeometry(QRect(400, 535, 100, 32));
    connect(Unjugador, SIGNAL(clicked()), this, SLOT(unjugadorLogin()));

    //Push Button for developer login
    multijugador = new QPushButton(viewer);
    multijugador->setText("Multijugador");
    multijugador->setObjectName(QString("Multijugador"));
    multijugador->setToolTip("Login as a guest");
    multijugador->setGeometry(QRect(540, 535, 100, 32));
    connect(multijugador, SIGNAL(clicked()), this, SLOT(multijugadorLogin()));

}


void Inicio::multijugadorLogin()
{
     multijugador->close();
     Unjugador->close();
     scene = new PrimerMundo(false,scroll,this);
     viewer->sceneSet(scene);

}

void Inicio::unjugadorLogin()
{
    Unjugador->close();
    multijugador->close();
    scene = new PrimerMundo(true,scroll,this);
    viewer->sceneSet(scene);
}
