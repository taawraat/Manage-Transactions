#ifndef SHOWPROFILE_H
#define SHOWPROFILE_H
#include "database.h"
#include <QMainWindow>

namespace Ui {
class showProfile;
}

class showProfile : public QMainWindow
{
    Q_OBJECT

public:
    void openShowProfile(int x,int y)
    {
        this->setWindowTitle("Profile");
        this->show();
        this->setGeometry(x,y+32,862,670);
    }
    explicit showProfile(QWidget *parent = nullptr,const QString val=nullptr);
    ~showProfile();

private:
    void cal(bool Case);
    void DPS(bool x);
    void editMode(bool y);
    Ui::showProfile *ui;
    QWidget *back;
    QString accNo;

private slots:
    void on_submit_clicked();
    void on_edit_clicked();
    void on_cancel_clicked();
    void on_add_clicked();
    void on_withdraw_clicked();
    void on_dlt_clicked();
    void on_back_clicked();
};

#endif // SHOWPROFILE_H
