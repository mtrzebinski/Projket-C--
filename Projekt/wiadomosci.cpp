#include "wiadomosci.h"
#include "ui_wiadomosci.h"
#include "QMessageBox"

Wiadomosci::Wiadomosci(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Wiadomosci)
{
    ui->setupUi(this);

    /*Połączenie z bazą danych i wyświetlanie informacji czy jest połaczona*/
    Login connect;

}

Wiadomosci::~Wiadomosci()
{
    delete ui;
}

/*Funkcja przycisku do zapisywania rekordu*/
void Wiadomosci::on_pushButton_clicked()
{
    Login connect;
    QString firstname,lastname,comment;
    firstname=ui->lineEdit_firstname->text();
    lastname=ui->lineEdit_lastname->text();
    comment=ui->lineEdit_comment->text();


    if(!connect.connectOpen())
    {
        qDebug()<<"Wstąpił nieoczekiwany problem z odtworzeniem bazy danych";
        return;
    }

    connect.connectOpen();
    QSqlQuery start;
    start.prepare("UPDATE Wiadomosci SET Wiadomosc='"+comment+"' WHERE Imie='"+firstname+"' AND Nazwisko='"+lastname+"';");

    if(start.exec())
    {
        QMessageBox::information(this,tr("Zapisane"),tr("Zapisane"));
        connect.connectClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),start.lastError().text());
    }
}

/*Przycisk służący do załadowania tabeli do tableView, wyświetlenia pola comboBox dla personali i tytułów*/
void Wiadomosci::on_pushButton_2_clicked()
{
    Login connect;
    QSqlQueryModel * model=new QSqlQueryModel();

    connect.connectOpen();
    QSqlQuery* start=new QSqlQuery(connect.projekt);

    start->prepare("select * from Wiadomosci;");

    start->exec();
    model->setQuery(*start);
    ui->tableView->setModel(model);

    connect.connectClose();
    qDebug()<<(model->rowCount());

    QSqlQueryModel * model1=new QSqlQueryModel();

    connect.connectOpen();
    QSqlQuery* start1=new QSqlQuery(connect.projekt);

    start1->prepare("select Imie, Nazwisko, Urodziny from Znajomi;");

    start1->exec();
    model1->setQuery(*start1);
    ui->tableView->setModel(model1);

    connect.connectClose();
    qDebug()<<(model1->rowCount());


}

/*Przypisywanie odpowiednim pól wartości z TableView*/
void Wiadomosci::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

    Login connect;
    if(!connect.connectOpen())
    {
        qDebug()<<"Wstąpił nieoczekiwany problem z odtworzeniem bazy danych";
        return;
    }

    connect.connectOpen();
    QSqlQuery start;
    start.prepare("select * from Wiadomosci where Imie='"+val+"' or Nazwisko='"+val+"' or Urodziny='"+val+"' or Wiadomosc='"+val+"'");

    if(start.exec())
    {
        while (start.next())
        {

            ui->lineEdit_firstname->setText(start.value(1).toString());
            ui->lineEdit_lastname->setText(start.value(2).toString());
            ui->lineEdit_comment->setText(start.value(3).toString());
        }
        connect.connectClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),start.lastError().text());
    }
}
