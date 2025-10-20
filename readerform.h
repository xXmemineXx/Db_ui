#ifndef READERFORM_H
#define READERFORM_H

#include <QWidget>
#include "database.h"

namespace Ui {
class ReaderForm;
}

class ReaderForm : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderForm(QWidget *parent = nullptr);
    ~ReaderForm();
    void setCurrentTab(int index);
    void setDatabase(Database *db);

private slots:
    void on_insert_reader_cancel_clicked();

    void on_reader_edit_cancel_clicked();

    void on_insert_reader_confirm_clicked();

private:
    Ui::ReaderForm *ui;
    Database *database;
};

#endif // READERFORM_H
