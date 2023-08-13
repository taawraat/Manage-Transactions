#include "login.h"
#include "ui_login.h"
#include<QPixmap>
#include <QFileDialog>
#include <QMessageBox>
Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    Database mydb;
    mydb.openDB();
    QPixmap pix(":/resources/img/login.svg");
    int w = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_clicked()
{
    Database mydb;
    QSqlQuery qry;

    QString username,password;
    username = ui->username->text();
    password = ui->password->text();
    qry.prepare("select * from users where name='"+username+"' and password='"+password+"'");

    if(username == NULL || password == NULL)
        ui->warning->setText("*Please enter username and password!");
    else if(qry.exec())
    {
        int count = 0;
        while(qry.next())
        {
            count++;
            if(count > 1)
                break;
        }
        if(count == 1){
            mydb.closeDB();
            hm = new home;
            int x = this->frameGeometry().x();
            int y = this->frameGeometry().y();
            this->close();
            hm->openHome(x,y);
        }
        else
            ui->warning->setText("*username or password is incorrect!");
    }
}

void Login::on_signup_clicked()
{
    Database mydb;
    mydb.closeDB();
    registration = new Registration(this);
    int x = this->frameGeometry().x();
    int y = this->frameGeometry().y();
    this->close();
    registration->openRegistration(x,y);
}
