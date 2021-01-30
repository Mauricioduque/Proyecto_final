#include "login.h"
#include "ui_login.h"
#include <QDebug>

string archivo;

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
        /* k: objeto que pertenece a la clase fstream,
         * donde estan definidas todas las funciones,
         * que permite comunicarnos con los archivos de texto.
         * se crea o se abre el archivo ensayo en modo escritura (fstream::out)
         *  o de manera binaria (fstream::binary)
        */
        fstream k(name,fstream::out | fstream::binary);
        k << data; // se escribe sobre archivo ensayo
        //k.write(data.c_str(),data.length());
        k.close();//cerrar archivo
}

void Login::on_Registrar_clicked()
{
    nombre=ui->USERNAME->text();
    contrasena= ui->PASSWORD->text();
    std::string stringNombre = nombre.toLocal8Bit().constData();
    std::string stringContrasena = contrasena.toLocal8Bit().constData();
    dato.append(stringNombre);
    dato.push_back(',');
    dato.append(stringContrasena);
    dato.push_back('\n');
    archivo.append(dato);
    escribir_txt("registro1.txt",archivo);
    close();
}
