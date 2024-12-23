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

private slots:
    void on_pushButtonAddTicket_clicked();
    void onUserAdded(const UserRequest &request);

private:
    Ui::UserWindow *ui; // delete у деструкторі
    QString username;

    Requests requests;
    std::vector<UserRequest> user_tickets; // delete у деструкторі

    void showAllTickets(bool reverse = false);
};

#endif // USER_WINDOW_H
