#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>

#include "../treeitem.h"

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

    public:
        explicit TreeModel(const QString &data, QObject *parent = nullptr);


        // Header:
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        // Basic functionality:
        QModelIndex index(int row, int column,
                          const QModelIndex &parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex &index) const override;

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;

        // Fetch data dynamically:
        bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;

        bool canFetchMore(const QModelIndex &parent) const override;
        void fetchMore(const QModelIndex &parent) override;

        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    private:
        void setupModelData(const QStringList &lines, TreeItem *parent);

         TreeItem *rootItem;
};

#endif // TREEMODEL_H
