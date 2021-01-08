#include "primermundo.h"
#include <iostream>
PrimerMundo::PrimerMundo(QScrollBar *s,QObject *parent):QGraphicsScene(0,0,8000,720,parent)
  , m_jumpAnimation(new QPropertyAnimation(this))
  , m_platform()
  , scroll(s)



{
    iniciarEscenaUno();

    //inicializamos timer

    timer.setInterval(20);
    connect(&timer, &QTimer::timeout, this, &PrimerMundo::moverPersonaje);

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

    jumping = false;
    falling = false;

    personaje->addStandingDirection(1);

}

void PrimerMundo::keyPressEvent(QKeyEvent *event){
    if (event->isAutoRepeat())
    return;

    switch (event->key()){
        case Qt::Key_Right:
        {
            personaje->addDirection(1);
            personaje->addStandingDirection(1);
            checkTimer();
            break;
        }


        case Qt::Key_Left:
        {
            personaje->addDirection(-1);
            personaje->addStandingDirection(-1);
            checkTimer();
            break;
        }

        case Qt::Key_Space:
        {
            if(mFallTimer.isActive()){
                return;
            }else{
                if (QAbstractAnimation::Stopped == m_jumpAnimation->state()){
                    m_jumpAnimation->start();

                }
            }
            break;
        }

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
            {
            personaje->addDirection(-1);
            personaje->addStandingDirection(1);
            checkTimer();
            break;
            }

        case Qt::Key_Left:
            {
            personaje->addDirection(1);
            personaje->addStandingDirection(-1);
            checkTimer();
            break;
            }

        default:
            break;
    }
}

void PrimerMundo::moverPersonaje()
{
    checkColisionMuros();

    if(personaje->isFalling()){
        return;
    }

    personaje->nextFrame();

    int direction = personaje->direction();
    if (0 == direction) return;

    if(!(m_platform && personaje->isTouchingPlatform(m_platform))&& m_jumpAnimation->state() == QAbstractAnimation::Stopped){
        if(m_platform){
            personaje->fall();
            mFallTimer.start();
        }
    }

    const int dx = direction * velocidad;
    if (direction > 0){

        if(personaje->pos().x()==7956){
            return;
        }
        personaje->moveBy(dx, 0);
        int diff = personaje->pos().x() - scroll->value();

        if(diff > 800){

            if(scroll->value() > 6720){
                qDebug()<<"6720";
                return;
            }
            scroll->setValue(dx + scroll->value());
            background->setPos(dx + background->pos().x(), background->y());
        }
    }

    if (direction < 0){

        if(personaje->pos().x()<0){
            return;
        }

        personaje->moveBy(dx, 0);
        int diff = personaje->pos().x() - scroll->value();

        if(diff < 600){

            if(background->pos().x() == 0){
                return;
            }

            scroll->setValue(dx + scroll->value());
            background->setPos(dx + background->pos().x(), background->y());
        }
    }

}

void PrimerMundo::jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    if(newState == QAbstractAnimation::Stopped && oldState == QAbstractAnimation::Running){
    }
}

