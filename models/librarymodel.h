#ifndef LIBRARYMODEL_H
#define LIBRARYMODEL_H

#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlError>
#include <QSqlQuery>

/*
  Item data handling functions: enable views and delegates
  1. Query dimensions of the model
  2. Examine items
  3. Retrieve data
  Navigation and index creation
  1. navigating the tree like structure provided by the model
  2. Obtain model indexes for items
  Drag and drop support and MIME type handling
  1. Decribe data items in ways that other components understand
*/
class LibraryModel: public QAbstractTableModel
{
    Q_OBJECT

    public:
         LibraryModel(QObject *parent = nullptr);

         int rowCount(const QModelIndex &parent = QModelIndex()) const override;
         int columnCount(const QModelIndex &parent = QModelIndex()) const override;
         QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
         QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
         /*QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const override;
         Qt::ItemFlags flags(const QModelIndex &index) const override;
         bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole) override;
         bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
         bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;*/

    public slots:

         void getLibrary(QTableView *libraryName);

};

#endif // LIBRARYMODEL_H
