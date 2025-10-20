#include "bookform.h"
#include "ui_bookform.h"

#include <QMessageBox>

BookForm::BookForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BookForm)
    , database(nullptr)
{
    ui->setupUi(this);
}

BookForm::~BookForm()
{
    delete ui;
}

void BookForm::setCurrentTab(int index){
    if (index >= 0 && index < ui->tabWidget->count()){
        ui->tabWidget->setCurrentIndex(index);
    }
}

void BookForm::on_book_edit_cancel_clicked()
{
    this->close();
}


void BookForm::on_pushButton_clicked()
{
    this->close();
}

void BookForm::setDatabase(Database *db){
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

void BookForm::on_pushButton_2_clicked()
{
    if (database && database->isOpen()){
        QString title = ui->new_book_title->text().trimmed();
        QString autor = ui->new_book_autor->text().trimmed();
        QString edition = ui->new_book_edition->text().trimmed();
        int copies = ui->new_book_copies->value();

        if(!title.isEmpty()){
            if(database->insert_book(title, autor, edition, copies)){
                QMessageBox::information(this, "success", "book successfully inserted in database");
            }else{
                QMessageBox::information(this, "error", "unable to insert book in database");
            }

        }else{
            QMessageBox::warning(this, "error", "book title cannot be empty");
        }

    }else{
        QMessageBox::warning(this, "database error", "unable to connect database");
    }
}

