#ifndef WIADOMOSCI_H
#define WIADOMOSCI_H

#include <QDialog>
#include "login.h"

namespace Ui {
class Wiadomosci;
}

class Wiadomosci : public QDialog
{
    Q_OBJECT

public:
    explicit Wiadomosci(QWidget *parent = nullptr);
    ~Wiadomosci();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::Wiadomosci *ui;
};

#endif // WIADOMOSCI_H
