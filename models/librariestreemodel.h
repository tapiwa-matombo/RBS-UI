#ifndef LIBRARIESTREEMODEL_H
#define LIBRARIESTREEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QTreeView>

class LibrariesTreeModel: public QAbstractTableModel
{
    Q_OBJECT

    public:
        LibrariesTreeModel(QObject *parent = nullptr);
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    public slots:
        void getLibraryTree(QTreeView *tree);
};

#endif // LIBRARIESTREEMODEL_H
