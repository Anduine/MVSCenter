#include "main_window.h"
#include "./ui_main_window.h"

#include "add_user_window.h"
#include "edit_user_window.h"

#include "requests.h"

#include <QElapsedTimer>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QString _username, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , username(_username)
{
    ui->setupUi(this);
    this->setWindowTitle("Менеджер центру МВС");

    connect(ui->tableWidget->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::onHeaderClicked);

    ui->tableWidget->setColumnWidth(0, 40);
    ui->tableWidget->setColumnWidth(1, 220);
    ui->tableWidget->setColumnWidth(2, 110);
    ui->tableWidget->setColumnWidth(3, 130);
    ui->tableWidget->setColumnWidth(5, 120);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAllUsers(bool reverse = false)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    if (reverse)
    {
        for (int i = 0; i < requests.size(); ++i)
        {
            UserRequest cur = requests[i];

            int rowCount = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowCount);

            ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(cur.id)));
            ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(cur.client_name));
            ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(cur.status));
            ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(cur.ticket_type));
            ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(cur.client_passportID));
            ui->tableWidget->setItem(rowCount, 5, new QTableWidgetItem(QString::number(cur.client_phonenumber)));
            ui->tableWidget->setItem(rowCount, 6, new QTableWidgetItem(
                                                      cur.date.time().toString("hh:mm") + " " +
                                                      cur.date.date().toString("dd.MM.yyyy")
                                                      ));
            ui->tableWidget->setItem(rowCount, 7, new QTableWidgetItem(QString::number(cur.attempt_number)));
        }
    }
    else
    {
        for (int i = requests.size() - 1; i >= 0; --i)
        {
            UserRequest cur = requests[i];

            int rowCount = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowCount);

            ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(cur.id)));
            ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(cur.client_name));
            ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(cur.status));
            ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(cur.ticket_type));
            ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(cur.client_passportID));
            ui->tableWidget->setItem(rowCount, 5, new QTableWidgetItem(QString::number(cur.client_phonenumber)));
            ui->tableWidget->setItem(rowCount, 6, new QTableWidgetItem(
                                                      cur.date.time().toString("hh:mm") + " " +
                                                      cur.date.date().toString("dd.MM.yyyy")
                                                      ));
            ui->tableWidget->setItem(rowCount, 7, new QTableWidgetItem(QString::number(cur.attempt_number)));
        }
    }
}

void MainWindow::onHeaderClicked(int column)
{
    QElapsedTimer timer;

    int method = ui->comboBoxSortMethod->currentIndex();
    timer.start();
    if (method == 0)
    {
        requests.heapSort(column);
    }
    else if (method == 1)
    {
        requests.bubbleSort(column);
    }
    else if (method == 2)
    {
        requests.selectionSort(column);
    }

    showAllUsers(true);
    qint64 work_time = timer.elapsed();

    ui->lineEditSortTime->setText(QString::number(work_time) + " мс");
}

void MainWindow::on_pushButtonAddUser_clicked()
{
    AddUser* add_user_form = new AddUser(&requests);
    add_user_form->setAttribute(Qt::WA_DeleteOnClose);
    add_user_form->show();

    connect(add_user_form, &AddUser::userAdded, this, &MainWindow::onUserAdded);
}

void MainWindow::onUserAdded(const UserRequest& request)
{
    // Опрацьовуємо дані, з AddUser
    requests.insertUser(request);

    showAllUsers();
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    // Получаем данные из строки
    UserRequest *cur = new UserRequest;

    cur->id = ui->tableWidget->item(row, 0)->text().toInt();
    cur->client_name = ui->tableWidget->item(row, 1)->text();
    cur->status = ui->tableWidget->item(row, 2)->text();
    cur->ticket_type = ui->tableWidget->item(row, 3)->text();
    cur->client_passportID = ui->tableWidget->item(row, 4)->text();
    cur->client_phonenumber = ui->tableWidget->item(row, 5)->text().toLongLong();
    cur->date = QDateTime::fromString(ui->tableWidget->item(row, 6)->text(), "hh:mm dd.MM.yyyy");
    cur->attempt_number = ui->tableWidget->item(row, 7)->text().toInt();

    // Выполняем нужные действия, например, редактирование
    EditUserWindow *edit_window = new EditUserWindow(&requests, cur);

    connect(edit_window, &EditUserWindow::userEdited, this, &MainWindow::onUserEdited);

    edit_window->setAttribute(Qt::WA_DeleteOnClose);
    edit_window->setAttribute(Qt::WA_SetWindowModality);
    edit_window->show();
}

void MainWindow::onUserEdited(const UserRequest &updated_user) {
    // Обновляем в requests
    for (auto &request : requests.getList()) {
        if (request.id == updated_user.id) {
            request = updated_user;
            break;
        }
    }

    // Обновляем только соответствующую строку в таблице
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        if (ui->tableWidget->item(row, 0)->text().toInt() == updated_user.id) {
            ui->tableWidget->item(row, 1)->setText(updated_user.client_name);
            ui->tableWidget->item(row, 2)->setText(updated_user.status);
            ui->tableWidget->item(row, 3)->setText(updated_user.ticket_type);
            ui->tableWidget->item(row, 4)->setText(updated_user.client_passportID);
            ui->tableWidget->item(row, 5)->setText(QString::number(updated_user.client_phonenumber));
            ui->tableWidget->item(row, 6)->setText(
                updated_user.date.time().toString("hh:mm") + " " +
                updated_user.date.date().toString("dd.MM.yyyy")
                );
            ui->tableWidget->item(row, 7)->setText(QString::number(updated_user.attempt_number));
            break;
        }
    }
}

void MainWindow::on_new_table_triggered()
{
    requests.clear();
    showAllUsers();
}

void MainWindow::on_add_one_triggered()
{
    on_pushButtonAddUser_clicked();
}

void MainWindow::on_add_from_file_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Оберіть файл для завантаження",
                                                    "",  // Директорія
                                                    "Text Files (*.txt);;All Files (*)"); // Фільтри файлів

    if (filePath.isEmpty()) {
        QMessageBox::information(this, "Відміна", "Файл не був обран.");
        return;
    }

    if (requests.loadFromFile(filePath)) {
        showAllUsers();
    } else {
        QMessageBox::warning(this, "Помилка", "Не вдалося завантажити дані з файлу.");
    }
}




