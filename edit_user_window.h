#ifndef EDIT_USER_WINDOW_H
#define EDIT_USER_WINDOW_H

#include "requests.h"

#include <QWidget>

namespace Ui {
class EditUserWindow;
}

class EditUserWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditUserWindow(Requests *_requests, UserRequest *_user_request, QWidget *parent = nullptr);
    ~EditUserWindow();

signals:
    void userEdited(const UserRequest& request);

private slots:
    void on_pushButtonAccept_clicked();

    void on_pushButtonTimeMenu_clicked();

    void on_pushButtonBack_clicked();

private:
    Ui::EditUserWindow *ui; // delete у деструкторі
    UserRequest *user_request; // delete не треба

    Requests *requests; // delete не треба
};

#endif // EDIT_USER_WINDOW_H
