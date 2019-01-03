#ifndef LOGIN_H
#define LOGIN_H

#include <QtSql>
#include <QDebug>
#include <QDialog>
#include <QFileInfo>
#include <menu.h>
#include <register.h>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    QSqlDatabase projekt;

    void connectClose()
    {
        projekt.close();
        projekt.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connectOpen()
    {
        projekt=QSqlDatabase::addDatabase("QSQLITE");
        projekt.setDatabaseName("C:/Users/mateu/Desktop/Projekt C++/Projekt/projekt.db");

        if(!projekt.open())
        {
            return false;
        }
        else
        {
            return true;
        }
    }

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


private:
    Ui::Login *ui;
};

#endif // LOGIN_H
