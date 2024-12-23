#include "user_window.h"
#include "ui_user_window.h"

#include "add_user_window.h"

#include <vector>

UserWindow::UserWindow(QString _username, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserWindow)
    , username(_username)
    , requests("input.txt")
{
    ui->setupUi(this);
    this->setWindowTitle("Користувач " + username);

    ui->labelUserName->setText(username);
    user_tickets = requests.getInfoUser(username);

    bool isContain{false};

    for (auto &user : user_tickets)
    {
        if (username == user.client_name)
        {
            isContain = true;
            break;
        }
    }

    if (isContain)
    {
        ui->lineEditPassport->setText(user_tickets[0].client_passportID);
        ui->lineEditPhonenumber->setText(QString::number(user_tickets[0].client_phonenumber));
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
    user_tickets.clear();
}

void UserWindow::showAllTickets(bool reverse)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    if (reverse)
    {
        for (int i = 0; i < user_tickets.size(); ++i)
        {
            UserRequest cur = user_tickets[i];

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
        for (int i = user_tickets.size() - 1; i >= 0; --i)
        {
            UserRequest cur = user_tickets[i];

            int rowCount = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowCount);

            ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(cur.date.time().hour()) + ":" + QString::number(cur.date.time().minute()) +
                                                                       " " + QString::number(cur.date.date().day()) + "." + QString::number(cur.date.date().month()) + "." + QString::number(cur.date.date().year())));
            ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(cur.status));
            ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(cur.ticket_type));
        }
    }
}

void UserWindow::on_pushButtonAddTicket_clicked()
{ // (Requests *_requests, bool _is_user, QString name, qint64 phonenumber, QString passportID, QWidget *parent)
    AddUser* add_user_form = new AddUser(&requests, true, ui->labelUserName->text(), ui->lineEditPhonenumber->text().toLongLong(), ui->lineEditPassport->text());
    add_user_form->setAttribute(Qt::WA_DeleteOnClose);
    add_user_form->show();

    connect(add_user_form, &AddUser::userAdded, this, &UserWindow::onUserAdded);
}

void UserWindow::onUserAdded(const UserRequest& request)
{
    user_tickets.push_back(request);
    requests.insertUser(request);

    showAllTickets();
}


