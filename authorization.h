#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QString>

#include <vector>

class Authorization
{
private:
    struct UserData
    {
        QString username;
        QString password;
        bool admin;
    };

    std::vector<UserData> user_database;
public:
    Authorization();

    int login(QString &username, QString &password);

    bool loadFromFile(QString filepath);
};

#endif // AUTHORIZATION_H
