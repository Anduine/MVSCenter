#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include "requests.h"

#include <QDate>
#include <QFile>
#include <QString>

#include <vector>

struct UserData
{
    QString username;
    QString password;
    bool admin;
};

class Authorization
{
private:
    std::vector<UserData> userDatabase;
    Requests *requests;
public:
    Authorization();
    int login(QString username, QString password);
    std::vector<UserRequest> logout();

    bool loadFromFile(QString filepath);
};

#endif // AUTHORIZATION_H
