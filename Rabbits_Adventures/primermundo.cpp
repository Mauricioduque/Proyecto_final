#include "primermundo.h"
#include <iostream>
PrimerMundo::PrimerMundo( QScrollBar *s,QObject *parent):QGraphicsScene(0,0,8000,720,parent)
  , m_jumpAnimation(new QPropertyAnimation(this))
  , m_platform()
  , scroll(s)

{


    Vida=5;
    iniciarEscenaUno();

    //inicializamos timer
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(moverPersonaje()));
    timer->setInterval(20);

    mFallTimer = new QTimer(this);
    connect(mFallTimer,SIGNAL(timeout()),this,SLOT(fallPersonaje()));
    mFallTimer->setInterval(20);

    m_jumpAnimation->setTargetObject(this);
    m_jumpAnimation->setPropertyName("jumpFactor");
    m_jumpAnimation->setStartValue(0);
    m_jumpAnimation->setKeyValueAt(0.5, 1);
    m_jumpAnimation->setEndValue(0);
    m_jumpAnimation->setDuration(800);
    m_jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);

    connect(this, &PrimerMundo::jumpFactorChanged, this, &PrimerMundo::jumpPersonaje);
    connect(m_jumpAnimation, &QPropertyAnimation::stateChanged, this, &PrimerMundo::jumpStatusChanged);

    personaje->addStandingDirection(1);

}


