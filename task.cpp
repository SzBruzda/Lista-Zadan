#include "task.h"

Task::Task(QObject *parent) : QObject(parent)
{

}

Task::Task(bool home, bool job, bool shop, bool general, QString task, QString date)
{
    this->home = home;
    this->job = job;
    this->shop = shop;
    this->task = task;
    this->general = general;
    this->date = date;
}

qint64 Task::days_to()
{
    QDate current = QDateTime::currentDateTime().date();
    QDate task_date = QDate::fromString(this->date , Qt::SystemLocaleShortDate);

    qint64 days_to = current.daysTo(task_date);
    return days_to;
}

QString Task::toString()
{
    QString flag;
    QString task;
    if(this->home){
        flag = "  #HOME";
        task_type = "home";
    }else if(this->job){
        flag = "  #JOB";
        task_type = "job";
    }else if(this->shop){
        flag = "  #SHOP";
        task_type = "shop";
    }else{
        flag = "  #GENERAL";
        task_type = "general";
    }
    task = this->task + flag;
    return task;
}
