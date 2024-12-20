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
}

void TimeMenu::setAvailableTimes(const QSet<QTime>& occupiedTimes, const QDate& date) {
    current_date = date;

    // Удалить предыдущие кнопки
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Создаём кнопки для временных интервалов
    QTime startTime(8, 0); // Начало рабочего дня
    QTime endTime(18, 0);  // Конец рабочего дня
    int row = 0;

    while (startTime < endTime) {
        QPushButton *timeButton = new QPushButton(startTime.toString("hh:mm"), this);

        if (occupiedTimes.contains(startTime))
        {
            timeButton->setEnabled(false);
            timeButton->setStyleSheet("background-color: #aeb8b8;");
        }
        else
        {
            timeButton->setStyleSheet("background-color: #e48926;");
            connect(timeButton, &QPushButton::clicked, [this, startTime]() {
                emit timeSelected(startTime);
                close();
            });
        }

        layout->addWidget(timeButton, row / 4, row % 4); // Кнопки в сетке
        row++;

        startTime = startTime.addSecs(30 * 60); // Интервалы по 30 минут
    }
}

