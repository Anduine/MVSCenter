#include "requests.h"

#include <QDate>
#include <QFile>
#include <QString>

#include <vector>

Requests::Requests() {}

Requests::Requests(QString filepath)
{
    loadFromFile(filepath);
}

void Requests::insertUser(UserRequest request)
{
    request.id = request_list.size();
    request_list.push_back(request);
}

bool Requests::loadFromFile(QString filepath)
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

            if (parts.size() < 8) {
                qDebug() << "Invalid line format: " << userInfo;
                //continue;
            }

            UserRequest userStruct;

            // дані в форматі id$date(27.10.2024 12:15)$status$type$client_name$client_passportID$client_phonenumber$attempt_number
            userStruct.id = parts[0].toInt();
            userStruct.date = QDateTime::fromString(parts[1], "dd.MM.yyyy hh:mm");
            // if (!userStruct.date.isValid()) {
            //     qDebug() << "Invalid date format: " << parts[1];
            //     continue;
            // }
            userStruct.status = parts[2];
            userStruct.ticket_type = parts[3];
            userStruct.client_name = parts[4];
            userStruct.client_passportID = parts[5];
            userStruct.client_phonenumber = parts[6].toLongLong();
            userStruct.attempt_number = parts[7].toInt();

            request_list.push_back(userStruct);
        }
        file.close();
        return true;
    }
}

void Requests::bubbleSort(int sort_mode)
{
    int n = request_list.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (compare(request_list[j], request_list[j + 1], sort_mode)) {
                std::swap(request_list[j], request_list[j + 1]);
            }
        }
    }
}

void Requests::selectionSort(int sort_mode)
{
    int n = request_list.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_i = i;
        for (int j = i + 1; j < n; ++j) {
            if (!compare(request_list[j], request_list[min_i], sort_mode)) {
                min_i = j;
            }
        }
        std::swap(request_list[i], request_list[min_i]);
    }
}

void Requests::heapSort(int sort_mode)
{
    int n = request_list.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(request_list, n, i, sort_mode);

    for (int i = n - 1; i > 0; i--) {
        std::swap(request_list[0], request_list[i]);
        heapify(request_list, i, 0, sort_mode);
    }
}
void Requests::heapify(std::vector<UserRequest> &array, int n, int i, int sort_mode)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && compare(array[left], array[largest], sort_mode))
        largest = left;
    if (right < n && compare(array[right], array[largest], sort_mode))
        largest = right;
    if (largest != i) {
        std::swap(array[i], array[largest]);
        heapify(array, n, largest, sort_mode);
    }
}

int Requests::size()
{
    return request_list.size();
}

void Requests::clear()
{
    request_list.clear();
}

std::vector<UserRequest>& Requests::getList(){
    return request_list;
}

const std::vector<UserRequest> Requests::getInfoUser(const QString& username) const {
    std::vector<UserRequest> filteredData;
    for (const UserRequest& request : request_list) {
        if (request.client_name == username) {
            filteredData.push_back(request);
        }
    }

    return filteredData;
}

QSet<QTime> Requests::getOccupiedTimes(const QDate &date) const
{
    QSet<QTime> occupiedTimes;
    for (const auto& request : request_list) {
        if (request.date.date() == date) {
            occupiedTimes.insert(request.date.time());
        }
    }
    return occupiedTimes;
}

UserRequest &Requests::operator[](const int index)
{
    return request_list[index];
}

bool Requests::compare(const UserRequest &a, const UserRequest &b, int index)
{
    switch (index) {
    case 0:
        return a.id > b.id;
    case 1:
        return a.client_name > b.client_name;
    case 2:
        return a.status > b.status;
    case 3:
        return a.ticket_type > b.ticket_type;
    case 4:
        return a.client_passportID > b.client_passportID;
    case 5:
        return a.client_phonenumber > b.client_phonenumber;
    case 6:
        return a.date > b.date;
    case 7:
        return a.attempt_number > b.attempt_number;
    default:
        return false;
    }
}


