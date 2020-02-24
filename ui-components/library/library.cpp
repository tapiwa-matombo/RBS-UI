#include "library.h"
#include "models/librarymodel.h"
#include "models/librariestreemodel.h"

#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>
#include <QDir>
#include <QDebug>


Library::Library(QObject *parent)
    :QObject (parent)
{

}

void Library::displayLibraryTree(QTreeView *tree)
{
    //set current folder
    LibrariesTreeModel *model = new LibrariesTreeModel;
    tree->setModel(model);
}

void Library::addLibrary(QTableView *tableView, QString &libraryName)
{
    //mkdir for library insert a new library name in table
    //if exists dont build dont add
    //call method to index music, sweepers, jingles, e.t.c collection
    //create a
    QDir dir;
    if (dir.exists(QDir::homePath() + "/Music/" + libraryName))
    {
        qDebug() << "Library with similar name already exists";
        //TODO: Message box to replace or abort or open
    }
    else if (dir.mkpath(QDir::homePath() + "/Music/" + libraryName))
    {
       qDebug() << QDir::homePath() + "/Music/" + libraryName;
       //TODO: Library is empty show empty table library
       showLibraryInTable(tableView);
    }
    else {
       qDebug() << "Some other error";
    }
}

void Library::showLibraryInTable(QTableView *tableView)
{
    //Get library name
    LibraryModel *model = new LibraryModel();
    model->getLibrary(tableView);
    //List the children of the library
    //get the list using a music library model
    //Get indexed list of music
    //Add to list view
}

