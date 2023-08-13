#include "newaccount.h"
#include "ui_newaccount.h"
#include "home.h"
#include <QMessageBox>

void newAccount::enableDSP(bool x)
{
    ui->accValidFrom->setEnabled(x);
    ui->accValidTill->setEnabled(x);
    ui->accPerMonth->setEnabled(x);
    ui->validFrom->setEnabled(x);
    ui->validTill->setEnabled(x);
    ui->perMonth->setEnabled(x);
}
newAccount::newAccount(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::newAccount)
{
    ui->setupUi(this);
    this->back = parent;
    Database mydb;
    db_opened = mydb.openDB();
}

newAccount::~newAccount()
{
    delete ui;
}

void newAccount::on_SB_pressed()
{
    enableDSP(0);
}

void newAccount::on_DPS_pressed()
{
    enableDSP(1);
}

void newAccount::on_submit_clicked()
{
    Database mydb;
    QSqlQuery qry;
    if(!db_opened)
        mydb.openDB();
    QString name = ui->accName->text();
    QString no = ui->accNo->text();
    QString bank_name = ui->accBankName->text();
    QString bank_address = ui->accBankAddress->text();
    QString bank_mobile = ui->accBankMobile->text();
    QString bank_email = ui->accBankEmail->text();
    QString total_amount = ui->accTotal->text();
    QString per_month = ui->accPerMonth->text();
    QString last_deposit = ui->accLastDate->text();
    QString valid_from = ui->accValidFrom->text();
    QString valid_till = ui->accValidTill->text();

    if(ui->SB->isChecked()){
        if(name == NULL || no == NULL || bank_name == NULL || bank_address == NULL || total_amount == NULL || last_deposit == NULL)
            ui->warning->setText("*Please fill required fields!");
        else
            qry.prepare("INSERT INTO acc_info (acc_no, name, type, bank_name, bank_address, bank_mobile, bank_email, total_amount, last_deposit) \
                        VALUES ('"+no+"','"+name+"','"+(QString)"SB"+"','"+bank_name+"','"+bank_address+"','"+bank_mobile+"','"+bank_email+"','"+total_amount+"','"+last_deposit+"')");
    }
    else{
        if(name == NULL || no == NULL || bank_name == NULL || bank_address == NULL || total_amount == NULL || last_deposit == NULL || per_month == NULL || valid_from == NULL || valid_till == NULL)
            ui->warning->setText("*Please fill required fields!");
        else
            qry.prepare("INSERT INTO acc_info (acc_no, name, type, bank_name, bank_address, bank_mobile, bank_email, total_amount, last_deposit, per_month, valid_from, valid_till) \
                        VALUES ('"+no+"','"+name+"','"+(QString)"DPS"+"','"+bank_name+"','"+bank_address+"','"+bank_mobile+"','"+bank_email+"','"+total_amount+"','"+last_deposit+"','"+per_month+"','"+valid_from+"','"+valid_till+"')");
    }
    if(qry.exec()){
       ui->warning->setText("");
       QMessageBox::information(this, "Saved", "Data saved successfully");
    }
    else
       QMessageBox::critical(this,"Error!", "Failed to save data!");
}

void newAccount::on_back_clicked()
{
    Database db;
    db.closeDB();
    int x = this->frameGeometry().x();
    int y = this->frameGeometry().y();
    home *hm;
    hm = new home;
    this->close();
    hm->openHome(x,y);
}

void newAccount::on_reset_clicked()
{
    ui->accName->setText("");
    ui->accNo->setText("");
    ui->accBankName->setText("");
    ui->accBankAddress->setText("");
    ui->accBankMobile->setText("");
    ui->accBankEmail->setText("");
    ui->accTotal->setText("");
    ui->accPerMonth->setText("");
}
