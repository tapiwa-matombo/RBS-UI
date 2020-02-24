#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QWidget>

namespace Ui {
class SettingsManager;
}

class SettingsManager : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsManager(QWidget *parent = nullptr);
    ~SettingsManager();

private:
    Ui::SettingsManager *ui;
};

#endif // SETTINGSMANAGER_H
