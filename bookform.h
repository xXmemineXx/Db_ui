#ifndef BOOKFORM_H
#define BOOKFORM_H

#include <QWidget>
#include "database.h"

namespace Ui {
class BookForm;
}

class BookForm : public QWidget
{
    Q_OBJECT

public:
    explicit BookForm(QWidget *parent = nullptr);
    ~BookForm();
    void setCurrentTab(int index);
    void setDatabase(Database *db);

private slots:
    void on_book_edit_cancel_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::BookForm *ui;
    Database *database;
};

#endif // BOOKFORM_H
