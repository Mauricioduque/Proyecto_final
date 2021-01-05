#include "primermundo.h"

PrimerMundo::PrimerMundo(QObject *parent):QGraphicsScene(0,0,8000,720,parent)
  , anchoEscena(6600)
  , personaje(nullptr)
  , salto(true)
  , background(nullptr)
  , velocidad(50)

{

    //inicializamos timer
    timerSprite = new QTimer(this);
    connect(timerSprite, SIGNAL(timeout()), this, SLOT(siguienteSprite()));

    timerEscena = new QTimer(this);
    connect(timerEscena, SIGNAL(timeout()), this, SLOT(correrEscena()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualizar()));

    m_jumpAnimation->setTargetObject(this);
    m_jumpAnimation->setPropertyName("jumpFactor");
    m_jumpAnimation->setStartValue(0);
    m_jumpAnimation->setKeyValueAt(0.5, 1);
    m_jumpAnimation->setEndValue(0);
    m_jumpAnimation->setDuration(800);
    m_jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);

    connect(this, &PrimerMundo::jumpFactorChanged, this, &PrimerMundo::jumpPersonaje);
    connect(m_jumpAnimation, &QPropertyAnimation::stateChanged, this, &PrimerMundo::jumpStatusChanged);

    setSceneRect(0,0,1280,720);

    //Agregamos el fondo
    background= new Fondo(QPixmap(":/fondo.jpg"));
    addItem(background);


    //Agregamos personaje
    personaje =  new PPConejo;
    addItem(personaje);

}

void PrimerMundo::iniciarEscenaUno()
{

    //iniciamos los timer
    timerEscena->start(100);
    timer->start(10);

    //Ponemos posicion incial del cielo
    background->setPos(0,0);
    background->show();

    //Agregamos ladrillos
    int posLadrillo[30][3] = {{550,500,1}, {650,500,1}, {750,500,1}, {650,300,1}, {1150,400,2}, {1350,500,2}, {1350,200,6}, {2150,450,1}
                             , {2250,450,1}, {3050,610,4}, {3100,560,3}, {3150,510,2}, {3200,460,1}, {3425,460,1}, {3425,510,2}, {3425,560,3}
                             , {3425,610,4}, {4000,500,1}, {4100,500,3}, {4100,300,1}, {4250,200,6}, {4650,200,1}, {4850,200,1}, {5400,610,7}
                             , {5450,560,6}, {5500,510,5}, {5550,460,4}, {5600,410,3}, {5650,360,2}, {5700,310,1}};
    for (int i = 0; i < 30; i++)
    {
        ladrillosNota.at(i)->setPos(posLadrillo[i][0],posLadrillo[i][1]);
    }

    //Agregamos lechugas
    int posLechugas[24][2] ={{550,450}, {600,450}, {650,450}, {700,450}, {750,450}, {650,250}, {1150,350}, {1200,350}, {1350,150}, {1400,150}
                         , {1450,150}, {1500,150}, {1550,150}, {1600,150}, {2750,500},{2800,500}, {2850,500}, {2900,500}, {2950,500}, {3000,500}, {2950,450}
                         , {2950,550}, {2900,400}, {2900,600}};
    for (int i= 0; i < 24;i++)
    {
        lechuga.at(i)->setPos(posLechugas[i][0], posLechugas[i][1]);
    }


    //Agregamos enemigo Cerdo
    int posCerdo[10] = {800, 1000, 1600, 1800, 2100, 2200, 2300, 2400, 3300, 3700};
    for (int i = 0; i < 10; i++)
    {
        cerdo.at(i)->setPos(posCerdo[i], nivelTierra - cerdo.at(i)->boundingRect().height());
    }

    //Agregamos enemigo Jabali
    int posJabali[10] = {870, 1070, 1670, 1870, 2170, 2270, 2370, 2470, 3370, 3770};
    for (int i = 0; i < 10; i++)
    {
        jabali.at(i)->setPos(posJabali[i], nivelTierra - jabali.at(i)->boundingRect().height());
    }

    personaje->setPos(-1000,-1000);
    minX = personaje->boundingRect().width();
    maxX = anchoEscena - personaje->boundingRect().width() / 2;
    posicionX = minX;

}

void PrimerMundo::agregarEntradaHorizontal(int entrada)
{

    personaje->addDirection(qBound(-1, entrada, 1));
    checkTimer();
}

void PrimerMundo::checkTimer()
{

}

