#include "authorization.h"

#include <QDate>
#include <QFile>
#include <QString>

#include <vector>

Authorization::Authorization()
{
    loadFromFile("reg.txt");
}

int Authorization::login(QString username, QString password)
{
    //const std::vector<UserRequest>& requests_list = requests->getList();
    for (const UserData& user : userDatabase) {
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
    return 0;
    //return filter(requests_list, username);
}

std::vector<UserRequest> Authorization::logout()
{
    std::vector<UserRequest> emptyList;
    return emptyList;
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
            QString userInfo = in.readLine();
            QStringList parts = userInfo.split("$");
            UserData user;
            // дані в форматі username$password$admin/user
            user.username = parts[0];
            user.password = parts[1];
            user.admin = (parts[2] == "admin");
            userDatabase.push_back(user);
        }
        file.close();
        qDebug() << "Інформація є";
        return true;
    }
}
