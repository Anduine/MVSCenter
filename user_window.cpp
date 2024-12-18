#include "user_window.h"
#include "ui_user_window.h"

#include <vector>

UserWindow::UserWindow(QString _username, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserWindow)
    , username(_username)
    , requests("input.txt")
{
    ui->setupUi(this);
    ui->labelUserName->setText(username);
    userTickets = requests.getInfoUser(username);

    bool isContain{false};

    for (auto &user : userTickets)
    {
        if (username == user.client_name)
        {
            isContain = true;
            break;
        }
    }

    if (isContain)
    {
        ui->lineEditPassport->setText(userTickets[0].client_passportID);
        ui->lineEditPhonenumber->setText(QString::number(userTickets[0].client_phonenumber));
    }
    else
    {
        ui->lineEditPassport->setText("Немає інформації");
        ui->lineEditPhonenumber->setText("Немає інформації");
    }

    ui->tableWidget->setColumnWidth(2, 160);

    showAllTickets();
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::showAllTickets(bool reverse)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    if (reverse)
    {
        for (int i = 0; i < userTickets.size(); ++i)
        {
            UserRequest cur = userTickets[i];

            int rowCount = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowCount);

            ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(cur.date.time().hour()) + ":" + QString::number(cur.date.time().minute()) +
                                                                        " " + QString::number(cur.date.date().day()) + "." + QString::number(cur.date.date().month()) + "." + QString::number(cur.date.date().year())));
            ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(cur.status));
            ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(cur.ticket_type));
        }
    }
    else
    {
        for (int i = userTickets.size() - 1; i >= 0; --i)
        {
            UserRequest cur = userTickets[i];

            int rowCount = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowCount);

            ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(cur.date.time().hour()) + ":" + QString::number(cur.date.time().minute()) +
                                                                       " " + QString::number(cur.date.date().day()) + "." + QString::number(cur.date.date().month()) + "." + QString::number(cur.date.date().year())));
            ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(cur.status));
            ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(cur.ticket_type));
        }
    }
}
