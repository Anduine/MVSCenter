#include "time_menu.h"
#include "ui_time_menu.h"

#include <QDate>
#include <QGridLayout>
#include <QPushButton>

TimeMenu::TimeMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TimeMenu)
    , layout(new QGridLayout(this))
{
    ui->setupUi(this);
    setWindowFlags(Qt::Popup); // флаг Popup
    setFixedSize(300, 200);
}

TimeMenu::~TimeMenu()
{
    delete ui;
    delete layout;

}

void TimeMenu::setAvailableTimes(const QSet<QTime> &occupied_times) {
    // Удалить предыдущие кнопки
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    QTime start_time(8, 0); // Начало рабочего дня
    QTime end_time(18, 0);  // Конец рабочего дня
    int row = 0;

    while (start_time < end_time) {
        QPushButton *timeButton = new QPushButton(start_time.toString("hh:mm"), this);

        if (occupied_times.contains(start_time))
        {
            timeButton->setEnabled(false);
            timeButton->setStyleSheet("background-color: #aeb8b8;");
        }
        else
        {
            timeButton->setStyleSheet("background-color: #e48926;");
            connect(timeButton, &QPushButton::clicked, [this, start_time]() {
                emit timeSelected(start_time);
                close();
            });
        }

        layout->addWidget(timeButton, row / 4, row % 4); // Кнопки в сетке
        row++;

        start_time = start_time.addSecs(30 * 60); // Интервалы по 30 минут
    }
}

