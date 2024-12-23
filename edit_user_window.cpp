#include "edit_user_window.h"
#include "ui_edit_user_window.h"

#include "requests.h"
#include "time_menu.h"

#include <QMessageBox>

EditUserWindow::EditUserWindow(Requests *_requests, UserRequest *_user_request, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EditUserWindow)
    , requests(_requests)
    , user_request(_user_request)
{
    ui->setupUi(this);
    this->setWindowTitle("Редагування");

    if (user_request)
    {
        ui->lineEditPIB->setText(user_request->client_name);
        ui->lineEditPhone->setText(QString::number(user_request->client_phonenumber));
        ui->lineEditPassportID->setText(user_request->client_passportID);
    }
}

EditUserWindow::~EditUserWindow()
{
    delete ui;
}

void EditUserWindow::on_pushButtonAccept_clicked()
{
    if (!requests || !user_request) return;

    if (ui->lineEditPIB->text().isEmpty() ||
        ui->lineEditPassportID->text().isEmpty() ||
        ui->lineEditPhone->text().isEmpty() ||
        ui->comboBoxType->currentText().isEmpty() ||
        ui->comboBoxStatus->currentText().isEmpty() ||
        ui->spinBoxAttempt->value() == 0 ||
        user_request->date.isNull() == true)
    {
        QMessageBox::warning(this, "Помилка", "Заповніть всі поля та оберіть час.");
        return;
    }

    user_request->client_name = ui->lineEditPIB->text();
    user_request->client_passportID = ui->lineEditPassportID->text();
    user_request->client_phonenumber = ui->lineEditPhone->text().toLongLong();
    user_request->ticket_type = ui->comboBoxType->currentText();
    user_request->status = ui->comboBoxStatus->currentText();
    user_request->attempt_number = ui->spinBoxAttempt->value();

    emit userEdited(*user_request);

    close();
}

void EditUserWindow::on_pushButtonTimeMenu_clicked()
{
    QDate selected_date = ui->dateEdit->date();
    QSet<QTime> occupiedTimes = requests->getOccupiedTimes(selected_date);

    TimeMenu *popup_menu = new TimeMenu(this);

    connect(popup_menu, &TimeMenu::timeSelected, [this, selected_date](const QTime &time) {
        user_request->date = QDateTime(selected_date, time);
    });

    popup_menu->move(ui->pushButtonTimeMenu->mapToGlobal(QPoint(-50, ui->pushButtonTimeMenu->height())));
    popup_menu->setAvailableTimes(occupiedTimes);
    popup_menu->show();
}

void EditUserWindow::on_pushButtonBack_clicked()
{
    close();
}

