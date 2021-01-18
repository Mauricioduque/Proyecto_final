#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class GameOver;
}

class GameOver : public QDialog
{
    Q_OBJECT

public:
    explicit GameOver(QWidget *parent = nullptr);
    ~GameOver();

private slots:
    void on_iniciar_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::GameOver *ui;
};

#endif // GAMEOVER_H
