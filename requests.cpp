#include "requests.h"

#include <QDate>
#include <QFile>
#include <QString>

#include <vector>

using namespace std;

Requests::Requests() {}

void Requests::insertUser(UserRequest request)
{
    request.id = request_list.size();
    request_list.push_back(request);
}

void Requests::loadFromFile(QString filepath)
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "File error: " << file.error();
    } else {
        //vector<UserRequest> request_list;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString callerInfo = in.readLine();
            QStringList parts = callerInfo.split("$");
            UserRequest callerStruct;

            // дані в форматі id$date$status$client_name$client_passportID$client_phonenumber$attempt_number ???
            callerStruct.id = parts[0].toInt();
            callerStruct.date = QDate::fromString(parts[1], "yyyy-MM-dd");
            callerStruct.status = parts[2];
            callerStruct.client_name = parts[3];
            callerStruct.client_passportID = parts[4];
            callerStruct.client_phonenumber = parts[5].toLongLong();
            callerStruct.attempt_number = parts[6].toInt();

            request_list.push_back(callerStruct);
        }
        file.close();
    }
}

void Requests::bubbleSort(int sort_mode)
{
    int n = request_list.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (compare(request_list[j], request_list[j + 1], sort_mode)) {
                swap(request_list[j], request_list[j + 1]);
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
            if (compare(request_list[j], request_list[min_i], sort_mode)) {
                min_i = j;
            }
        }
        swap(request_list[i], request_list[min_i]);
    }
}

void Requests::heapSort(int sort_mode)
{
    int n = request_list.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(request_list, n, i, sort_mode);

    for (int i = n - 1; i > 0; i--) {
        swap(request_list[0], request_list[i]);
        heapify(request_list, i, 0, sort_mode);
    }
}
void Requests::heapify(vector<UserRequest> &array, int n, int i, int sort_mode)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && compare(array[left], array[largest], sort_mode))
        largest = left;
    if (right < n && compare(array[right], array[largest], sort_mode))
        largest = right;
    if (largest != i) {
        swap(array[i], array[largest]);
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

UserRequest &Requests::operator[](const int index)
{
    return request_list[index];
}

bool compare(const UserRequest &a, const UserRequest &b, int index)
{
    switch (index) {
        case 0: return a.id > b.id;
        case 1: return a.client_name > b.client_name;
        case 2: return a.client_passportID > b.client_passportID;
        case 3: return a.client_phonenumber > b.client_phonenumber;
        case 4: return a.date > b.date;
        case 5: return a.status > b.status;
        case 6: return a.attempt_number > b.attempt_number;
        default: return false;
    }
}

