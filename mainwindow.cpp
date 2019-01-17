#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->add_widget->hide();
    QFont myFont("Arial", 12,QFont::Bold,false);
    myFont.setLetterSpacing(QFont::PercentageSpacing,150);
    ui->task_confirme->setFont(myFont);
    ui->task_default->setChecked(true);


    this->load();
    this->all_reload();

}

MainWindow::~MainWindow(){
    delete ui;
}

/////////FUNC

void MainWindow::load()
{
    QDomDocument document;

    //Load the file
    QFile file("taskSave.xml");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(
        this,
        tr("Error"),
        tr("Wczytywanie nie powiodło się.") );
    }else{
        if(!document.setContent(&file)){
            QMessageBox::information(
            this,
            tr("Error"),
            tr("Wczytywanie nie powiodło się.") );
        }
        file.close();
    }

    QDomElement root = document.firstChildElement();

    QDomNodeList items = root.elementsByTagName("Task");
    for(int i = 0; i < items.count(); i++){
       QDomNode itemnode = items.at(i);

       //convert to element
       if(itemnode.isElement()){
           QDomElement itemele = itemnode.toElement();
           task_list.append(new Task(itemele.attribute("home")=="1"?true:false,itemele.attribute("job")=="1"?true:false,
                                    itemele.attribute("shop")=="1"?true:false,itemele.attribute("general")=="1"?true:false,itemele.attribute("task"), itemele.attribute("date")));
       }
    }
}

void MainWindow::save()
{
    QDomDocument document;
    QDomElement root = document.createElement("Tasks");
    document.appendChild(root);
    foreach(Task *item, task_list){
        QDomElement task = document.createElement("Task");
        QStringList task_list = item->toString().split("#");
        QString task_text = task_list.at(0);
        task.setAttribute("task", task_text.remove(task_text.length()-2,2));
        task.setAttribute("home", item->home);
        task.setAttribute("job", item->job);
        task.setAttribute("shop", item->shop);
        task.setAttribute("general", item->general);
        task.setAttribute("home", item->home);
        task.setAttribute("date", item->date);
        root.appendChild(task);
    }
    QFile file("taskSave.xml");

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::information(
        this,
        tr("Error"),
        tr("Zapisywanie nie powiodło się.") );
    }else{
        QTextStream stream(&file);
        stream << document.toString();
        file.close();
        QMessageBox::information(
        this,
        tr("Lista zadan."),
        tr("Zapisywanie powiodło się.") );
    }
}

void MainWindow::add_task_show()
{
    if(ui->add_widget->isVisible()){
        ui->add_widget->hide();
    }else{
        ui->add_widget->show();
    }
}

void MainWindow::list_reload(Task *item){
    QListWidgetItem* li_item = new QListWidgetItem(item->toString());
    if(QString::compare(item->task_type,"home") == 0){
        li_item->setBackgroundColor(QColor(244,204,112));
    } else if(QString::compare(item->task_type,"job") == 0){
       li_item->setBackgroundColor(QColor(222,122,34));
    } else if(QString::compare(item->task_type,"shop") == 0){
       li_item->setBackgroundColor(QColor(32,148,139));
    } else{
        li_item->setBackgroundColor(QColor(106,177,135));
    }
    ui->listWidget->addItem(li_item);

    QListWidgetItem* li_date = new QListWidgetItem(item->date);
    if(item->days_to() <= 7){
        li_date->setBackgroundColor(Qt::red);
    }else{
        li_date->setBackgroundColor(Qt::green);
    }
    ui->listWidget_date->addItem(li_date);
}

void MainWindow::list_clear()
{
    ui->listWidget->clear();
    ui->listWidget_date->clear();
}

void MainWindow::all_reload()
{
    this->list_clear();
    foreach(Task *item, task_list){
        this->list_reload(item);
    }
}

void MainWindow::time(int days)
{
    this->list_clear();
    foreach(Task *item , task_list){
        if(item->days_to() < days){
            this->list_reload(item);
        }
    }
}

void MainWindow::filter(bool type, Task *item)
{
    if(type){
        this->list_reload(item);
    }
}


/////// Buttons Events

void MainWindow::on_add_button_clicked()
{
    this->add_task_show();
}

void MainWindow::on_task_confirme_clicked()
{
   task_list.append(new Task(ui->task_home->isChecked(),ui->task_job->isChecked(),
                             ui->task_shop->isChecked(),ui->task_default->isChecked() ,ui->task_text->toPlainText(), ui->task_calendar->selectedDate().toString(Qt::SystemLocaleShortDate)));
   this->all_reload();
   ui->task_text->clear();
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    foreach(Task *task, task_list){
        if (QString::compare(item->text(),task->toString()) == 0){
            task_list.removeAt(task_list.indexOf(task));
        }
    }
    this->all_reload();
}

void MainWindow::on_pushButton_4_clicked()
{
    this->list_clear();
    foreach(Task *item , task_list){
        this->filter(item->general, item);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    this->list_clear();
    foreach(Task *item , task_list){
        this->filter(item->shop, item);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    this->list_clear();
    foreach(Task *item , task_list){
        this->filter(item->job, item);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    this->list_clear();
    foreach(Task *item , task_list){
        this->filter(item->home, item);
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    this->time(32);
}

void MainWindow::on_pushButton_clicked()
{
    this->time(8);
}

void MainWindow::on_pushButton_7_clicked()
{
    this->list_clear();
    this->all_reload();
}

void MainWindow::on_actionZapisz_triggered()
{
    this->save();
}

void MainWindow::on_actionDodaj_zadanie_triggered()
{
    this->add_task_show();
}
