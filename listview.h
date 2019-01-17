#ifndef LISTVIEW_H
#define LISTVIEW_H

#include "task.h"

#include <QObject>

class listView : public QObject
{
    Q_OBJECT
public:
    explicit listView(QObject *parent = nullptr);
//    QList<Task*> task_list;


//    void add_task
signals:

public slots:
};

#endif // LISTVIEW_H
