#include "add_user.h"
#include "ui_add_user.h"

#include "requests.h"

AddUser::AddUser(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddUser)
{
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
    request->client_phonenumber = ui->lineEditPhone->text().toLongLong();
    request->date = ui->dateEdit->date();
    request->status = ui->comboBoxStatus->currentText();
    request->attempt_number = ui->spinBoxAttempt->value();

    emit userAdded(*request);

    close();
}

void AddUser::on_pushButtonBack_clicked()
{
    close();
}




