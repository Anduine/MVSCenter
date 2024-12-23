#include "authorization.h"

#include <QDate>
#include <QFile>
#include <QString>

#include <vector>

Authorization::Authorization()
{
    loadFromFile("reg.txt");
}

int Authorization::login(QString &username, QString &password)
{
    for (const UserData& user : user_database) {
        if (user.username == username && user.password == password) {
            if (user.admin) {
                return 2;
            }
            else
            {
                return 1;
            }
        }
    }
    return 0; // 0 - нема; 1 - користувач; 2 - адмін
}

bool Authorization::loadFromFile(QString filepath)
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "File error: " << file.error();
        return false;
    }
    else {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString user_info = in.readLine();
            QStringList parts = user_info.split("$");
            UserData user;
            // дані в форматі username$password$admin/user
            user.username = parts[0];
            user.password = parts[1];
            user.admin = (parts[2] == "admin");
            user_database.push_back(user);
        }
        file.close();
        return true;
    }
}
