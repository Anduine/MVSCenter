#ifndef AUTH_WINDOW_H
#define AUTH_WINDOW_H

#include "authorization.h"
#include "main_window.h"
#include "user_window.h"

#include <QWidget>

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AuthWindow(MainWindow *_main_window, UserWindow *_user_window, QWidget *parent = nullptr);
    ~AuthWindow();

private slots:
    void on_pushButtonLogin_clicked();

private:
    Ui::AuthWindow *ui;
    MainWindow *main_window;
    UserWindow *user_window;
    Authorization auth;
};

#endif // AUTH_WINDOW_H
