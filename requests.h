#ifndef REQUESTS_H
#define REQUESTS_H

#include <QDate>
#include <QString>
#include <vector>

struct UserRequest{
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

    void heapSort();
    void heapify(int heap_size, int cur_index);

    void bubbleSort();
    void selectionSort();

    void loadFromFile(QString filepath);
};

#endif // REQUESTS_H
