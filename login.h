#ifndef LOGIN_H
#define LOGIN_H
#include "registration.h"
#include "home.h"
#include "database.h"
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    void openLogin(int x, int y)
    {
        this->setWindowTitle("Login");
        this->show();
        this->setGeometry(x,y+32,862,670);
    }
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_signup_clicked();

    void on_login_clicked();

private:
    Ui::Login *ui;
    Registration *registration;
    home *hm;
};
#endif // LOGIN_H
