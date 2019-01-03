#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    // Łączenie z bazą danych
    Login connect;
}

Menu::~Menu()
{
    delete ui;
}

// Przycisk do sekcji listy osób w serwisie
void Menu::on_pushButton_clicked()
{
    Lista lista;
    lista.setModal(true);
    lista.exec();
}

// Przycisk do sekcji znajomych w serwisie
void Menu::on_pushButton_2_clicked()
{
    Znajomi znajomi;
    znajomi.setModal(true);
    znajomi.exec();
}


