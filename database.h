#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    bool initialize_database();
    bool insert_reader(const QString &name);
    bool insert_book(QString &title, QString &autor,QString &edition, int &copies);
    bool insert_borrow_by_id(int &book_id, int &reader_id, QString &borrow_date, QString &return_date);

    bool is_aivable(int &book_id);
    bool can_borrow(int &reader_id);
    bool update_book_on_insert_borrow(int &book_id);
    bool update_reader_on_insert_borrow(int &reader_id);

    int get_reader_id(QString &name);
    int get_book_id(QString &title);

    bool isOpen() const {return my_database.isOpen();}

private:
    bool execute_schema();
    QSqlDatabase my_database;
};

#endif // DATABASE_H
