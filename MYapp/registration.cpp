#include "registration.h"
#include "ui_registration.h"
#include <QPixmap>

Registration::Registration(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
    this->back = parent;
    Database mydb;
    check = mydb.openDB();
    QPixmap pix(":/resources/img/signup.svg");
    int h = ui->label_pic->width();
    int w = ui->label_pic->height() - 150;
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_pushButton_clicked()
{
    QSqlQuery qry;

    QString name,email,password,gender,password2;
    name = ui->user_name->text();
    email= ui->user_email->text();
    password = ui->user_password->text();
    password2 = ui->user_password2->text();
    if(ui->male->isChecked()) gender = "male";
    else gender = "female";
    if(name == NULL || email == NULL || password == NULL || password2 == NULL || !(ui->checkBox->isChecked()))
        ui->warning->setText("*Please fill all the fields and checkbox!");
    else if(QString::compare(password,password2) != 0)
        ui->warning->setText("*Password doesn't match!");
    else{
        ui->warning->setText("");
        qry.prepare("INSERT INTO users (name,email,gender,password) VALUES ('"+name+"','"+email+"','"+gender+"','"+password+"')");
        if(qry.exec())
        {
            Database mydb;
            mydb.closeDB();
            hm = new home;
            int x = this->frameGeometry().x();
            int y = this->frameGeometry().y();
            this->close();
            hm->openHome(x,y);
        }
        else
            ui->warning->setText("*username already exists");
    }
}

void Registration::on_back_clicked()
{
    int x = this->frameGeometry().x();
    int y = this->frameGeometry().y();
    this->back->setGeometry(x,y+33,862,670);
    this->close();
    this->back->show();
}
