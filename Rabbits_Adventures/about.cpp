#include "about.h"
#include "ui_about.h"

#include <QDesktopWidget>
#include <QFile>

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);

    //this->setMaximumWidth(350);
    this->setFixedSize(350,300);

    this->setWindowTitle("Rabbit's adventures: About");

    this->mainVBox = new QVBoxLayout;

    this->logo = new QPixmap(":/ass.png");
    logoLbl = new QLabel;
    logoLbl->setPixmap(*logo);
    logoLbl->setContentsMargins(2,10,2,2);


//    this->spacerBar = new QPixmap(":/images/AD_Spacer_Bar.png");
//    this->spacerLabel = new QLabel;
//    spacerLabel->setPixmap(*spacerBar);
//    spacerLabel->setContentsMargins(55,8,0,3);

    this->schoolInfo = new QLabel;
    this->info= new QLabel;
    this->classInfo = new QLabel;
    this->groupMember1 = new QLabel;
    this->groupMember2 = new QLabel;



    this->setLayout(mainVBox);
    mainVBox->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    mainVBox->addWidget(logoLbl);
    logoLbl->show();

    mainVBox->addWidget(schoolInfo);
    mainVBox->addWidget(info);
    mainVBox->addWidget(classInfo);
    mainVBox->addWidget(spacerLabel);
    mainVBox->addWidget(groupMember1);
    mainVBox->addWidget(groupMember2);


    schoolInfo->show();
    schoolInfo->setAlignment(Qt::AlignCenter);
    schoolInfo->setText("Universidad de Antioquia | 2021 \n" );
    schoolInfo->setTextFormat(Qt::RichText);
    schoolInfo->setTextInteractionFlags(Qt::TextBrowserInteraction);
    schoolInfo->setOpenExternalLinks(true);
    schoolInfo->setContentsMargins(0,0,20,0);
    schoolInfo->show();

    info->setAlignment(Qt::AlignCenter);
    info->setText("Facultad de ingenieria" );
    info->setTextFormat(Qt::RichText);
    info->setTextInteractionFlags(Qt::TextBrowserInteraction);
    info->setOpenExternalLinks(true);
    info->setContentsMargins(0,0,20,0);

    classInfo->show();
    classInfo->setAlignment(Qt::AlignCenter);
    classInfo->setText("Informática II. Proyecto Final : <a href = \"https://github.com/Mauricioduque/Proyecto_final.git\"> GitHub </a> ");
    classInfo->setTextFormat(Qt::RichText);
    classInfo->setTextInteractionFlags(Qt::TextBrowserInteraction);
    classInfo->setOpenExternalLinks(true);

    groupMember1->show();
    groupMember1->setAlignment(Qt::AlignCenter);
    groupMember1->setText("Mauricio Duque : <a href = \"https://github.com/Mauricioduque\"> GitHub </a> ");
    groupMember1->setTextFormat(Qt::RichText);
    groupMember1->setTextInteractionFlags(Qt::TextBrowserInteraction);
    groupMember1->setOpenExternalLinks(true);
    groupMember1->setContentsMargins(14,0,0,0);

    groupMember2->show();
    groupMember2->setAlignment(Qt::AlignCenter);
    groupMember2->setText("Laura Isabel Vidal : <a href = \"https://github.com/Laurav2103\"> GitHub </a> ");
    groupMember2->setTextFormat(Qt::RichText);
    groupMember2->setTextInteractionFlags(Qt::TextBrowserInteraction);
    groupMember2->setOpenExternalLinks(true);
    groupMember2->setContentsMargins(20,0,0,0);



}

about::~about()
{
    delete ui;
}
