/*
 Proyecto: Rabbit's Adventures

 Creado por: Laura Isabel Vidal - Mauricio Duque

 Informática II
 Facultad de Ingeniería
 Departamento de Electrónica y Telecomunicaciones
 Universidad de Antioquia

 Clase login: ventana que permite registrar un nuevo usuario, donde despues de ingresado
 el nombre y contraseña se adecuan los datos ("nombre","contraseña)
 y se escriben en un archivo .txt, llamado registro1.txt que será la base de datos del juego

 */


#include "login.h"
#include "ui_login.h"
#include <QDebug>


Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::escribir_txt(string name, string data)
{
        fstream k(name,fstream::app);
        k << data; // se escribe sobre archivo ensayo
        //k.write(data.c_str(),data.length());
        k.close();//cerrar archivo
}

void Login::on_Registrar_clicked()
{
    string dato;
    nombre=ui->USERNAME->text();
    contrasena= ui->PASSWORD->text();
    std::string stringNombre = nombre.toLocal8Bit().constData();
    std::string stringContrasena = contrasena.toLocal8Bit().constData();
    dato.append(stringNombre);
    dato.push_back(',');
    dato.append(stringContrasena);
    dato.push_back('\n');
    escribir_txt("registro1.txt",dato);
    Login::reject();
}

void Login::on_pushButton_2_clicked()
{
    Login::reject();
}
