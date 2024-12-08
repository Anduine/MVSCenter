#include "requests.h"

#include <QDate>
#include <QFile>
#include <QString>
#include <vector>
using namespace std;

Requests::Requests() {}

    void loadFromFile(QString filepath){
        QFile file(filepath);
        if(!file.open(QIODevice::ReadOnly)){
            qDebug() << "%File error%" << file.error();
        }else{
            vector<UserRequest> request_list;
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
                callerStruct.client_phonenumber = parts[5].toInt();
                callerStruct.attempt_number = parts[6].toInt();
                request_list.push_back(callerStruct);
            file.close();
        }
    }

}
    void Requests::bubbleSortDate(){
        int n = request_list.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
               if (compareDate(request_list[j], request_list[j + 1])){
                    swap(request_list[j], request_list[j + 1]);
                }
            }
        }
}
    void Requests::bubbleSortName(){
        int n = request_list.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (compareName(request_list[j], request_list[j + 1])){
                    swap(request_list[j], request_list[j + 1]);
                }
            }
        }
    }

    void Requests::selectionSortDate(){
        int n = request_list.size();
        for (int i = 0; i < n - 1; ++i) {
            int min_i  = i;
            for (int j = i + 1; j < n; ++j) {
                if (compareDate(request_list[j], request_list[min_i])) {
                    min_i = j;
                }
            }
            swap(request_list[i], request_list[min_i]);
        }
    }

    void Requests::selectionSortName(){
        int n = request_list.size();
        for (int i = 0; i < n - 1; ++i) {
            int min_i  = i;
            for (int j = i + 1; j < n; ++j) {
                if (compareName(request_list[j], request_list[min_i])) {
                    min_i = j;
                }
            }
            swap(request_list[i], request_list[min_i]);
        }
    }

bool compareDate(const UserRequest& a, const UserRequest& b){
    return a.date > b.date;
}
bool compareName(const UserRequest& a, const UserRequest& b){
    return a.client_name > b.client_name;
}
