#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <login.h>

namespace Ui {
class Register;
}

class Register : public QDialog
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
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
