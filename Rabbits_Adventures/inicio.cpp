/*
 Proyecto: Rabbit's Adventures

 Creado por: Laura Isabel Vidal - Mauricio Duque

 Informática II
 Facultad de Ingeniería
 Departamento de Electrónica y Telecomunicaciones
 Universidad de Antioquia

 Clase inicio: ventana que despliega la pantalla de inicio,
 donde se adminsitra el registro e ingreso de usuarios y el modo en que se
 desee jugar

 */


#include "inicio.h"
#include <QMessageBox>

//se genera la ventana inicial y los botones de cargar partida, mltijugador o nuevo usuario
//y los text edit de usuario y contrasena
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


    //Push Button para jugar individual
    Unjugador = new QPushButton(viewer);
    Unjugador->setText("Load Game");
    Unjugador->setObjectName(QString("Load Game"));
    Unjugador->setToolTip("Login as a guest");
    Unjugador->setGeometry(QRect(440, 400, 100, 32));
    connect(Unjugador, SIGNAL(clicked()), this, SLOT(unjugadorLogin()));

    //Push Button para multijugador
    multijugador = new QPushButton(viewer);
    multijugador->setText("Multiplayer");
    multijugador->setObjectName(QString("Multiplayer"));
    multijugador->setToolTip("Login as a guest");
    multijugador->setGeometry(QRect(550, 400, 100, 32));
    connect(multijugador, SIGNAL(clicked()), this, SLOT(multijugadorLogin()));

    //Push Button para about
    aboutButton = new QPushButton(viewer);
    aboutButton->setText("About");
    aboutButton->setObjectName(QString("about"));
    aboutButton->setToolTip("about information");
    aboutButton->setGeometry(QRect(490, 500, 100, 32));
    connect(aboutButton, SIGNAL(clicked()), this, SLOT(showAbout()));


    instructionsButton = new QPushButton(viewer);
    instructionsButton->setText("Instructions");
    instructionsButton->setObjectName(QString("Instructions"));
    instructionsButton->setToolTip("about information");
    instructionsButton->setGeometry(QRect(610, 500, 100, 32));
    connect(instructionsButton, SIGNAL(clicked()), this, SLOT(showinstruction()));

    newUserButton = new QPushButton(viewer);
    newUserButton->setText("New User");
    newUserButton->setObjectName(QString("newUserButton"));
    newUserButton->setToolTip("Click to create a login");
    newUserButton->setGeometry(QRect(660, 400, 100, 32));
    connect(newUserButton, SIGNAL(clicked()), this, SLOT(newUser()));

    labelusuario = new QLineEdit(viewer);
    labelusuario->setObjectName(QString("userLine"));
    labelusuario->setToolTip("Enter you username");
    labelusuario->setGeometry(QRect(540, 320, 200, 25));

    //Se agrega label para username
    QFont font("MV Boli", 15, QFont::Bold);
    userName = new QLabel(viewer);
    userName->setFont(font);
    userName->setText("Username");
    userName->setObjectName(QString("username"));
    userName->setGeometry(QRect(430, 320, 100, 25));

    //Se agrega  line edit para  password, con opción de ocultarlo
    labelcontrasena = new QLineEdit(viewer);
    labelcontrasena->setEchoMode(QLineEdit::Password);
    labelcontrasena->setObjectName(QString("passLine"));
    labelcontrasena->setToolTip("Enter password");
    labelcontrasena->setGeometry(QRect(540, 350, 200, 25));

    //Se agrega label para password
    password = new QLabel(viewer);
    password->setFont(font);
    password->setText("Password");
    password->setObjectName(QString("password"));
    password->setGeometry(QRect(430, 350, 100, 25));

}

//se carga en un string la base de datos
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

//se verifica si el registro del usuario es correcto
bool Inicio::checkUser()
{
    string dato;
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
    if(found!=string::npos){

        return true;
    }
    else {
        return false;
    }


}

//inicia en modo multijugador
void Inicio::multijugadorLogin()
{
     multijugador->close();
     Unjugador->close();
     newUserButton->close();
     labelusuario->close();
     labelcontrasena->close();
     password->close();
     userName->close();
     aboutButton->close();
     instructionsButton->close();
     scene = new PrimerMundo(false,scroll,this);
     viewer->sceneSet(scene);

}

//inicia en modo un jugador si se realiza de manera correcta el ingreso de usuario
void Inicio::unjugadorLogin()
{
    usuario=checkUser();
    if(usuario){
        Unjugador->close();
        multijugador->close();
        newUserButton->close();
        labelusuario->close();
        labelcontrasena->close();
        password->close();
        userName->close();
        aboutButton->close();
        instructionsButton->close();
        scene = new PrimerMundo(true,scroll,this);
        viewer->sceneSet(scene);
    }
    else {
        QMessageBox msgBoxFail;
        msgBoxFail.setText("That is not a valid user.   ");
        msgBoxFail.setWindowTitle("Warning");
        msgBoxFail.exec();
        return;
    }

}

//despliega la ventana de registro de nuevo usuario
void Inicio::newUser()
{
    loginWindow = new Login();
    loginWindow->open();
}

//despliega la ventana de la información de los creadores
void Inicio::showAbout()
{
    aboutt = new about;
    aboutt->setWindowFlags(((aboutt->windowFlags()|Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
    aboutt->open();
    return;
}

//despliega la ventana de instrucciones
void Inicio::showinstruction()
{
    Instruction = new instructions;
    Instruction->setWindowFlags(((Instruction->windowFlags()|Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
    Instruction->open();
    return;
}

