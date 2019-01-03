#ifndef LISTA_H
#define LISTA_H

#include <QDialog>
#include "login.h"

namespace Ui {
class Lista;
}

class Lista : public QDialog
{
    Q_OBJECT

public:
    explicit Lista(QWidget *parent = nullptr);
    ~Lista();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::Lista *ui;
};

#endif // LISTA_H

