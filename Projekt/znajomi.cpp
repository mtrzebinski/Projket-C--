#include "znajomi.h"
#include "ui_znajomi.h"
#include "QMessageBox"

Znajomi::Znajomi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Znajomi)
{
    ui->setupUi(this);

    // Łączenie z bazą danych
    Login connect;

}

Znajomi::~Znajomi()
{
    delete ui;
}


// Przycisk do wyszukiwania osoby na liście znajomych
void Znajomi::on_pushButton_clicked()
{
    Login connect;
    QSqlQueryModel * model=new QSqlQueryModel();

    connect.connectOpen();
    QSqlQuery* pocz=new QSqlQuery(connect.projekt);
    QString firstname,lastname,birth_date,interests,mess;
    firstname=ui->lineEdit_firstname->text();
    lastname=ui->lineEdit_lastname->text();
    birth_date=ui->lineEdit_birth_date->text();
    interests=ui->lineEdit_interests->text();
    mess=ui->lineEdit_mess->text();

    pocz->prepare("SELECT*FROM Znajomi WHERE Imie='"+firstname+"' OR Nazwisko='"+lastname+"' OR Urodziny='"+birth_date+"' OR Zainteresowania='"+interests+"';");

    pocz->exec();
    model->setQuery(*pocz);
    ui->tableView->setModel(model);

    connect.connectClose();
    qDebug()<<(model->rowCount());
}

// Przycisku do dodawania osbób z listy wszystkich użytkowników do naszych znajomych
void Znajomi::on_pushButton_2_clicked()
{
    Login connect;
    QString firstname,lastname,birth_data,interests,mess;
    firstname=ui->lineEdit_firstname->text();
    lastname=ui->lineEdit_lastname->text();
    birth_data=ui->lineEdit_birth_date->text();
    interests=ui->lineEdit_interests->text();
    mess=ui->lineEdit_mess->text();

    connect.connectOpen();
    QSqlQuery pocz;
    pocz.prepare("INSERT INTO Znajomi(Imie, Nazwisko, Urodziny, Zainteresowania) SELECT Imie, Nazwisko, Urodziny, Zainteresowania FROM Lista where Lista.Imie='"+firstname+"' and Lista.Nazwisko='"+lastname+"';");
    if(pocz.exec())
    {
        QMessageBox::information(this,tr("DODAJ"),tr("Dodano do listy znajomych"));
        connect.connectClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),pocz.lastError().text());
    }

}

// Przycisk do usuwania znajmoych
void Znajomi::on_pushButton_3_clicked()
{
    Login connect;
    QString firstname,lastname,birth_data,interests,mess;
    firstname=ui->lineEdit_firstname->text();
    lastname=ui->lineEdit_lastname->text();
    birth_data=ui->lineEdit_birth_date->text();
    interests=ui->lineEdit_interests->text();
    mess=ui->lineEdit_mess->text();

    connect.connectOpen();
    QSqlQuery pocz;
    pocz.prepare("DELETE FROM Znajomi WHERE Imie='"+firstname+"' AND Nazwisko='"+lastname+"';");

    if(pocz.exec())
    {
        QMessageBox::information(this,tr("USUŃ"),tr("Usunięto znajomego"));
        connect.connectClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),pocz.lastError().text());
    }

}
// Przycisk do wysyłania wiadomości do naszych znajomych
void Znajomi::on_pushButton_5_clicked()
{
    Login connect;
    QString firstname,lastname,birth_data,interests,mess;
    firstname=ui->lineEdit_firstname->text();
    lastname=ui->lineEdit_lastname->text();
    birth_data=ui->lineEdit_birth_date->text();
    interests=ui->lineEdit_interests->text();
    mess=ui->lineEdit_mess->text();

    connect.connectOpen();
    QSqlQuery pocz;
    pocz.prepare("UPDATE Znajomi SET Wiadomość='"+mess+"' WHERE Imie='"+firstname+"' AND Nazwisko='"+lastname+"';");

    if(pocz.exec())
    {
        QMessageBox::information(this,tr("WYŚLIJ"),tr("Wysłano wiadomość"));
        connect.connectClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),pocz.lastError().text());
    }

}
// Przycisk łądujący tabelę
void Znajomi::on_pushButton_4_clicked()
{
    Login connect;
    QSqlQueryModel * model=new QSqlQueryModel();

    connect.connectOpen();
    QSqlQuery* pocz=new QSqlQuery(connect.projekt);

    pocz->prepare("SELECT*FROM Znajomi;");

    pocz->exec();
    model->setQuery(*pocz);
    ui->tableView->setModel(model);

    connect.connectClose();
    qDebug()<<(model->rowCount());

}


void Znajomi::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

    Login connect;

    connect.connectOpen();
    QSqlQuery pocz;
    pocz.prepare("SELECT*FROM Znajomi WHERE Imie='"+val+"' OR Nazwisko='"+val+"' OR Urodziny='"+val+"' OR Zainteresowania='"+val+"' or Wiadomość='"+val+"';");

    if(pocz.exec())
    {
        while (pocz.next())
        {
            ui->lineEdit_firstname->setText(pocz.value(1).toString());
            ui->lineEdit_lastname->setText(pocz.value(2).toString());
            ui->lineEdit_birth_date->setText(pocz.value(3).toString());
            ui->lineEdit_interests->setText(pocz.value(4).toString());
            ui->lineEdit_mess->setText(pocz.value(5).toString());
        }
        connect.connectClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),pocz.lastError().text());
    }
}
