#ifndef TIME_MENU_H
#define TIME_MENU_H

#include <QWidget>
#include <QDate>
#include <QGridLayout>

namespace Ui {
class TimeMenu;
}

class TimeMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TimeMenu(QWidget *parent = nullptr);
    ~TimeMenu();

    void setAvailableTimes(const QSet<QTime>& occupiedTimes, const QDate& date);

signals:
    void timeSelected(const QTime& time);

private:
    Ui::TimeMenu *ui;
    QDate current_date;
    QGridLayout *layout;
};

#endif // TIME_MENU_H
