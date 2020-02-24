#ifndef DBA_H
#define DBA_H

#include <QtSql>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDriver>

class DBA: public QObject
{
    Q_OBJECT
    public:
        DBA(QObject *parent);

        QString default_driver = "QSQLITE";
        QString default_dbname = "libraries.db";
        bool isActive = false;

    public slots:
        QSqlError initDb();
        bool insert(QString &q);
        bool remove(QString &q);
        bool update(QString &q);

    private slots:
        QList<QString> tables();
        bool createMetaDataTable(QString q);
};

#endif // DBA_H
