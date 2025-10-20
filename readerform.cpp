#include "readerform.h"
#include "ui_readerform.h"
#include "database.h"
#include <QDebug>
#include <QMessageBox>

ReaderForm::ReaderForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReaderForm)
    , database(nullptr)
{
    ui->setupUi(this);
}

ReaderForm::~ReaderForm()
{
    delete ui;
}

void ReaderForm::setCurrentTab(int index){
    if (index >= 0 && index < ui->tabWidget->count()){
        ui->tabWidget->setCurrentIndex(index);
    }
}

void ReaderForm::on_insert_reader_cancel_clicked()
{
    this->close();
}


void ReaderForm::on_reader_edit_cancel_clicked()
{
    this->close();
}

void ReaderForm::setDatabase(Database *db)
{
    database = db;

    if(database && database->isOpen()){
        ui->status_label->setText("database : connected");
        ui->status_label_edit->setText("database : connected");
        ui->status_label->setStyleSheet("color: green;");
        ui->status_label_edit->setStyleSheet("color: green;");
    }else{
        ui->status_label->setText("database : not connected");
        ui->status_label_edit->setText("database : not connected");
        ui->status_label->setStyleSheet("color: red;");
        ui->status_label_edit->setStyleSheet("color: red;");
    }
}


void ReaderForm::on_insert_reader_confirm_clicked()
{
    if (database && database->isOpen()){
        QString reader_name = ui->insert_reader_name_edit->text().trimmed();

        if (!reader_name.isEmpty()){
            if (database->insert_reader(reader_name)){
                QMessageBox::information(this, "success", "reader successfully insert in the database");
            }else{
                QMessageBox::information(this, "error", "unable to insert reader in the database");
            }
        }
    }else{
        QMessageBox::warning(this, "database error", "database unaivable");
    }
    ui->insert_reader_name_edit->clear();
}

