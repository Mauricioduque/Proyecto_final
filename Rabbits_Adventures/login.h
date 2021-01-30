#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <iostream>
#include <fstream>
#include <string>
#include <QString>
#include <QWidget>
using namespace std;

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    void escribir_txt(string name,string data);

private slots:
    void on_Registrar_clicked();

private:
    Ui::Login *ui;
    QString nombre,contrasena;
    string dato;
};

#endif // LOGIN_H
