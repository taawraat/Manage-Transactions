#ifndef REGISTRATION_H
#define REGISTRATION_H
#include "database.h"
#include "home.h"
#include <QMainWindow>

namespace Ui {
class Registration;
}

class Registration : public QMainWindow
{
    Q_OBJECT

public:
    void openRegistration(int x,int y)
    {
        this->setWindowTitle("Registration");
        this->show();
        this->setGeometry(x,y+32,862,670);
    }
    bool check;
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();

private slots:
    void on_pushButton_clicked();

    void on_back_clicked();

private:
    Ui::Registration *ui;
    home *hm;
    QWidget *back;
};

#endif // REGISTRATION_H
