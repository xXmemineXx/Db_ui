#include "database.h"

Database::Database(QObject *parent) : QObject(parent)
{
    initialize_database();
}

Database::~Database()
{
    if(my_database.isOpen()){
        my_database.close();
    }
}

bool Database::initialize_database()
{
    my_database = QSqlDatabase::addDatabase("QSQLITE");
    my_database.setDatabaseName("database.sqlite");

    if (!my_database.open()){
        qDebug() << "Error: failed to open database: " << my_database.lastError().text();
        return false;
    }else {
        qDebug() << "database opened successfully";
    }

    return execute_schema();
}

bool Database::execute_schema()
{
    QFile sqlFile(":/sql/database_schema.sql");
    if (!sqlFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Error : cannot open SQL file: " << sqlFile.errorString();
        return false;
    }

    QTextStream in(&sqlFile);
    QStringList statements;
    QString current_statement;

    while(!in.atEnd()){
        QString line = in.readLine().trimmed();

        if(line.isEmpty() || line.startsWith("--")){
            continue;
        }

        current_statement += line + " ";

        if(line.endsWith(';')){
            statements.append(current_statement.trimmed());
            current_statement.clear();
        }
    }

    sqlFile.close();

    QSqlQuery query;
    for(const QString &statement : statements){
        if(!query.exec(statement)){
            qDebug() << "Error executing SQL:" << query.lastError().text();
            qDebug() << "Failed statement:" << statement;
            return false;
        }
    }

    qDebug() << "database schema executed successfully";
    return true;
}

bool Database::insert_reader(const QString &name)
{
    if (!my_database.isOpen()){
        qDebug() << "database is not open";
        return false;
    }

    if(name.isEmpty()){
        qDebug() << "error name cannot be empty";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO readers(name) VALUES (:name)");
    query.bindValue(":name", name);

    if (!query.exec()){
        qDebug() << "failed to insert reader" << query.lastError().text();
        return false;
    }

    qDebug() << "user inserted successfully:" << name;
    return true;
}

bool Database::insert_book(QString &title, QString &autor, QString &edition, int &copies){
    if (!my_database.isOpen()){
        qDebug() << "database is not open";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO books(title, autor, edition_date, copies, aivables) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(title);
    query.addBindValue(autor);
    query.addBindValue(edition);
    query.addBindValue(copies);
    query.addBindValue(copies);

    if(!query.exec()){
        qDebug() << "failed to insert book" << query.lastError().text();
        return false;
    }

    qDebug() << "book inserted successfully";
    return true;
}

bool Database::insert_borrow_by_id(int &book_id, int &reader_id, QString &borrow_date, QString &return_date){
    if (!my_database.isOpen()){
        qDebug() << "database is not opened";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO borrows(book_id, reader_id, borrow_date, return_date) VALUES(?, ?, ?, ?)");
    query.addBindValue(book_id);
    query.addBindValue(reader_id);
    query.addBindValue(borrow_date);
    query.addBindValue(return_date);

    if (!query.exec()){
        qDebug() << "failed to link borrow link";
        return false;
    }

    qDebug() << "borrow linked successfully";
    return true;
}

int Database::get_reader_id(QString &name){
    int id = 0;
    QSqlQuery query;
    query.prepare("SELECT id FROM readers WHERE name = '?'");
    query.addBindValue(name);
    if (!query.exec() && query.next()){
        qDebug() << "unable to get reader id :" << query.lastError();
        return 0;
    }else{
        id = query.value("id").toInt();
        qDebug() << id << "id";
        return id;
    }
}

int Database::get_book_id(QString &title){
    int id = 0;
    QSqlQuery query;
    query.prepare("SELECT id FROM books WHERE title = '?';");
    query.addBindValue(title);
    if (!query.exec() && query.next()){
        qDebug() << "unable to get book id :" << query.lastError();
        return 0;
    }else{
        id = query.value("id").toInt();
        qDebug() << id << "id";
        return id;
    }
}

bool Database::is_aivable(int &book_id){
    if(!my_database.isOpen()){
        qDebug() << "the database is not opend";
        return false;
    }else{
        int borrowed = 0;

        QSqlQuery query1;
        query1.prepare("SELECT aivables FROM books WHERE id = ?");
        query1.addBindValue(book_id);
        if(!(query1.exec() && query1.next())){
            qDebug() << "error getting book information";
            return false;
        }else{
            borrowed = query1.value("aivables").toInt();
            qDebug() << "borrowed copies " << borrowed;
        }
        return borrowed > 0;
    }

}

bool Database::can_borrow(int &reader_id){
    if(!my_database.isOpen()){
        qDebug() << "the database is not opened";
        return false;
    }else{
        int actual = 0;

        QSqlQuery query;
        query.prepare("SELECT borrowed FROM readers WHERE id = ?");
        query.addBindValue(reader_id);
        if(!(query.exec() && query.next())){
            qDebug() << "error getting reader information :" << query.lastError();
            return false;
        } else{
            actual = query.value(0).toInt();
            qDebug() << "borrowed " << actual;
        }
        return actual <= 2;
    }
}

bool Database::update_book_on_insert_borrow(int &book_id){
    if(!my_database.isOpen()){
        qDebug() << "the database is not open";
        return false;
    }else {
        QSqlQuery query;


        query.prepare("UPDATE books SET aivables = aivables - 1 WHERE id = ?");
        query.addBindValue(book_id);
        if(!query.exec()){
            qDebug() << "error updating book informations" << query.lastError();
            return false;
        }else{
            qDebug() << "book informations updated successfully";
        }
        return true;
    }
}

bool Database::update_reader_on_insert_borrow(int &reader_id){
    if(!my_database.isOpen()){
        qDebug() << "the database is not open";
        return false;
    }else {
        QSqlQuery query;

        query.prepare("UPDATE readers SET borrowed = borrowed + 1 WHERE id = ?");
        query.addBindValue(reader_id);
        if(!query.exec()){
            qDebug() << "error updating reader informations" << query.lastError();
            return false;
        }else{
            qDebug() << "book informations updated successfully";
        }
        return true;
    }
}
