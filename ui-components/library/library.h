#ifndef LIBRARY_H
#define LIBRARY_H

#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>

#include "models/librarymodel.h"
#include "models/librariestreemodel.h"

class LibraryModel;

class LibrariesTreeModel;

class Library: public QObject
{
    Q_OBJECT

    public:
        Library(QObject *parent = nullptr);

    public slots:
        void displayLibraryTree(QTreeView *tree);
        void addLibrary(QTableView *tableView, QString &libraryName);
        void showLibraryInTable(QTableView *libraryName);
};

#endif // LIBRARY_H
