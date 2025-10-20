#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "readerform.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_database(new Database(this))
    , m_bookform(nullptr)
    , m_borrowform(nullptr)
    , m_readerform(nullptr)
{
    ui->setupUi(this);

    refresh_readers();
    refresh_books();

    QTimer *refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, &MainWindow::refresh_readers);
    connect(refreshTimer, &QTimer::timeout, this, &MainWindow::refresh_books);
    refreshTimer->start(2000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_home_add_reader_clicked()
{
    if (!m_readerform){
        m_readerform = new ReaderForm(this);
        m_readerform->setDatabase(m_database);
    }

    m_readerform->setWindowTitle("reader");
    m_readerform->ReaderForm::setCurrentTab(0);
    m_readerform->show();
    refresh_readers();
}

void MainWindow::on_reader_table_add_clicked()
{
    if (!m_readerform){
        m_readerform = new ReaderForm(this);
        m_readerform->setDatabase(m_database);
    }

    m_readerform->setWindowTitle("reader");
    m_readerform->ReaderForm::setCurrentTab(0);
    m_readerform->show();
}

void MainWindow::on_reader_table_edit_btn_clicked()
{
    if (!m_readerform){
        m_readerform = new ReaderForm(this);
        m_readerform->setDatabase(m_database);
    }

    m_readerform->setWindowTitle("reader");
    m_readerform->ReaderForm::setCurrentTab(1);
    m_readerform->show();
}

void MainWindow::on_home_edit_reader_clicked()
{
    if (!m_readerform){
        m_readerform = new ReaderForm(this);
        m_readerform->setDatabase(m_database);
    }

    m_readerform->setWindowTitle("reader");
    m_readerform->ReaderForm::setCurrentTab(1);
    m_readerform->show();
}

void MainWindow::on_home_delete_reader_clicked()
{
    ui->main_container->setCurrentIndex(1);
}

void MainWindow::on_home_add_book_clicked()
{
    if (!m_bookform){
        m_bookform = new BookForm(this);
        m_bookform->setDatabase(m_database);
    }

    m_bookform->setWindowTitle("books");
    m_bookform->BookForm::setCurrentTab(0);
    m_bookform->show();
}

void MainWindow::on_book_table_add_btn_clicked()
{
    if (!m_bookform){
        m_bookform = new BookForm(this);
        m_bookform->setDatabase(m_database);
    }

    m_bookform->setWindowTitle("books");
    m_bookform->BookForm::setCurrentTab(0);
    m_bookform->show();
}

void MainWindow::on_home_edit_book_clicked()
{
    if (!m_bookform){
        m_bookform = new BookForm(this);
        m_bookform->setDatabase(m_database);
    }

    m_bookform->setWindowTitle("books");
    m_bookform->BookForm::setCurrentTab(1);
    m_bookform->show();
}

void MainWindow::on_book_table_edit_btn_clicked()
{
    if (!m_bookform){
        m_bookform = new BookForm(this);
        m_bookform->setDatabase(m_database);
    }

    m_bookform->setWindowTitle("books");
    m_bookform->BookForm::setCurrentTab(1);
    m_bookform->show();
}


void MainWindow::on_home_delete_book_clicked()
{
    ui->main_container->setCurrentIndex(2);
}

void MainWindow::on_home_add_borrow_clicked()
{
    if (!m_borrowform){
        m_borrowform = new BorrowForm(this);
        m_borrowform->setDatabase(m_database);
    }

    m_borrowform->setWindowTitle("borrows");
    m_borrowform->BorrowForm::setCurrentTab(0);
    m_borrowform->show();
}

void MainWindow::on_borrow_table_add_btn_clicked()
{
    if (!m_borrowform){
        m_borrowform = new BorrowForm(this);
        m_borrowform->setDatabase(m_database);
    }

    m_borrowform->setWindowTitle("borrows");
    m_borrowform->BorrowForm::setCurrentTab(0);
    m_borrowform->show();
}

void MainWindow::on_home_edit_borrow_clicked()
{
    if (!m_borrowform){
        m_borrowform = new BorrowForm(this);
        m_borrowform->setDatabase(m_database);
    }

    m_borrowform->setWindowTitle("borrows");
    m_borrowform->BorrowForm::setCurrentTab(1);
    m_borrowform->show();
}

void MainWindow::on_borrow_table_edit_btn_clicked()
{
    if (!m_borrowform){
        m_borrowform = new BorrowForm(this);
        m_borrowform->setDatabase(m_database);
    }

    m_borrowform->setWindowTitle("borrows");
    m_borrowform->BorrowForm::setCurrentTab(1);
    m_borrowform->show();
}

void MainWindow::on_home_delete_borrows_clicked()
{
    ui->main_container->setCurrentIndex(3);
}

void MainWindow::refresh_readers(){
    if (!m_database->isOpen()) return;
    QString name_search = ui->user_search_edit->text().trimmed();

    if (name_search.isEmpty()){
        QSqlQuery query("SELECT id, name FROM readers");

        ui->reader_table->setRowCount(0);

        int row = 0;
        while (query.next()) {
            ui->reader_table->insertRow(row);

            ui->reader_table->setItem(row, 0, new QTableWidgetItem(query.value("id").toString()));
            ui->reader_table->setItem(row, 1, new QTableWidgetItem(query.value("name").toString()));

            row++;
        }
    } else{
        QSqlQuery query1;
        query1.prepare("SELECT id, name FROM readers WHERE name LIKE '%?%'");
        query1.addBindValue(name_search);
        ui->reader_table->clear();
        ui->reader_table->setRowCount(0);
        qDebug() << query1.lastError();

        int row = 0;
        while (query1.next()) {
            ui->reader_table->insertRow(row);

            ui->reader_table->setItem(row, 0, new QTableWidgetItem(query1.value("id").toString()));
            ui->reader_table->setItem(row, 1, new QTableWidgetItem(query1.value("name").toString()));

            row++;
        }
    }

}

void MainWindow::refresh_books(){
    if (!m_database->isOpen()) return;
    QSqlQuery query("SELECT b.id, b.title, b.autor, b.edition_date, b.copies, b.aivables FROM books b");

    ui->book_table->setRowCount(0);

    int row = 0;
    while (query.next()){
        ui->book_table->insertRow(row);

        ui->book_table->setItem(row, 0, new QTableWidgetItem(query.value("id").toString()));
        ui->book_table->setItem(row, 1, new QTableWidgetItem(query.value("title").toString()));
        ui->book_table->setItem(row, 2, new QTableWidgetItem(query.value("autor").toString()));
        ui->book_table->setItem(row, 3, new QTableWidgetItem(query.value("edition_date").toString()));
        ui->book_table->setItem(row, 4, new QTableWidgetItem(query.value("copies").toString()));
        ui->book_table->setItem(row, 5, new QTableWidgetItem(query.value("aivables").toString()));

        row++;
    }
}

