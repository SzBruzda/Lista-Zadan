#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QDate>
class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = nullptr);

    Task(bool home, bool job, bool shop, bool general, QString task, QString date);

    bool home, job, shop, general;

    QString task, task_type, date;

    qint64 days_to();

    QDate deadline();

    QString toString();


signals:

public slots:
};

#endif // TASK_H
