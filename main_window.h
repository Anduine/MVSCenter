#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "requests.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonAddUser_clicked();
    void onUserAdded(const UserRequest& request);

private:
    Ui::MainWindow *ui;
    Requests requests;
    void showAllUsers();
    void onHeaderClicked(int column);
};
#endif // MAIN_WINDOW_H
