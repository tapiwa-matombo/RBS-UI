#include "librariestreemodel.h"

LibrariesTreeModel::LibrariesTreeModel(QObject *parent)
    : QAbstractTableModel (parent)
{

}

int LibrariesTreeModel::rowCount(const QModelIndex & /*parent*/) const
{
    return 2;
}

int LibrariesTreeModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 1;
}

QVariant LibrariesTreeModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
           return QString("Row%1, Column%1").arg(index.row() + 1).arg(index.column());
    }
    return QVariant();
}

QVariant LibrariesTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0:
                return QString("Libraries");
        }
    }
    return QVariant();
}

void LibrariesTreeModel::getLibraryTree(QTreeView *tree)
{
    // Assign model for library tree view
    LibrariesTreeModel *model = new LibrariesTreeModel;
    tree->setModel(model);
}

