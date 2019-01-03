#include "lista.h"
#include "ui_lista.h"
#include "QMessageBox"

Lista::Lista(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lista)
{
    ui->setupUi(this);

    // Łączenie z bazą danych
    Login connect;

}

Lista::~Lista()
{
    delete ui;
}

// Przycisku do wyszukiwania osoby na liście
void Lista::on_pushButton_clicked()
{
    Login connect;
    QSqlQueryModel * model=new QSqlQueryModel();

    connect.connectOpen();
    QSqlQuery* pocz=new QSqlQuery(connect.projekt);
    QString firstname,lastname,birth_date,interests;
    firstname=ui->lineEdit_firstname->text();
    lastname=ui->lineEdit_lastname->text();
    birth_date=ui->lineEdit_birth_date->text();
    interests=ui->lineEdit_interests->text();

    pocz->prepare("SELECT*FROM Lista WHERE Imie='"+firstname+"' OR Nazwisko='"+lastname+"' OR Urodziny='"+birth_date+"' OR Zainteresowania='"+interests+"';");

    pocz->exec();
    model->setQuery(*pocz);
    ui->tableView->setModel(model);

    connect.connectClose();
    qDebug()<<(model->rowCount());
}


// Przycisk łądujący tabelę
void Lista::on_pushButton_2_clicked()
{
    Login connect;
    QSqlQueryModel * model=new QSqlQueryModel();

    connect.connectOpen();
    QSqlQuery* pocz=new QSqlQuery(connect.projekt);

    pocz->prepare("SELECT*FROM Lista;");

    pocz->exec();
    model->setQuery(*pocz);
    ui->tableView->setModel(model);

    connect.connectClose();
    qDebug()<<(model->rowCount());
}

void Lista::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

    Login connect;

    connect.connectOpen();
    QSqlQuery pocz;
    pocz.prepare("SELECT*FROM Lista WHERE Imie='"+val+"' OR Nazwisko='"+val+"' OR Urodziny='"+val+"' OR Zainteresowania='"+val+"';");

    if(pocz.exec())
    {
        while (pocz.next())
        {
            ui->lineEdit_firstname->setText(pocz.value(1).toString());
            ui->lineEdit_lastname->setText(pocz.value(2).toString());
            ui->lineEdit_birth_date->setText(pocz.value(3).toString());
            ui->lineEdit_interests->setText(pocz.value(4).toString());
        }
        connect.connectClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),pocz.lastError().text());
    }
}
