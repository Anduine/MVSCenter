#ifndef REQUESTS_H
#define REQUESTS_H

#include <QDate>
#include <QString>
#include <vector>

struct UserRequest
{
    int id;
    QDate date;
    QString status;
    QString client_name;
    QString client_passportID;
    int client_phonenumber;
    int attempt_number;
};

class Requests
{
private:
    std::vector<UserRequest> request_list; 
public:
    Requests();

    void heapSortDate();
    void heapifyDate(std::vector<UserRequest>& array, int n, int index);
    void heapSortName();
    void heapifyName(std::vector<UserRequest>& array, int n, int index);

    void bubbleSortDate();
    void bubbleSortName();

    void selectionSortDate();
    void selectionSortName();

    void loadFromFile(QString filepath);
};

bool compareDate(const UserRequest &a, const UserRequest &b);
bool compareName(const UserRequest &a, const UserRequest &b);

#endif // REQUESTS_H
