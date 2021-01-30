#include "inicio.h"

#include <QMessageBox>
#include <Qstring>

Inicio::Inicio(View *view, QWidget *parent) : QGraphicsScene(parent)
{
    viewer = view;
    viewer->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    scroll = new QScrollBar;
    scroll = viewer->horizontalScrollBar();

    foreground = new QGraphicsPixmapItem(QPixmap(":/fodoinicio.png"));
    addItem(foreground);
    this->setFocus();
    this->setSceneRect(0,0,1280,720);
    view->sceneSet(this);


    //Push Button for developer login
    Unjugador = new QPushButton(viewer);
    Unjugador->setText("New Game");
    Unjugador->setObjectName(QString("New Game"));
    Unjugador->setToolTip("Login as a guest");
    Unjugador->setGeometry(QRect(400, 535, 100, 32));
    connect(Unjugador, SIGNAL(clicked()), this, SLOT(unjugadorLogin()));

    //Push Button for developer login
    multijugador = new QPushButton(viewer);
    multijugador->setText("Multiplayer");
    multijugador->setObjectName(QString("Multiplayer"));
    multijugador->setToolTip("Login as a guest");
    multijugador->setGeometry(QRect(540, 535, 100, 32));
    connect(multijugador, SIGNAL(clicked()), this, SLOT(multijugadorLogin()));

    newUserButton = new QPushButton(viewer);
    newUserButton->setText("New User");
    newUserButton->setObjectName(QString("newUserButton"));
    newUserButton->setToolTip("Click to create a login");
    newUserButton->setGeometry(QRect(642, 500, 100, 32));
    connect(newUserButton, SIGNAL(clicked()), this, SLOT(newUser()));

    labelusuario = new QLineEdit(viewer);
    //userLine->setObjectName(QString("userLine"));
    labelusuario->setToolTip("Enter you username");
    labelusuario->setGeometry(QRect(540, 320, 200, 25));

    //Add Label for username
    QFont font("MV Boli", 15, QFont::Bold);
    userName = new QLabel(viewer);
    userName->setFont(font);
    userName->setText("Username");
    userName->setObjectName(QString("username"));
    userName->setGeometry(QRect(430, 320, 100, 25));

    //Add line edit for password, set tooltip
    labelcontrasena = new QLineEdit(viewer);
    labelcontrasena->setEchoMode(QLineEdit::Password);
    labelcontrasena->setObjectName(QString("passLine"));
    labelcontrasena->setToolTip("Enter password");
    labelcontrasena->setGeometry(QRect(540, 350, 200, 25));

    //Add Label For password
    password = new QLabel(viewer);
    password->setFont(font);
    password->setText("Password");
    password->setObjectName(QString("password"));
    password->setGeometry(QRect(430, 350, 100, 25));

}

string Inicio::lectura_txt(string name)
{
    long long int tam;
    string data;
    //abrir archivo en modo lectura o posicionar el cursos al final del archivo(ate)
    fstream k(name,fstream::in | fstream::ate);
    tam=k.tellg();  // determina el tamaño de caracteres en el  archivo al colocar el cursor al final del texto
    k.seekg(0);    // defino el cursor al incio del texto
    if (k.is_open()){
        for(long long int i=0;i<tam;i++) data.push_back(k.get());// concateno caracter por caracter
    }
    else cout<<"El archivo no existe"<<endl;
    k.close();//cerrar archivo
    return data;
}

bool Inicio::checkUser()
{
    QString nombre=labelusuario->text();
    QString contrasena=labelcontrasena->text();
    string stringNombre = nombre.toLocal8Bit().constData();
    string stringContrasena = contrasena.toLocal8Bit().constData();
    dato.append(stringNombre);
    dato.push_back(',');
    dato.append(stringContrasena);
    dato.push_back('\n');
    database=lectura_txt("registro1.txt");
    size_t found=database.find(dato);
    if(found!=string::npos) return true;
    else return false;


}


void Inicio::multijugadorLogin()
{
     multijugador->close();
     Unjugador->close();
     newUserButton->close();
     scene = new PrimerMundo(false,scroll,this);
     viewer->sceneSet(scene);

}

void Inicio::unjugadorLogin()
{
    usuario=checkUser();
    if(usuario){
        Unjugador->close();
        multijugador->close();
        newUserButton->close();
        scene = new PrimerMundo(true,scroll,this);
        viewer->sceneSet(scene);
    }
    else {
        QMessageBox msgBoxFail;
        msgBoxFail.setText("That is not a valid email address.   ");
        msgBoxFail.setWindowTitle("Warning");
        msgBoxFail.exec();
        return;
    }

}

void Inicio::newUser(){

    loginWindow = new Login();
    loginWindow->exec();

}




