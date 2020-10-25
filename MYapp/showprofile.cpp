#include "showprofile.h"
#include "ui_showprofile.h"
#include "home.h"
#include <QMessageBox>

void showProfile::cal(bool Case)
{
    int x,y,total;
    QSqlQuery qry;
    QString no = ui->accNo->text();
    y = ui->accAdd->text().toInt();
    x = ui->accTotal->text().toInt();
    if(Case == 1) total = x+y;
    else if(Case == 0 && x-y>0) total = x-y;
    else total = 0;
    QString temp = QString::number(total);
    qry.prepare("update acc_info set total_amount='"+temp+"' where acc_no='"+no+"'");
    if(ui->accAdd->text() == NULL)
        QMessageBox::critical(this,"Warning!","Please give desired value!");
    else if(qry.exec()){
        QMessageBox::information(this, "Update", "Data updated successfully");
        ui->accTotal->setText(temp);
    }
    else
        QMessageBox::critical(this, "Error!", "An unexpected error occured!");
}

void showProfile::DPS(bool x)
{
    ui->accValidFrom->setEnabled(x);
    ui->accValidTill->setEnabled(x);
    ui->accPerMonth->setEnabled(x);
    ui->validFrom->setEnabled(x);
    ui->validTill->setEnabled(x);
    ui->perMonth->setEnabled(x);
}

void showProfile::editMode(bool y)
{
    ui->accNo->setReadOnly(!y);
    ui->accName->setReadOnly(!y);
    ui->accBankName->setReadOnly(!y);
    ui->accBankAddress->setReadOnly(!y);
    ui->accBankMobile->setReadOnly(!y);
    ui->accBankEmail->setReadOnly(!y);
    ui->accTotal->setReadOnly(!y);
    ui->accLastDate->setReadOnly(!y);
    ui->accPerMonth->setReadOnly(!y);
    ui->accValidFrom->setReadOnly(!y);
    ui->accValidTill->setReadOnly(!y);
    ui->submit->setEnabled(y);
    ui->dlt->setEnabled(y);
    ui->cancel->setEnabled(y);

    if(y == true){
        ui->submit->setStyleSheet("background: green; color: white");
        ui->dlt->setStyleSheet("background: rgb(196, 160, 0);\
                               font-weight: 500;\
                               color:white;");
        ui->cancel->setStyleSheet("background: red;\
                                  font-weight: 500;\
                                  color:white;");
    }
    else
    {
        ui->submit->setStyleSheet("background: grey; font-weight: 500; color: black");
        ui->dlt->setStyleSheet("background: grey;\
                               font-weight: 500;\
                               color:black;");
        ui->cancel->setStyleSheet("background: grey;\
                                  font-weight: 500;\
                                  color:black;");
    }
}

showProfile::showProfile(QWidget *parent,QString val) :
    QMainWindow(parent),
    ui(new Ui::showProfile)
{
    ui->setupUi(this);

    QSqlQuery qry;
    qry.prepare("select * from acc_info where acc_no='"+val+"'");
    this->back = parent;
    if(qry.exec())
    {
        while (qry.next()) {
            ui->accNo->setText(qry.value(0).toString());
            ui->accName->setText(qry.value(1).toString());
            ui->accType->setText(qry.value(2).toString());
            if(qry.value(2).toString() == "DPS") DPS(true);
            ui->accBankName->setText(qry.value(3).toString());
            ui->accBankAddress->setText(qry.value(4).toString());
            ui->accBankMobile->setText(qry.value(5).toString());
            ui->accBankEmail->setText(qry.value(6).toString());
            ui->accTotal->setText(qry.value(7).toString());
            ui->accLastDate->setText(qry.value(8).toString());
            ui->accPerMonth->setText(qry.value(9).toString());
            ui->accValidFrom->setText(qry.value(10).toString());
            ui->accValidTill->setText(qry.value(11).toString());
        }
    }
    this->accNo = ui->accNo->text();
}

showProfile::~showProfile()
{
    delete ui;
}

void showProfile::on_submit_clicked()
{
    QString type = ui->accType->text();
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

    QSqlQuery qry;

    if(name == NULL || no == NULL || bank_name == NULL || bank_address == NULL || total_amount == NULL || last_deposit == NULL || (type=="DPS" && (per_month == NULL || valid_from == NULL || valid_till == NULL)))
        ui->warning->setText("*Please fill required fields!");

    else{
        qry.prepare("update acc_info set acc_no='"+no+"', name='"+name+"', bank_name='"+bank_name+"', bank_address='"+bank_address+"', bank_mobile='"+bank_mobile+"', bank_email='"+bank_email+"', total_amount='"+total_amount+"', last_deposit='"+last_deposit+"', per_month='"+per_month+"', valid_from='"+valid_from+"', valid_till='"+valid_till+"' where acc_no='"+this->accNo+"'");

        if(qry.exec()){
            ui->warning->setText("");
            QMessageBox::information(this,"Saved", "successfully edited");
            this->accNo = ui->accNo->text();
        }
        else
            QMessageBox::critical(this,"Error!", "Failed to save data!");
    }
}

void showProfile::on_edit_clicked()
{
    editMode(true);
}

void showProfile::on_cancel_clicked()
{
    editMode(false);
}

void showProfile::on_add_clicked()
{
    cal(1);
}

void showProfile::on_withdraw_clicked()
{
    cal(0);
}

void showProfile::on_dlt_clicked()
{
    QString no = ui->accNo->text();

    QSqlQuery qry;
    qry.prepare("delete from acc_info where acc_no='"+no+"'");
    if(qry.exec()){
        QMessageBox::information(this, "Deleted", "Account deleted successfully!");
        on_back_clicked();
    }
    else
        QMessageBox::critical(this,"Error", "An unexpected error occured!");
}

void showProfile::on_back_clicked()
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
