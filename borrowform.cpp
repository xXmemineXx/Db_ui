#include "borrowform.h"
#include "ui_borrowform.h"

#include <QMessageBox>

BorrowForm::BorrowForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BorrowForm)
    , database(nullptr)
{
    ui->setupUi(this);
}

BorrowForm::~BorrowForm()
{
    delete ui;
}

void BorrowForm::setCurrentTab(int index){
    if (index >= 0 && index < ui->tabWidget->count()){
        ui->tabWidget->setCurrentIndex(index);
    }
}

void BorrowForm::on_insert_borrow_cancel_clicked()
{
    this->close();
}


void BorrowForm::on_edited_borrow_cancel_clicked()
{
    this->close();
}

void BorrowForm::setDatabase(Database *db){
    database = db;
    if(database && database->isOpen()){
        ui->insert_status->setText("database : connected");
        ui->edit_status->setText("database : connected");
        ui->insert_status->setStyleSheet("color: green;");
        ui->edit_status->setStyleSheet("color: green;");
    }else{
        ui->insert_status->setText("database : not connected");
        ui->edit_status->setText("database : not connected");
        ui->insert_status->setStyleSheet("color: red;");
        ui->edit_status->setStyleSheet("color: red;");
    }
}

void BorrowForm::on_insert_borro_confirm_clicked()
{
    if(database && database->isOpen()){
        int book_id = ui->new_book_id->value();
        int reader_id = ui->new_reader_id->value();
        QString book_title = ui->new_book_title->text().trimmed();
        QString reader_name = ui->new_reader_name->text().trimmed();
        QDate borrow_date = ui->new_borrow_date->date();
        QDate return_date = ui->new_return_date->date();
        QString b_date = ui->new_borrow_date->text().trimmed();
        QString r_date = ui->new_return_date->text().trimmed();

        if (borrow_date < return_date){
            if(book_title.isEmpty() && reader_name.isEmpty()){
                if(!(database->is_aivable(book_id)
                    && database->can_borrow(reader_id))){
                    QMessageBox::information(this, "error", "wether the reader cannot borrow or the has no more copies");
                }else{
                    if(!(database->insert_borrow_by_id(book_id, reader_id, b_date, r_date)
                        && database->update_book_on_insert_borrow(book_id)
                        && database->update_reader_on_insert_borrow(reader_id))){
                        QMessageBox::information(this, "error", "cannot insert link to database");
                    }else{
                        QMessageBox::information(this, "success", "link inserted successfully");
                    }
                }
            }else{
                book_id = database->get_book_id(book_title);
                reader_id = database->get_reader_id(reader_name);

                if(!(database->insert_borrow_by_id(book_id, reader_id, b_date, r_date)
                      && database->update_book_on_insert_borrow(book_id)
                      && database->update_reader_on_insert_borrow(reader_id))){
                    QMessageBox::information(this, "error", "cannot insert link to database");
                }else{
                    QMessageBox::information(this, "success", "link inserted successfully");
                }
            }
        }else {
            QMessageBox::information(this, "error", "borrow_date cannot be later than return date");
        }

    }else{
        QMessageBox::warning(this, "error", "could not connect to database");
    }
}

