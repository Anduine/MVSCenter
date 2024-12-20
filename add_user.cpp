#include "add_user.h"
#include "ui_add_user.h"

#include "requests.h"
#include "time_menu.h"

#include <QMenu>
#include <QMessageBox>

AddUser::AddUser(Requests *_requests, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddUser)
    , requests(_requests)
{
    ui->setupUi(this);
    this->setWindowTitle("Послуга");
    request = new UserRequest();
}

AddUser::AddUser(Requests *_requests, bool _is_user, QString name, qint64 phonenumber, QString passportID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddUser)
    , requests(_requests)
    , is_user(_is_user)
{
    ui->setupUi(this);
    this->setWindowTitle("Послуга");
    request = new UserRequest();

    if (is_user)
    {
        ui->lineEditPIB->setText(name);
        ui->lineEditPhone->setText(QString::number(phonenumber));
        ui->lineEditPassportID->setText(passportID);

        ui->lineEditPIB->setReadOnly(true);
        ui->lineEditPhone->setReadOnly(true);
        ui->lineEditPassportID->setReadOnly(true);

        ui->comboBoxStatus->hide();
        ui->label_6->hide();
        ui->spinBoxAttempt->hide();
        ui->label_7->hide();
    }
}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::on_pushButtonAccept_clicked()
{
    if (ui->lineEditPIB->text().isEmpty() ||
        ui->lineEditPassportID->text().isEmpty() ||
        ui->lineEditPhone->text().isEmpty() ||
        ui->comboBoxType->currentText().isEmpty() ||
        ui->comboBoxStatus->currentText().isEmpty() ||
        ui->spinBoxAttempt->value() == 0 ||
        request->date.isNull() == true)
    {
        QMessageBox::warning(this, "Помилка", "Заповніть всі поля та оберіть час.");
        return;
    }

    request->client_name = ui->lineEditPIB->text();
    request->client_passportID = ui->lineEditPassportID->text();
    request->client_phonenumber = ui->lineEditPhone->text().toLongLong();
    request->ticket_type = ui->comboBoxType->currentText();
    request->status = ui->comboBoxStatus->currentText();
    request->attempt_number = ui->spinBoxAttempt->value();

    emit userAdded(*request);

    close();
}

void AddUser::on_pushButtonBack_clicked()
{
    close();
}

void AddUser::on_pushButtonTimeMenu_clicked()
{
    QDate selected_date = ui->dateEdit->date();
    QSet<QTime> occupiedTimes = requests->getOccupiedTimes(selected_date);

    TimeMenu *popup_menu = new TimeMenu(this);

    connect(popup_menu, &TimeMenu::timeSelected, [this, selected_date](const QTime &time) {
        request->date = QDateTime(selected_date, time);
    });

    popup_menu->move(ui->pushButtonTimeMenu->mapToGlobal(QPoint(-50, ui->pushButtonTimeMenu->height())));
    popup_menu->setAvailableTimes(occupiedTimes, selected_date);
    popup_menu->show();
}

