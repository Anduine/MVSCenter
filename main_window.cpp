#include "main_window.h"
#include "./ui_main_window.h"
#include "add_user.h"

#include "requests.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonAddUser_clicked()
{
    UserRequest *request = nullptr;
    AddUser* add_user_form = new AddUser(request);
    add_user_form->setAttribute(Qt::WA_DeleteOnClose);
    add_user_form->show();
}