void PrimerMundo::keyPressEvent(QKeyEvent *event){
    if (event->isAutoRepeat())
    return;

    switch (event->key()){
        case Qt::Key_Right:
        {
            reinicio=true;
            personaje->addDirection(1);
            personaje->addStandingDirection(1);
            checkTimer();
            break;
        }


        case Qt::Key_Left:
        {
            reinicio=false;
            personaje->addDirection(-1);
            personaje->addStandingDirection(-1);
            checkTimer();
            break;
        }

        case Qt::Key_Space:
        {
            if(mFallTimer->isActive()){
                return;
            }
            else{
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
                reinicio=true;
                personaje->addDirection(-1);
                personaje->addStandingDirection(1);
                checkTimer();
                break;
            }

        case Qt::Key_Left:
            {
            reinicio=false;
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
    checkColZanahoria();
    checkColPina();

    if(personaje->isFalling()){
        return;
    }

    personaje->nextFrame();


    direction = personaje->direction();

    if (0 == direction) return;

    if(!(m_platform && personaje->isTouchingPlatform(m_platform))&& m_jumpAnimation->state() == QAbstractAnimation::Stopped){
        if(m_platform){
            personaje->fall();
            mFallTimer->start();
        }
    }

    const int dx = direction * velocidad;
    if (direction > 0){

        if(personaje->pos().x()==8100){
            return;
        }
        personaje->moveBy(dx, 0);
        int diff = personaje->pos().x() - scroll->value();

        if(diff > 850){


            scroll->setValue(dx + scroll->value());
            background->setPos(dx + background->pos().x(), background->y());
            Puntaje->setPos(dx + Puntaje->pos().x(), Puntaje->y());
            LogoPuntaje->setPos(dx + LogoPuntaje->pos().x(), LogoPuntaje->y());
            vidas_->setPos(dx + vidas_->pos().x(), vidas_->y());
            LogoVida->setPos(dx + LogoVida->pos().x(), LogoVida->y());
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
            Puntaje->setPos(dx + Puntaje->pos().x(), Puntaje->y());
            LogoPuntaje->setPos(dx + LogoPuntaje->pos().x(), LogoPuntaje->y());
            vidas_->setPos(dx + vidas_->pos().x(), vidas_->y());
            LogoVida->setPos(dx + LogoVida->pos().x(), LogoVida->y());

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
       mFallTimer->stop();
       personaje->walk();
    }
    else if(personaje->pos().y() + personaje->boundingRect().height() >= nivelTierra){
            personaje->setPos(personaje->pos().x(), nivelTierra - personaje->boundingRect().height());
            mFallTimer->stop();
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

    if(mFallTimer->isActive()){
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
                    mFallTimer->start();
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

    //se agrega puntaje
    LogoPuntaje = new Fondo(QPixmap(":/scoretext.png"));
    LogoPuntaje->setPos(870, nivelTierra -647 );
    addItem(LogoPuntaje);
    Puntaje = new puntaje();
    Puntaje->setPos(980, nivelTierra - Puntaje->boundingRect().height()-610);
    addItem(Puntaje);

    //Se agrega vidas
    LogoVida = new Fondo(QPixmap(":/vida.png"));
    LogoVida->setPos(200, nivelTierra - 647 );
    addItem(LogoVida);

    vidas_ = new vidas(Vida);
    Vida--;
    vidas_->setPos(330, nivelTierra - vidas_->boundingRect().height()-610);
    addItem(vidas_);


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
    int posLadrillo[41][3] = {{150,200,2}, {850,200,2}, {950,400,1},{1100,400,1},{1240,300,2}, {1366,450,2}, {1600,520,8}, {1740,330,1}, {1920,330,1}
                             , {2100,200,3}, {2300,460,4}, {2800,615,2}, {2800,575,2}, {2800,535,2},{3100,615,2}, {3100,575,2}, {3360,400,1}, {3800,615,2}
                             , {3800,575,2},{3800,535,2}, {4050,350,1}, {4250,200,1}, {4400,615,2}, {4400,575,2}, {4400,535,2}, {4400,495,2}, {4400,455,2}
                             , {4400,415,2}, {4400,375,2}, {4920,480,6}, {5000,300,1},{5100,200,1},{5600,615,2}, {5680,570,2},{5760,525,2},{5840,480,2}, {5920,435,2}
                             , {6500,410,1},{7000,410,1},{7500,410,1}};
    for (int i = ladrillosNota.size() - 1; 0 <= i; i--)
    {
        removeItem(ladrillosNota.at(i));
    }
    ladrillosNota.clear();
    for (int i = 0; i < 41; i++)
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


     //Agregamos los cerdos enemigos
      cerdo1 = new CerdoEnemigo(800,1200);
      cerdo1->setPos(1200, nivelTierra-150);
      addItem(cerdo1);
      connect(this->cerdo1, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      cerdo2 = new CerdoEnemigo(1600,1900);
      cerdo2->setPos(1900, nivelTierra-280);
      addItem(cerdo2);
      connect(this->cerdo2, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      cerdo3 = new CerdoEnemigo(2100,2400);
      cerdo3->setPos(2400, nivelTierra-150);
      addItem(cerdo3);
      connect(this->cerdo3, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      cerdo4 = new CerdoEnemigo(3250,3500);
      cerdo4->setPos(3500, nivelTierra-150);
      addItem(cerdo4);
      connect(this->cerdo4, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      cerdo5 = new CerdoEnemigo(3950,4100);
      cerdo5->setPos(4100, nivelTierra-150);
      addItem(cerdo5);
      connect(this->cerdo5, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      cerdo6 = new CerdoEnemigo(4900,5300);
      cerdo6->setPos(5300, nivelTierra-150);
      addItem(cerdo6);
      connect(this->cerdo6, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      cerdo7 = new CerdoEnemigo(4900,5100);
      cerdo7->setPos(5100, nivelTierra-320);
      addItem(cerdo7);
      connect(this->cerdo7, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      //Agregamos Águilas enemigas
//        aguila=new Aguila(6000,6400);
//        aguila->setPos(6000,50);
//        addItem(aguila);
//        connect(this->aguila, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

//        aguila2=new Aguila(6600,6900);
//        aguila2->setPos(6600,50);
//        addItem(aguila2);
//        connect(this->aguila2, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

//        aguila3=new Aguila(7200,7750);
//        aguila3->setPos(7200,50);
//        addItem(aguila3);
//        connect(this->aguila3, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));


        //Agrego bandera fin de primer nivel
        flag=new Flag();
        flag->setPos(7500,330);
        //flag->setPos(400,550);
        addItem(flag);
        connect(this->flag, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

           //MUNDO 2:

        fuego = new New(600,300,500,400,5);
        fuego->setPos(600,300);
        addItem(fuego);
        fuego1 = new New(750,300,650,400,-5);
        fuego1->setPos(800,300);
        addItem(fuego1);

        //CAZADOR:
        cazador1 = new Fondo(QPixmap(":/hunterleft.png"));
        cazador1->setPos(150,55);
        addItem(cazador1);
        cazador2 = new Fondo(QPixmap(":/hunterright.png"));
        cazador2->setPos(850,55);
        addItem(cazador2);

        //BALAS:
        bullet1=new Bullet(260,50,-25,true);
        bullet1->setPos(260,135);
        addItem(bullet1);
        connect(this->bullet1, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

        bullet2=new Bullet(800,60,-30,false);
        bullet2->setPos(800,140);
        addItem(bullet2);
        connect(this->bullet2, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));


}

void PrimerMundo::iniciarEscenaDos()
{
    delete personaje;
    delete timer;
    delete mFallTimer;
    delete background;
    delete ground;
    delete danger;
    delete Puntaje;
    delete LogoPuntaje;
    delete LogoVida;
    delete cerdo1;
    delete cerdo2;
    delete cerdo3;
    delete cerdo4;
    delete cerdo5;
    delete cerdo6;
    delete cerdo7;
    delete aguila;
    delete aguila2;
    delete aguila3;


    m_platform=0;
    m_jumpAnimation->stop();
    scroll->setValue(0);

    setSceneRect(0,0,8000,720);
    nivelTierra = 660;

    //Ponemos posicion incial del cielo
    background=new Fondo(QPixmap(":/bosqueNoche.png"));
    background->setPos(0,0);
    addItem(background);


    //add ground
    ground = new Fondo(QPixmap(":/ground.png"));
    ground->setPos(0,nivelTierra);
    addItem(ground);

    //se agrega puntaje
    LogoPuntaje = new Fondo(QPixmap(":/scoretext.png"));
    LogoPuntaje->setPos(870, nivelTierra -647 );
    addItem(LogoPuntaje);
    Puntaje = new puntaje();
    Puntaje->setPos(980, nivelTierra - Puntaje->boundingRect().height()-610);
    addItem(Puntaje);

    //Se agrega vidas
    LogoVida = new Fondo(QPixmap(":/vida.png"));
    LogoVida->setPos(200, nivelTierra - 647 );
    addItem(LogoVida);

    vidas_ = new vidas(Vida);
    Vida--;
    vidas_->setPos(330, nivelTierra - vidas_->boundingRect().height()-610);
    addItem(vidas_);


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
    int posLadrillo[41][3] = {{400,500,2}, {526,400,2}, {650,300,2}, {900,400,1},{1100,400,1},{1240,300,2}, {1366,450,2}, {1600,520,8}, {1740,330,1}, {1920,330,1}
                             , {2100,200,3}, {2300,460,4}, {2800,615,2}, {2800,575,2}, {2800,535,2},{3100,615,2}, {3100,575,2}, {3360,400,1}, {3800,615,2}
                             , {3800,575,2},{3800,535,2}, {4050,350,1}, {4250,200,1}, {4400,615,2}, {4400,575,2}, {4400,535,2}, {4400,495,2}, {4400,455,2}
                             , {4400,415,2}, {4400,375,2}, {4920,480,6}, {5000,300,1},{5100,200,1},{5600,615,2}, {5680,570,2},{5760,525,2},{5840,480,2}, {5920,435,2}
                             , {6500,410,1},{7000,410,1},{7500,410,1}};
    for (int i = ladrillosNota.size() - 1; 0 <= i; i--)
    {
        removeItem(ladrillosNota.at(i));
    }
    ladrillosNota.clear();
    for (int i = 0; i < 41; i++)
    {
        ladrillosNota.append(new MurosNota(posLadrillo[i][2]));
        ladrillosNota.last()->setPos(posLadrillo[i][0],posLadrillo[i][1]);
        addItem(ladrillosNota.last());
    }


  //  Agregamos zanahorias
    int posPina[40][2] ={{700,600},{850,600},{900,600},{950,600},{1000,600},{1050,600},{1100,600},{1150,600},{1200,600}, {900,340}
                             ,{1100,340},{1610,460},{1660,460},{1710,460},{1760,460},{1810,460},{1860,460},{1910,460},{1960,460},{2010,460}
                              ,{2060,460},{2100,140},{2150,140},{2200,140},{2250,140},{2350,600},{2400,600},{2450,600},{3300,600},{3400,600}
                             ,{5110,140},{5010,240},{4950,600},{5000,600},{5050,600},{5100,600},{5150,600},{5200,600},{3300,600},{3350,600}};
    for (int i = pina.size() - 1; 0 <= i; i--)
    {
        removeItem(pina.at(i));
    }
    pina.clear();

    for (int i= 0; i < 40;i++)
    {
        pina.append(new Pina());
        pina.last()->setPos(posPina[i][0], posPina[i][1]);
        addItem(pina.last());

    }


     //Agregamos los cerdos enemigos
      jabali1 = new JabaliEnemigo();
      jabali1->setPos(100, nivelTierra-150);
      addItem(jabali1);


      cerdo2 = new CerdoEnemigo(1600,1900);
      cerdo2->setPos(1900, nivelTierra-280);
      addItem(cerdo2);
      connect(this->cerdo2, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      cerdo3 = new CerdoEnemigo(2100,2400);
      cerdo3->setPos(2400, nivelTierra-150);
      addItem(cerdo3);
      connect(this->cerdo3, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      cerdo4 = new CerdoEnemigo(3250,3500);
      cerdo4->setPos(3500, nivelTierra-150);
      addItem(cerdo4);
      connect(this->cerdo4, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      cerdo5 = new CerdoEnemigo(3950,4100);
      cerdo5->setPos(4100, nivelTierra-150);
      addItem(cerdo5);
      connect(this->cerdo5, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      cerdo6 = new CerdoEnemigo(4900,5300);
      cerdo6->setPos(5300, nivelTierra-150);
      addItem(cerdo6);
      connect(this->cerdo6, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      cerdo7 = new CerdoEnemigo(4900,5100);
      cerdo7->setPos(5100, nivelTierra-320);
      addItem(cerdo7);
      connect(this->cerdo7, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      //Agregamos Águilas enemigas
        aguila=new Aguila(6000,6400);
        aguila->setPos(6000,50);
        addItem(aguila);
        connect(this->aguila, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

        aguila2=new Aguila(6600,6900);
        aguila2->setPos(6600,50);
        addItem(aguila2);
        connect(this->aguila2, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

        aguila3=new Aguila(7200,7750);
        aguila3->setPos(7200,50);
        addItem(aguila3);
        connect(this->aguila3, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));


        //Agrego bandera fin de primer nivel
        flag=new Flag();
        flag->setPos(7500,330);
        addItem(flag);

        timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(moverPersonaje()));
        timer->setInterval(20);
        mFallTimer = new QTimer(this);
        connect(mFallTimer,SIGNAL(timeout()),this,SLOT(fallPersonaje()));
        mFallTimer->setInterval(20);

        personaje->set_m_direction(0);
        personaje->addDirection(1);
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
        timer->stop();
    }
    else if (!timer->isActive()){
        timer->start();
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

void PrimerMundo::checkColZanahoria()
{
    for (int i=0;i<zanahoria.size() ;i++ ) {
         if(personaje->collidesWithItem(zanahoria.at(i))){
            removeItem(zanahoria.at(i));
            Puntaje->incrementar();
            zanahoria=eliminarZanahoria(zanahoria,i);

         }
    }
}

void PrimerMundo::checkColPina()
{
    for (int i=0;i<pina.size() ;i++ ) {
         if(personaje->collidesWithItem(pina.at(i))){
            removeItem(pina.at(i));
            Puntaje->incrementar();
            pina=eliminarPina(pina,i);

         }
    }
}

QList<Pina *> PrimerMundo::eliminarPina(QList<Pina *> pina, int pos)
{
    QList<Pina *> aux;
    for (int i=0;i<pina.size() ;i++ ) {
        if (i!=pos){
            aux.push_back(pina.at(i));
        }
    }
    return aux;

}

QList<Zanahoria *> PrimerMundo::eliminarZanahoria(QList<Zanahoria *> zanahoria, int pos)
{
    QList<Zanahoria *> aux;
    for (int i=0;i<zanahoria.size() ;i++ ) {
        if (i!=pos){
            aux.push_back(zanahoria.at(i));
        }
    }
    return aux;

}

void PrimerMundo::Estado(int n)
{
    int number = n;
    if(number == 0){
       iniciarEscenaDos();
    }
    else if(number == 1){
        if (Vida==0){
            gameOverWindow = new GameOver();
            gameOverWindow->setWindowFlags(((gameOverWindow->windowFlags()|Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
            gameOverWindow->exec();
        }
        else reiniciarEscenaUno();


    }
    else return;
}

void PrimerMundo::reiniciarEscenaUno()
{
    delete personaje;
    delete timer;
    delete mFallTimer;
    delete background;
    delete ground;
    delete danger;
    delete Puntaje;
    delete LogoPuntaje;
    delete LogoVida;
    delete cerdo1;
    delete cerdo2;
    delete cerdo3;
    delete cerdo4;
    delete cerdo5;
    delete cerdo6;
    delete cerdo7;
    delete aguila;
    delete aguila2;
    delete aguila3;
    delete flag;
    delete fuego;
    delete fuego1;
    delete cazador1;
    delete cazador2;
    delete bullet1;
    delete bullet2;
    m_platform=0;
    m_jumpAnimation->stop();
    scroll->setValue(0);
    iniciarEscenaUno();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(moverPersonaje()));
    timer->setInterval(20);
    mFallTimer = new QTimer(this);
    connect(mFallTimer,SIGNAL(timeout()),this,SLOT(fallPersonaje()));
    mFallTimer->setInterval(20);
    if(reinicio){
        personaje->set_m_direction(0);
        personaje->addDirection(1);
    }
    else {

        personaje->set_m_direction(0);
        personaje->addDirection(-1);
    }

}

PrimerMundo::~PrimerMundo()
{
    delete personaje;
    delete ground;
    delete danger;
    delete background;
    delete cerdo1;
    delete cerdo2;
    delete cerdo3;
    delete cerdo4;
    delete jabali1;
    delete aguila;
    delete aguila2;
    delete aguila3;
    delete flag;
    delete fuego;
    delete fuego1;
    delete cazador1;
    delete cazador2;
    delete bullet1;
    delete bullet2;
    zanahoria.clear();
    ladrillosNota.clear();

}
