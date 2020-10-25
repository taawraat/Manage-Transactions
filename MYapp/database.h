#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QMainWindow>

class Database : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase db;

    bool openDB()
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("/home/tawraat/DB/MyApp.db");

        if(db.open()) return true;
        else return false;
    }

    void closeDB()
    {
        db.close();
        db.removeDatabase(QSqlDatabase::defaultConnection);
    }

    ~Database(){}
};

#endif // DATABASE_H




