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
    danger->setPos(5950,360);
    addItem(danger);

    //AgregarPersonaje
    personaje = new PPConejo();
    personaje->setPos(50, nivelTierra - personaje->boundingRect().height() );
    addItem(personaje);

    startTimer( 100 );


    //Agregamos ladrillos
    int posLadrillo[38][3] = {{400,500,2}, {526,400,2}, {650,300,2}, {900,400,1},{1100,400,1},{1240,300,2}, {1366,450,2}, {1600,520,8}, {1740,330,1}, {1920,330,1}
                             , {2100,200,3}, {2300,460,4}, {2800,615,2}, {2800,575,2}, {2800,535,2},{3100,615,2}, {3100,575,2}, {3360,400,1}, {3800,615,2}
                             , {3800,575,2},{3800,535,2}, {4050,350,1}, {4250,200,1}, {4400,615,2}, {4400,575,2}, {4400,535,2}, {4400,495,2}, {4400,455,2}
                             , {4400,415,2}, {4400,375,2}, {4920,480,6}, {5000,300,1},{5100,200,1},{5600,615,2}, {5680,570,2},{5760,525,2},{5840,480,2}, {5920,435,2}};
    for (int i = ladrillosNota.size() - 1; 0 <= i; i--)
    {
        removeItem(ladrillosNota.at(i));
    }
    ladrillosNota.clear();
    for (int i = 0; i < 38; i++)
    {
        ladrillosNota.append(new MurosNota(posLadrillo[i][2]));
        ladrillosNota.last()->setPos(posLadrillo[i][0],posLadrillo[i][1]);
        addItem(ladrillosNota.last());
    }


  //  Agregamos zanahorias
    int posZanahoria[40][2] ={{800,600},{850,600},{900,600},{950,600},{1000,600},{1050,600},{1100,600},{1150,600},{1200,600}, {900,340}
                             ,{1100,340},{1610,460},{1660,460},{1710,460},{1760,460},{1810,460},{1860,460},{1910,460},{1960,460},{2010,460}
                              ,{2060,460},{2100,140},{2150,140},{2200,140},{2250,140},{2350,600},{2400,600},{2450,600},{3300,600},{3400,600}
                             ,{5110,140},{5010,240},{4950,600},{5000,600},{5050,600},{5100,600},{5150,600},{5200,600},{3300,600},{3350,600}};
    for (int i = zanahoria.size() - 1; 0 <= i; i--)
    {
        removeItem(zanahoria.at(i));
    }
    zanahoria.clear();

    for (int i= 0; i < 40;i++)
    {
        zanahoria.append(new Zanahoria());
        zanahoria.last()->setPos(posZanahoria[i][0], posZanahoria[i][1]);
        addItem(zanahoria.last());

    }


   // Agregamos lechugas
//    int posLechugas[8][2] = {{400,300},{900,70},{1000,300},{1300,290},{1500,160},{1600,160},{1660,160},{1900,160}};
//    for (int i = lechuga.size() - 1; 0 <= i; i--)
//    {
//        removeItem(lechuga.at(i));
//    }
//    lechuga.clear();
//    for (int i = 0; i < 8; i++)
//    {
//        lechuga.append(new Lechuga());
//        lechuga.last()->setPos(posLechugas[i][0], posLechugas[i][1]);
//        addItem(lechuga.last());
//    }

    // Agregamos Piñas
//     int posPinas[9] = {200,400,1500,1700,1900,2100,2300,3700,3900};
//     for (int i = pina.size() - 1; 0 <= i; i--)
//     {
//         removeItem(pina.at(i));
//     }
//     pina.clear();
//     for (int i = 0; i < 9; i++)
//     {
//         pina.append(new Pina());
//         pina.last()->setPos(posPinas[i], nivelTierra - pina.last()->boundingRect().height());
//         addItem(pina.last());
//     }



//    //Agregamos enemigo jabali
//     jabali1 = new JabaliEnemigo();
//     jabali1->setPos(100, nivelTierra-90);
//     addItem(jabali1);

     //Agregamos los cerdos enemigos
      cerdo1 = new CerdoEnemigo(800,1200);
      cerdo1->setPos(1200, nivelTierra-150);
      addItem(cerdo1);

      cerdo2 = new CerdoEnemigo(1600,1900);
      cerdo2->setPos(1900, nivelTierra-280);
      addItem(cerdo2);

      cerdo3 = new CerdoEnemigo(2100,2400);
      cerdo3->setPos(2400, nivelTierra-150);
      addItem(cerdo3);

      cerdo4 = new CerdoEnemigo(3250,3500);
      cerdo4->setPos(3500, nivelTierra-150);
      addItem(cerdo4);

      cerdo5 = new CerdoEnemigo(3950,4100);
      cerdo5->setPos(4100, nivelTierra-150);
      addItem(cerdo5);

      cerdo6 = new CerdoEnemigo(4900,5300);
      cerdo6->setPos(5300, nivelTierra-150);
      addItem(cerdo6);

      cerdo7 = new CerdoEnemigo(4900,5100);
      cerdo7->setPos(5100, nivelTierra-320);
      addItem(cerdo7);





}

void PrimerMundo::correrEscena(QTimerEvent *)
{

//    for (int i = 0;i < zanahoria.size(); i++)
//    {
//        zanahoria.at(i)->nextSprite();
//    }

//    for (int i = 0;i < cerdo.size(); i++)
//    {
//        cerdo.at(i)->nextSprite();
//    }
//    for (int i = 0;i < jabali.size(); i++)
//    {
//        jabali.at(i)->nextSprite();
//    }

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
                    personaje->setPos(w->pos().x() + personaje->boundingRect().width()+63,personaje->pos().y());
                }
            }
        }
     }
}

PrimerMundo::~PrimerMundo()
{
    delete personaje;
    delete ground;
    delete danger;
    delete background;
    delete cerdo1;
    delete jabali1;
    lechuga.clear();
    zanahoria.clear();
    ladrillosNota.clear();
    jabali.clear();
    cerdo.clear();
}
