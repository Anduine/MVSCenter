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

    void on_tableWidget_cellDoubleClicked(int row, int column);
    void onUserEdited(const UserRequest &updated_user);

    void on_new_table_triggered();

    void on_add_one_triggered();

    void on_add_from_file_triggered();

private:
    Ui::MainWindow *ui; // delete у деструкторі

    Requests requests;
    void showAllUsers(bool reverse);
    void onHeaderClicked(int column);
};
#endif // MAIN_WINDOW_H
