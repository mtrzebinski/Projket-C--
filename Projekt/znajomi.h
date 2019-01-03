#ifndef ZNAJOMI_H
#define ZNAJOMI_H

#include <QDialog>
#include "login.h"

namespace Ui {
class Znajomi;
}

class Znajomi : public QDialog
{
    Q_OBJECT

public:
    explicit Znajomi(QWidget *parent = nullptr);
    ~Znajomi();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::Znajomi *ui;
};

#endif // ZNAJOMI_H
