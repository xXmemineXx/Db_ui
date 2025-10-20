#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "database.h"
#include "borrowform.h"
#include "bookform.h"
#include "readerform.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void refresh_readers();
    void refresh_books();

    void on_home_add_reader_clicked();

    void on_home_add_book_clicked();

    void on_home_edit_reader_clicked();

    void on_home_edit_book_clicked();

    void on_home_add_borrow_clicked();

    void on_home_edit_borrow_clicked();

    void on_home_delete_reader_clicked();

    void on_home_delete_book_clicked();

    void on_home_delete_borrows_clicked();

    void on_reader_table_edit_btn_clicked();

    void on_reader_table_add_clicked();

    void on_book_table_edit_btn_clicked();

    void on_book_table_add_btn_clicked();

    void on_borrow_table_edit_btn_clicked();

    void on_borrow_table_add_btn_clicked();

private:
    Ui::MainWindow *ui;

    Database *m_database;
    BookForm *m_bookform;
    ReaderForm *m_readerform;
    BorrowForm *m_borrowform;
};
#endif // MAINWINDOW_H
