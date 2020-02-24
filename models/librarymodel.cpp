#include "librarymodel.h"

#include <QObject>
#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QTableView>


LibraryModel::LibraryModel(QObject *parent)
    :QAbstractTableModel (parent)
{
}

int LibraryModel::rowCount(const QModelIndex & /*parent*/) const
{
    return 2;
}

int LibraryModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;
}

QVariant LibraryModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        return QString("Row%1, Column%2")
                           .arg(index.row() + 1)
                           .arg(index.column() +1);
    }
    return QVariant();
}

QVariant LibraryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0:
                return QString("Track Title");
            case 1:
                return QString("Artist");
            case 2:
                return QString("Genre");
        }
    }
    return QVariant();
}

void LibraryModel::getLibrary(QTableView *libraryName)
{
    // Assign model for library
    LibraryModel *model = new LibraryModel;
    libraryName->setModel(model);
}


