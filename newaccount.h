#ifndef NEWACCOUNT_H
#define NEWACCOUNT_H
#include "database.h"
#include <QMainWindow>

namespace Ui {
class newAccount;
}

class newAccount : public QMainWindow
{
    Q_OBJECT

public:
    Database mydb;
    void openNewAcc(int x,int y)
    {
        this->setWindowTitle("Create Account");
        this->show();
        this->setGeometry(x,y+32,862,670);
    }
    explicit newAccount(QWidget *parent = nullptr);
    ~newAccount();

private slots:
    void on_SB_pressed();

    void on_DPS_pressed();

    void on_submit_clicked();

    void on_back_clicked();

    void on_reset_clicked();

private:
    void enableDSP(bool x);
    Ui::newAccount *ui;
    bool db_opened = false;
    QWidget *back;
};

#endif // NEWACCOUNT_H
