#include "auth_window.h"
#include "ui_auth_window.h"

#include "authorization.h"
#include "main_window.h"
#include "user_window.h"

#include <QMessageBox>

AuthWindow::AuthWindow(MainWindow *_main_window, UserWindow *_user_window, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AuthWindow)
    , main_window(_main_window)
    , user_window(_user_window)
{
    ui->setupUi(this);
    this->setWindowTitle("Авторизація в системі МВС");
    auth = new Authorization();
}

AuthWindow::~AuthWindow()
{
    delete ui;
    delete auth;
}

void AuthWindow::on_pushButtonLogin_clicked()
{
    QString username = ui->lineEditUserName->text();
    QString password = ui->lineEditPassword->text();

    if (auth->login(username, password) == 2)
    {
        main_window = new MainWindow();
        main_window->show();
        close();
    }
    else if (auth->login(username, password) == 1)
    {
        user_window = new UserWindow(username);
        user_window->show();
        close();
    }
    else
    {
        QMessageBox::warning(this, "Помилка", "Невірний логін або пароль!");
        ui->lineEditPassword->clear();
    }
}

