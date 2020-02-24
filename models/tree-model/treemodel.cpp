#include "treemodel.h"

TreeModel::TreeModel(const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    rootItem = new TreeItem({tr("Title"), tr("Summary")});
    setupModelData(data.split('\n'), rootItem);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
            return rootItem->data(section);

        return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
            return QModelIndex();

        TreeItem *parentItem;

        if (!parent.isValid())
            parentItem = rootItem;
        else
            parentItem = static_cast<TreeItem*>(parent.internalPointer());

        TreeItem *childItem = parentItem->child(row);
        if (childItem)
            return createIndex(row, column, childItem);
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
            return QModelIndex();

        TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
        TreeItem *parentItem = childItem->parentItem();

        if (parentItem == rootItem)
            return QModelIndex();

        return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
            return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
        return rootItem->columnCount();
}

bool TreeModel::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    if (parent.isValid())
        return true;
    return false;
}

bool TreeModel::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    if (parent.isValid())
        return true;
    return false;
}

void TreeModel::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
    parent.data();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent)
{
    QVector<TreeItem*> parents;
        QVector<int> indentations;
        parents << parent;
        indentations << 0;

        int number = 0;

        while (number < lines.count()) {
            int position = 0;
            while (position < lines[number].length()) {
                if (lines[number].at(position) != ' ')
                    break;
                position++;
            }

            const QString lineData = lines[number].mid(position).trimmed();

            if (!lineData.isEmpty()) {
                // Read the column data from the rest of the line.
                const QStringList columnStrings = lineData.split('\t', QString::SkipEmptyParts);
                QVector<QVariant> columnData;
                columnData.reserve(columnStrings.count());
                for (const QString &columnString : columnStrings)
                    columnData << columnString;

                if (position > indentations.last()) {
                    // The last child of the current parent is now the new parent
                    // unless the current parent has no children.

                    if (parents.last()->childCount() > 0) {
                        parents << parents.last()->child(parents.last()->childCount()-1);
                        indentations << position;
                    }
                } else {
                    while (position < indentations.last() && parents.count() > 0) {
                        parents.pop_back();
                        indentations.pop_back();
                    }
                }

                // Append a new item to the current parent's list of children.
                parents.last()->appendChild(new TreeItem(columnData, parents.last()));
            }
            ++number;
        }
}