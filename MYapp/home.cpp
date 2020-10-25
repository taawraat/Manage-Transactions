#include "home.h"
#include "login.h"
#include "ui_home.h"
#include "showprofile.h"
#include <QPixmap>
#include <QRegExp>

home::home(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::home)
{
    ui->setupUi(this);
    Database mydb;
    if(mydb.openDB()) db_check = true;

    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry = new QSqlQuery();

    qry->prepare("select name,acc_no from acc_info");

    qry->exec();

    model->setQuery(*qry);
    ui->allUsers->setModel(model);
    ui->allUsers->setColumnWidth(0, ui->allUsers->width()/2);
    ui->allUsers->setColumnWidth(1, 300);
    ui->allUsers->setCornerButtonEnabled(false);
    ui->allUsers->setWordWrap(false);
    QPixmap pic(":/resources/img/magnifying-glass.png");
    QIcon button(pic);
    ui->searchButton->setIcon(button);
}

home::~home()
{
    delete ui;
}

void home::on_newAccount_clicked()
{
    Database mydb;
    if(db_check) mydb.closeDB();
    newAcc = new newAccount(this);
    int x = this->frameGeometry().x();
    int y = this->frameGeometry().y();
    this->close();
    newAcc->openNewAcc(x,y);
}

void home::on_allUsers_doubleClicked(const QModelIndex &index)
{
    QString val = ui->allUsers->model()->data(index).toString();
    showprofile = new showProfile(this,val);
    int x = this->frameGeometry().x();
    int y = this->frameGeometry().y();
    this->close();
    showprofile->openShowProfile(x,y);
}

void home::on_searchButton_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery *qry = new QSqlQuery;

    if(ui->search->text() == NULL)
        qry->prepare("select name from acc_info");
    else
        qry->prepare("select name from acc_info where name='"+ui->search->text()+"'");

    qry->exec();
    model->setQuery(*qry);
    ui->allUsers->setModel(model);
    ui->allUsers->setCornerButtonEnabled(false);
}

void home::on_logout_clicked()
{
    Database mydb;
    mydb.closeDB();
    Login *lg;
    lg = new Login;
    int x = this->frameGeometry().x();
    int y = this->frameGeometry().y();
    this->close();
    lg->openLogin(x,y);
}
