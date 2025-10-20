-- sqlite
PRAGMA foreign_keys = ON;

DROP TABLE IF EXISTS borrows;
DROP TABLE IF EXISTS readers;
DROP TABLE IF EXISTS books;

CREATE TABLE readers (
id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,
borrowed INTEGER DEFAULT 0 NOT NULL,
name VARCHAR(150) UNIQUE NOT NULL
);

CREATE TABLE books (
id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,
title VARCHAR(100) UNIQUE NOT NULL,
autor VARCHAR(150),
edition_date TEXT NOT NULL,
copies INTEGER DEFAULT 1 NOT NULL,
aivables INTEGER DEFAULT 1 NOT NULl
);

CREATE TABLE borrows (
id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,
reader_id INTEGER NOT NULL,
book_id INTEGER NOT NULL,
borrow_date TEXT NOT NULL,
return_date TEXT NOT NULL,
FOREIGN KEY (reader_id) REFERENCES readers (id),
FOREIGN KEY (book_id) REFERENCES books (id)
);

INSERT INTO readers(name)
VALUES ('memine'), ('rabe'), ('rakoto'), ('tay');

INSERT INTO books(title, autor, edition_date, copies, aivables)
VALUES ('kokokok', 'arara', '2000-3-13', 17, 17);