void PrimerMundo::fallPersonaje()
{

    personaje->setPos(personaje->pos().x(), personaje->pos().y() +30);
    QGraphicsItem *item = collidingPlatforms();
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

void PrimerMundo::iniciarEscenaUno()
{
    setSceneRect(0,0,8000,720);

    nivelTierra = 660;

    //Ponemos posicion incial del cielo
    background=new Fondo(QPixmap(":/fondo.png"));
    background->setPos(0,0);
    addItem(background);


    //add ground
    ground = new Fondo(QPixmap(":/ground.png"));
    ground->setPos(0,nivelTierra);
    addItem(ground);

    //add señal
    danger = new Fondo(QPixmap(":/danger.png"));
    danger->setPos(5650,335);
    addItem(danger);

    //AgregarPersonaje
    personaje = new PPConejo();
    personaje->setPos(50, nivelTierra - personaje->boundingRect().height() );
    addItem(personaje);

    zanahoria1 = new Zanahoria();
    zanahoria1->setPos(50, nivelTierra - zanahoria1->boundingRect().height()-200);
    addItem(zanahoria1);
    startTimer( 100 );



    //Agregamos ladrillos
    int posLadrillo[33][3] = {{550,500,2}, {650,400,2}, {750,300,2}, {1050,300,2}, {1150,400,2}, {1250,500,2}, {1550,200,3}, {1350,330,1}
                             , {1900,200,3}, {1700,440,4}, {2250,440,1}, {2850,510,2}, {2950,460,1},{2750,560,3}, {3200,460,1}, {3250,510,2}, {3300,560,3}
                             , {3350,610,4},{2650,610,4}, {4000,500,1}, {4100,500,3}, {4100,300,1}, {4250,200,6}, {4650,200,1}, {4850,200,1}, {5400,610,7}
                             , {5450,560,6}, {5500,510,5}, {5550,460,4}, {5600,410,3}, {5650,360,2}, {5700,310,1},{5800,260,1}};
    for (int i = ladrillosNota.size() - 1; 0 <= i; i--)
    {
        removeItem(ladrillosNota.at(i));
    }
    ladrillosNota.clear();
    for (int i = 0; i < 30; i++)
    {
        ladrillosNota.append(new MurosNota(posLadrillo[i][2]));
        ladrillosNota.last()->setPos(posLadrillo[i][0],posLadrillo[i][1]);
        addItem(ladrillosNota.last());
    }


  //  Agregamos zanahorias
    int posZanahoria[30][2] ={{820,300},{910,70},{1030,300},{1350,290},{1560,160},{1610,160},{1660,160},{1910,160},{1960,160}, {2010,160}
                             ,{2250,400},{2950,420},{3060,280},{3200,420},{4000,460},{4130,460},{4180,460},{4230,460},{4100,260},{4280,160}
                              ,{4330,160},{4380,160},{4430,160},{4480,160},{4530,160},{4580,160},{4650,160},{4850,160}};
    for (int i = zanahoria.size() - 1; 0 <= i; i--)
    {
        removeItem(zanahoria.at(i));
    }
    zanahoria.clear();

    for (int i= 0; i < 30;i++)
    {
        zanahoria.append(new Zanahoria());
        zanahoria.last()->setPos(posZanahoria[i][0], posZanahoria[i][1]);
        addItem(zanahoria.last());

    }


   // Agregamos lechugas
    int posLechugas[8] = {300,1600,1800,2000,2200,2400,2600,3800};
    for (int i = lechuga.size() - 1; 0 <= i; i--)
    {
        removeItem(lechuga.at(i));
    }
    lechuga.clear();
    for (int i = 0; i < 8; i++)
    {
        lechuga.append(new Lechuga());
        lechuga.last()->setPos(posLechugas[i], nivelTierra - lechuga.last()->boundingRect().height());
        addItem(lechuga.last());
    }

    // Agregamos Piñas
      int posPinas[9] = {200,400,1500,1700,1900,2100,2300,3700,3900};
     for (int i = pina.size() - 1; 0 <= i; i--)
     {
         removeItem(pina.at(i));
     }
     pina.clear();
     for (int i = 0; i < 9; i++)
     {
         pina.append(new Pina());
         pina.last()->setPos(posPinas[i], nivelTierra - pina.last()->boundingRect().height());
         addItem(pina.last());
     }



    //Agregamos enemigo jabali
    int posJabali[10] = {800, 1000, 1600, 1800, 2100, 2200, 2300, 2400, 3300, 3700};
    for (int i = jabali.size() - 1 ; 0 <= i; i--)
    {
        removeItem(jabali.at(i));
    }
    jabali.clear();
    for (int i = 0; i < 10; i++)
    {
        jabali.append(new JabaliEnemigo());
        jabali.last()->setPos(posJabali[i], nivelTierra - jabali.last()->boundingRect().height());
        addItem(jabali.last());
    }

    //Agregamos enemigo cerdo
    int posCerdo[10] = {700, 900, 1500, 1700, 2100, 2150, 2350, 2450, 3350, 3750};
    for (int i = cerdo.size() - 1 ; 0 <= i; i--)
    {
        removeItem(cerdo.at(i));
    }
    cerdo.clear();
    for (int i = 0; i < 10; i++)
    {
        cerdo.append(new CerdoEnemigo());
        cerdo.last()->setPos(posCerdo[i], nivelTierra - cerdo.last()->boundingRect().height());
        addItem(cerdo.last());
    }


}

void PrimerMundo::correrEscena(QTimerEvent *)
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

//    //mueve los cerdos
//    for (int i = 0;i < cerdo.size(); i++)
//    {
//        cerdo.at(i)->setX(cerdo.at(i)->pos().x() + cerdo.at(i)->getDireccion() * (-7));
//    }

//    //mueve los jabalis
//    for (int i = 0;i < jabali.size(); i++)
//    {
//        jabali.at(i)->setX(jabali.at(i)->pos().x() + jabali.at(i)->getDireccion() * (-7));
//    }

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

void PrimerMundo::checkTimer()
{

    if (0 == personaje->direction()){
        personaje->stand();
        timer.stop();
    }
    else if (!timer.isActive()){
        timer.start();
        personaje->walk();
    }

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

bool PrimerMundo::manejoColisiones()
{
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
    return 0;
}

void PrimerMundo::checkColisionMuros()
{
    QList<QGraphicsItem*> items = collidingItems(personaje);
    foreach (QGraphicsItem* item, items) {

        MurosNota * w = qgraphicsitem_cast<MurosNota *>(item);
        if(w){
            if(w->pos().x()){
                if(personaje->pos().x() < w->pos().x())
                    personaje->setPos(w->pos().x()- personaje->boundingRect().width(),personaje->pos().y());
                if(personaje->pos().x() > w->pos().x()){
                    personaje->setPos(w->pos().x() + personaje->boundingRect().width()+96,personaje->pos().y());
                }
            }
        }
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