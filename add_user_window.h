#ifndef ADD_USER_WINDOW_H
#define ADD_USER_WINDOW_H

#include "requests.h"

#include <QWidget>

namespace Ui {
class AddUser;
}

class AddUser : public QWidget
{
    Q_OBJECT

public:
    explicit AddUser(Requests *_requests, QWidget *parent = nullptr);
    explicit AddUser(Requests *_requests, bool _is_user, QString name, qint64 phonenumber, QString passportID, QWidget *parent = nullptr);
    ~AddUser();

signals:
    void userAdded(const UserRequest& request);

private slots:
    void on_pushButtonBack_clicked();

    void on_pushButtonAccept_clicked();

    void on_pushButtonTimeMenu_clicked();

private:
    Ui::AddUser *ui;
    UserRequest *request;

    Requests *requests;

    bool is_user;
};

#endif // ADD_USER_WINDOW_H
