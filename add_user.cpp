#include "add_user.h"
#include "ui_add_user.h"

#include "requests.h"

AddUser::AddUser(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddUser)
{
    ui->setupUi(this);
}

AddUser::AddUser(UserRequest *user_request)
    : QWidget(nullptr)
    , ui(new Ui::AddUser)
{
    request = user_request;
    ui->setupUi(this);
}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::on_pushButtonAccept_clicked()
{
    request = new UserRequest();


    request->client_name = ui->lineEditPIB->text();
    request->client_passportID = ui->lineEditPassportID->text();
    request->client_phonenumber = ui->lineEditPhone->text().toInt();
    request->date = ui->dateEdit->date();
    request->status = ui->comboBoxStatus->currentText();
    request->attempt_number = ui->spinBoxAttempt->displayIntegerBase();

    close();
}

void AddUser::on_pushButtonBack_clicked()
{
    close();
}




