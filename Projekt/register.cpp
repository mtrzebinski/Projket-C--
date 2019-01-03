#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

// Przycisk przenoszący do panelu logowania, po wpisaniu odpowiednich danych użytkownika
void Register::on_pushButton_clicked()
{
    QString username,password;
    username=ui->lineEdit_username->text();
    password=ui->lineEdit_password->text();

    connectOpen();

    // Deklaracja zmiennej i wypakowanie danych z tabeli i przypisanie odpowiednich pól do zmiennych
    QSqlQuery pocz;
    pocz.prepare("INSERT INTO Loguj(Login, Haslo) VALUES('"+username +"','"+password+ "');" );
    if(pocz.exec())
    {
        this->hide();
        Login login;
        login.setModal(true);
        login.exec();
    }


}
