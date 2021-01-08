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
    developerButton = new QPushButton(viewer);
    developerButton->setText("Guest Login");
    developerButton->setObjectName(QString("developerButton"));
    developerButton->setToolTip("Login as a guest");
    developerButton->setGeometry(QRect(540, 535, 100, 32));
    connect(developerButton, SIGNAL(clicked()), this, SLOT(developerLogin()));

}


void Inicio::developerLogin()
 {
     developerButton->close();
     scene = new PrimerMundo(scroll,this);
     viewer->sceneSet(scene);

 }
