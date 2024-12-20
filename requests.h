#ifndef REQUESTS_H
#define REQUESTS_H

#include <QDate>
#include <QString>
#include <QSet>

#include <vector>

struct UserRequest
{
    int id;
    QDateTime date;
    QString status;
    QString ticket_type;
    QString client_name;
    QString client_passportID;
    qint64 client_phonenumber;
    int attempt_number;
};

class Requests
{
private:
    std::vector<UserRequest> request_list;

public:
    Requests();
    Requests(QString filepath);

    void insertUser(UserRequest request);

    void heapSort(int sort_mode);
    void heapify(std::vector<UserRequest> &array, int n, int index, int sort_mode);

    void bubbleSort(int sort_mode);
    void selectionSort(int sort_mode);

    bool loadFromFile(QString filepath);

    int size();
    void clear();

    UserRequest &operator[](const int index);
    bool compare(const UserRequest &a, const UserRequest &b, int index);

    const std::vector<UserRequest>& getList() const;
    const std::vector<UserRequest> getInfoUser(const QString& username) const;
    QSet<QTime> getOccupiedTimes(const QDate& date) const;
};

#endif // REQUESTS_H
