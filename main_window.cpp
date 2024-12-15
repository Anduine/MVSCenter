#include "main_window.h"
#include "./ui_main_window.h"
#include "add_user.h"

#include "requests.h"

#include <QElapsedTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tableWidget->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::onHeaderClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAllUsers()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    for (int i = 0; i < requests.size(); i++)
    {
        UserRequest cur = requests[i];

        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);

        ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(cur.id))); // ID
        ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(cur.client_name));
        ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(cur.client_passportID));
        ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString::number(cur.client_phonenumber)));
        ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(QString::number(cur.date.year()) + "-" +
                                                                   QString::number(cur.date.month()) + "-" + QString::number(cur.date.day())));
        ui->tableWidget->setItem(rowCount, 5, new QTableWidgetItem(cur.status));
        ui->tableWidget->setItem(rowCount, 6, new QTableWidgetItem(QString::number(cur.attempt_number)));
    }
}

void MainWindow::onHeaderClicked(int column)
{
    QElapsedTimer timer;
    if (column == 1)
    {
        timer.start();

        requests.selectionSortName();
        showAllUsers();

        qint64 work_time = timer.elapsed();

        ui->lineEditSortTime->setText(QString::number(work_time) + " мс");
    }
}

void MainWindow::on_pushButtonAddUser_clicked()
{
    AddUser* add_user_form = new AddUser();
    add_user_form->setAttribute(Qt::WA_DeleteOnClose);
    add_user_form->show();

    connect(add_user_form, &AddUser::userAdded, this, &MainWindow::onUserAdded);
}

void MainWindow::onUserAdded(const UserRequest& request)
{
    // Обрабатываем данные, переданные из AddUser
    requests.insertUser(request); // Добавляем пользователя в структуру данных
    ui->lineEditStatus->setText("Готово");

    showAllUsers();

}

