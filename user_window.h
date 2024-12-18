#ifndef USER_WINDOW_H
#define USER_WINDOW_H

#include "requests.h"

#include <QWidget>

namespace Ui {
class UserWindow;
}

class UserWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UserWindow(QString _username, QWidget *parent = nullptr);
    ~UserWindow();

private:
    Ui::UserWindow *ui;
    QString username;

    Requests requests;
    std::vector<UserRequest> userTickets;

    void showAllTickets(bool reverse = false);
};

#endif // USER_WINDOW_H
