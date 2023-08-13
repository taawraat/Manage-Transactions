#ifndef HOME_H
#define HOME_H
#include "newaccount.h"
#include "showprofile.h"
#include "database.h"
#include <QMainWindow>

namespace Ui {
class home;
}

class home : public QMainWindow
{
    Q_OBJECT

public:

    void openHome(int x, int y)
    {
        this->setWindowTitle("Home");
        this->show();
        this->setGeometry(x,y+32,862,670);
    }
    explicit home(QWidget *parent = nullptr);
    ~home();

private slots:
    void on_newAccount_clicked();

    void on_allUsers_doubleClicked(const QModelIndex &index);

    void on_searchButton_clicked();

    void on_logout_clicked();

private:
    Ui::home *ui;
    newAccount *newAcc;
    showProfile *showprofile;
    bool db_check = false;
};

#endif // HOME_H
