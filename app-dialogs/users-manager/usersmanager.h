#ifndef USERSMANAGER_H
#define USERSMANAGER_H

#include <QWidget>

namespace Ui {
class UsersManager;
}

class UsersManager : public QWidget
{
    Q_OBJECT

public:
    explicit UsersManager(QWidget *parent = nullptr);
    ~UsersManager();

private:
    Ui::UsersManager *ui;
};

#endif // USERSMANAGER_H
