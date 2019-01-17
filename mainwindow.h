#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "task.h"

#include <QMainWindow>
#include <QListWidgetItem>
#include <QtXml>
#include <QMessageBox>

#include "libxl.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QList<Task*> task_list;

private slots:

    ////Func
    void load();

    void save();

    void add_task_show();

    void list_reload(Task *item);

    void list_clear();

    void all_reload();

    void time(int days);

    void filter(bool type, Task *item);

    ///Button Events
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_add_button_clicked();

    void on_task_confirme_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_7_clicked();

    void on_actionZapisz_triggered();

    void on_actionDodaj_zadanie_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
