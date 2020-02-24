#include "rbs.h"
#include "players/player.h"
#include "db/dba.h"
#include "app-dialogs/playlist-manager/playlistmanager.h"
//#include "pythonhandler.h"
//#include "pythoncontroller.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDesktopWidget>
#include <QFile>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QSettings>
#include <QIcon>
#include <QDir>
#include <QUrl>

#include <stdlib.h>

//! [0]
static bool associateFileTypes()
{
    QString displayName = QGuiApplication::applicationDisplayName();
    QString filePath = QCoreApplication::applicationFilePath();
    QString fileName = QFileInfo(filePath).fileName();

    const QString key = QStringLiteral("HKEY_CURRENT_USER\\Software\\Classes\\Applications\\") + fileName;
    QSettings settings(key, QSettings::NativeFormat);
    if (settings.status() != QSettings::NoError) {
        qWarning() << "Cannot access registry key" << key;
        return false;
    }
    settings.setValue(QStringLiteral("FriendlyAppName"), displayName);

    settings.beginGroup(QStringLiteral("SupportedTypes"));
    QMimeDatabase mimeDatabase;
    const QStringList supportedMimeTypes = Player::supportedMimeTypes();
    for (const QString &fileType : supportedMimeTypes) {
        const QStringList suffixes = mimeDatabase.mimeTypeForName(fileType).suffixes();
        for (QString suffix : suffixes) {
            suffix.prepend('.');
            settings.setValue(suffix, QString());
        }
    }
    settings.endGroup();

    settings.beginGroup(QStringLiteral("shell"));
    settings.beginGroup(QStringLiteral("open"));
    settings.setValue(QStringLiteral("FriendlyAppName"), displayName);
    settings.beginGroup(QStringLiteral("Command"));
    settings.setValue(QStringLiteral("."),
                      QLatin1Char('"') + QDir::toNativeSeparators(filePath) + QStringLiteral("\" \"%1\""));

    return true;
}
//! [0]

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    if (!associateFileTypes())
        return -1;

    rbs w;
    w.setLibraryWidget();
    w.show();

//    QCommandLineOption pylocation("f", "Location of the python file", "Path");

//    QCommandLineParser parser;

//        if ( parser.isSet(pylocation) ) {
//            QString pyfile = parser.value(pylocation);
//            // the Python controller
//            PythonController pycontroller;
//            // the Python handler
//            PythonHandler pyhandler;
//            // Connecting to the onMessage signal of PythonHandler
//            QObject::connect(&pyhandler, &PythonHandler::onMessage, [&](const QString& msg) {
//              qDebug() << "main debug callback" << msg;
//            });
//            // Connecting to the pythonError signal of PythonController
//            QObject::connect(&pycontroller, &PythonController::pythonError, [&](const QString& error) {
//              qDebug() << "pythonError:" << error;
//            });

//            // load the python file
//            pycontroller.load(pyfile);
//            // call the python method "initialize"
//            pycontroller.pyInitialize(&pyhandler);
//        }

    return app.exec();
}
