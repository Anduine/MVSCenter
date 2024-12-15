#ifndef ADD_USER_H
#define ADD_USER_H

#include "requests.h"

#include <QWidget>

namespace Ui {
class AddUser;
}

class AddUser : public QWidget
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = nullptr);
    explicit AddUser(UserRequest *user_request);
    ~AddUser();

private slots:
    void on_pushButtonBack_clicked();

    void on_pushButtonAccept_clicked();

private:
    Ui::AddUser *ui;
    UserRequest *request;
};

#endif // ADD_USER_H
