#include "primermundo.h"

PrimerMundo::PrimerMundo(QScrollBar *s,QObject *parent):QGraphicsScene(0,0,8000,720,parent)
  , personaje(nullptr)
  , background(nullptr)
  , m_jumpAnimation(new QPropertyAnimation(this))
  , scroll(s)
  , lechuga()
  , ladrillosNota()


{

    //inicializamos timer
    timerSprite = new QTimer(this);
    connect(timerSprite, SIGNAL(timeout()), this, SLOT(siguienteSprite()));

    timerEscena = new QTimer(this);
    connect(timerEscena, SIGNAL(timeout()), this, SLOT(correrEscena()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moverPersonaje()));

    mFallTimer.setInterval(20);
    connect(&mFallTimer, &QTimer::timeout, this, &PrimerMundo::fallPersonaje);


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


qreal PrimerMundo::jumpFactor() const{

    return m_jumpFactor;
}
void PrimerMundo::setJumpFactor(const qreal &jumpFactor)
{
        if (m_jumpFactor == jumpFactor) return;

        m_jumpFactor = jumpFactor;
        emit jumpFactorChanged(m_jumpFactor);
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

    if (0 == personaje->direction()){
        personaje->stand();
        timerSprite->stop();
    }
    else if (!timerSprite->isActive()){
        timerSprite->start();
        personaje->walk();
    }

}

void PrimerMundo::correrEscena()
{

    for (int i = 0;i < zanahoria.size(); i++)
    {
        zanahoria.at(i)->nextSprite();
    }

    for (int i = 0;i < cerdo.size(); i++)
    {
        cerdo.at(i)->nextSprite();
    }
    for (int i = 0;i < jabali.size(); i++)
    {
        jabali.at(i)->nextSprite();
    }

    //mueve los cerdos
    for (int i = 0;i < cerdo.size(); i++)
    {
        cerdo.at(i)->setX(cerdo.at(i)->pos().x() + cerdo.at(i)->getDireccion() * (-7));
    }

    //mueve los jabalis
    for (int i = 0;i < jabali.size(); i++)
    {
        jabali.at(i)->setX(jabali.at(i)->pos().x() + jabali.at(i)->getDireccion() * (-7));
    }

}

void PrimerMundo::jumpPersonaje()
{
    if (QAbstractAnimation::Stopped == m_jumpAnimation->state()){
       personaje->stand();
       return;
    }
    QGraphicsItem *item = collidingPlatforms();
    if(item){
        if(personaje->isTouchingHead(item)){

            m_jumpAnimation->stop();

            if(m_platform){
                personaje->setPos(personaje->pos().x(), m_platform->pos().y() - personaje->boundingRect().height());
                return;
            }
            if(!m_platform){
                personaje->setPos(personaje->pos().x(), nivelTierra - personaje->boundingRect().height());
                return;
            }
        }
        else{
            if(manejoColisiones()){
                return;
            }
        }
    }

    if(mFallTimer.isActive()){
        return;
    }
    qreal y = (nivelTierra - personaje->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
    if(m_platform){
        y = (m_platform->pos().y() - personaje->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
        if(!(m_platform && personaje->isTouchingPlatform(m_platform)) && m_jumpFactor < 0.1 ) {
            if((personaje->pos().x() < m_platform->pos().x()) || (personaje->pos().x() > m_platform->pos().x() + m_platform->boundingRect().width())){
                if(!m_platform){
                    m_platform = 0;
                }
                if(personaje->pos().y() <nivelTierra){
                    personaje->fall();
                    mFallTimer.start();
                    return;
                }
            }
        }
    }
    personaje->setPos(personaje->pos().x(), y);




}

void PrimerMundo::jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    if(newState == QAbstractAnimation::Stopped && oldState == QAbstractAnimation::Running){
    }
}

void PrimerMundo::moverPersonaje()
{

    int direction = personaje->direction();
    int dx=direction *velocidad;
    personaje->nextFrame();
    if (0 == direction){
     return;
        if(!(m_platform && personaje->isTouchingPlatform(m_platform))&& m_jumpAnimation->state() == QAbstractAnimation::Stopped){
            if(m_platform){
                personaje->fall();
                //mFallTimer.start();
            }
        }
    }

    qreal newX = qBound(minX, posicionX + dx, maxX);
    if (newX == posicionX)
    {
        return;
    }
    posicionX = newX;

    const int longituCambio = 300;
    int derechaLongitudCambio = width() - longituCambio;

    const int posicionVisibleJugador = posicionX - desplazamientoMundo;
    const int newMundoDerecha = posicionVisibleJugador - derechaLongitudCambio;
    if (newMundoDerecha > 0)
    {
        desplazamientoMundo += newMundoDerecha;
    }
    const int newMundoIzquierda = longituCambio - posicionVisibleJugador;
    if (newMundoIzquierda > 0)
    {
        desplazamientoMundo -= newMundoIzquierda;
    }

    const int maxDesplazamientoMundo = anchoEscena - qRound(width());
    desplazamientoMundo = qBound(0, desplazamientoMundo, maxDesplazamientoMundo);

    //mueve los ladrillos
    for (int i = 0;i < ladrillosNota.size(); i++)
    {
        ladrillosNota.at(i)->setX(-dx + ladrillosNota.at(i)->pos().x());
    }

    //mueve las monedas
    for (int i = 0;i < lechuga.size(); i++)
    {
        lechuga.at(i)->setX(-dx + lechuga.at(i)->pos().x());
    }

    //mueve las zanahorias
    for (int i = 0;i < zanahoria.size(); i++)
    {
        zanahoria.at(i)->setX(-dx + zanahoria.at(i)->pos().x());
    }

    //mover cerdos
    for (int i = 0;i < cerdo.size(); i++)
    {
        cerdo.at(i)->setX(-dx + cerdo.at(i)->pos().x());
    }

    //mover jabali
    for (int i = 0;i < jabali.size(); i++)
    {
        jabali.at(i)->setX(-dx + jabali.at(i)->pos().x());
    }
}

void PrimerMundo::fallPersonaje()
{
    QGraphicsItem *item = collidingPlatforms();
    personaje->setPos(personaje->pos().x(), personaje->pos().y() +30);
    if(item && manejoColisiones()){
       mFallTimer.stop();
       personaje->walk();
    }
    else if(personaje->pos().y() + personaje->boundingRect().height() >= nivelTierra){
            personaje->setPos(personaje->pos().x(), nivelTierra - personaje->boundingRect().height());
            mFallTimer.stop();
            personaje->walk();
            m_platform = 0;
        }

}

bool PrimerMundo::manejoColisiones()
{
    QGraphicsItem *platform= collidingPlatforms();
    if(platform) {
        QPointF platformPos = platform->pos();
        if(personaje->isTouchingFoot(platform)){
            personaje->setPos(personaje->pos().x(), platformPos.y() - personaje->boundingRect().height());
            m_platform = platform;
            m_jumpAnimation->stop();
            return true;
        }
    }
    else{
        m_platform = 0;
    }
    return false;
}

QGraphicsItem *PrimerMundo::collidingPlatforms()
{
        QList<QGraphicsItem*> items =  collidingItems(personaje);
        foreach(QGraphicsItem *item, items){
            if(MurosNota *brickplatform = qgraphicsitem_cast<MurosNota *>(item)){
                return brickplatform;
           }
        }
        return 0;
}

void PrimerMundo::keyPressEvent(QKeyEvent *event)
{

    if (event->isAutoRepeat())
        return;

    switch (event->key()){
        case Qt::Key_Right:
                personaje->addDirection(1);
                personaje->addStandingDirection(1);
                checkTimer();
                break;

        case Qt::Key_Left:
                personaje->addDirection(-1);
                personaje->addStandingDirection(-1);
                checkTimer();
                break;

        case Qt::Key_Space:
                if(mFallTimer.isActive()){
                    return;}
                else{
                    if (QAbstractAnimation::Stopped == m_jumpAnimation->state()){
                        m_jumpAnimation->start();
                    }
                }
                break;

        default:
            break;
    }
}

void PrimerMundo::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key())
    {
        case Qt::Key_Right:
            personaje->addDirection(-1);
            personaje->addStandingDirection(1);
            checkTimer();
            break;

        case Qt::Key_Left:
            personaje->addDirection(1);
            personaje->addStandingDirection(-1);
            checkTimer();
            break;

        default:
            break;
    }
}

PrimerMundo::~PrimerMundo()
{
    delete personaje;
    delete background;
    lechuga.clear();
    zanahoria.clear();
    ladrillosNota.clear();
    jabali.clear();
    cerdo.clear();
}
