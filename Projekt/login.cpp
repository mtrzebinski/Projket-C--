#include "login.h"
#include "register.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

// Przycisk przenoszący do menu po zalogowaniu
void Login::on_pushButton_clicked()
{
    QString username,password;
    username=ui->lineEdit_username->text();
    password=ui->lineEdit_password->text();

    connectOpen();

    // Deklaracja zmiennej i wypakowanie danych z tabeli i przypisanie odpowiednich pól do zmiennych
    QSqlQuery pocz;
    pocz.prepare("SELECT*FROM Loguj WHERE Login='"+username +"' AND NOT Login='""' AND Haslo='"+password+ "' AND NOT Haslo='""';" );

    // Pętla sprawdzająca poprawność podanych danych
    if(pocz.exec())
    {
        int count=0;
        while(pocz.next())
        {
            count++;
        }
        if(count==1)
        {
            this->hide();
            Menu menu;
            menu.setModal(true);
            menu.exec();
        }
        if(count<1)
            ui->label->setText("Login albo hasło jest nie prawidłowe");
    }
}

// Przycisk przenoszący do panelu rejestracji
void Login::on_pushButton_2_clicked()
{
    this->hide();
    Register regist;
    regist.setModal(true);
    regist.exec();
}
