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

    void insertUser(UserRequest request);

    void heapSort(int sortMode);
    void heapify(std::vector<UserRequest> &array, int n, int index, int sortMode);

    void bubbleSort(int sortMode);
    void selectionSort(int sortMode);


    void loadFromFile(QString filepath);

    int size();

    UserRequest &operator[](const int index);
};

bool compare(const UserRequest &a, const UserRequest &b, int index);


#endif // REQUESTS_H
