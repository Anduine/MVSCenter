#include "auth_window.h"
#include "main_window.h"
#include "user_window.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "MVSCenter_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow *main_window;
    // w.show();
    UserWindow *user_window;

    AuthWindow auth_window(main_window, user_window);
    auth_window.show();

    return a.exec();
}
