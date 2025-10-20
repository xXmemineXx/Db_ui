#ifndef BORROWFORM_H
#define BORROWFORM_H

#include <QWidget>
#include "database.h"

namespace Ui {
class BorrowForm;
}

class BorrowForm : public QWidget
{
    Q_OBJECT

public:
    explicit BorrowForm(QWidget *parent = nullptr);
    ~BorrowForm();
    void setCurrentTab(int index);
    void setDatabase(Database *db);

private slots:
    void on_insert_borrow_cancel_clicked();

    void on_edited_borrow_cancel_clicked();

    void on_insert_borro_confirm_clicked();

private:
    Ui::BorrowForm *ui;
    Database *database;
};

#endif // BORROWFORM_H
