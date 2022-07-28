#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QListWidgetItem>

player** tempArray;

void mergeSort_age(player** arr, int first, int last);

void mergeSort_value(player** arr, int first, int last);

void mergeSort_release_clause(player** arr, int first, int last);

void mergeSort_height(player** arr, int first, int last);

void mergeSort_weight(player** arr, int first, int last);

void mergeSort_wage(player** arr, int first, int last);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix(":/new/prefix1/img/defaultavatar.png");
    int w = ui->label_28->width();
    int h = ui->label_28->height();
    ui->label_28->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));

    array1 = new player[13000];

    age = new player*[13000];
    height = new player*[13000];
    weight = new player*[13000];
    wage = new player*[13000];
    value = new player*[13000];
    release_clause = new player*[13000];
    club = new AVL_Tree_NC;
    country = new AVL_Tree_NC;

    parser(array1);

    for (int i = 0; i < 13000; i++)
    {
        age[i] = &array1[i];
        height[i] = &array1[i];
        weight[i] = &array1[i];
        wage[i] = &array1[i];
        value[i] = &array1[i];
        release_clause[i] = &array1[i];
    }

    tempArray = new player*[13000];
    mergeSort_age(age, 0, 12999);
    delete tempArray;

    tempArray = new player*[13000];
    mergeSort_value(value, 0, 12999);
    delete tempArray;

    tempArray = new player*[13000];
    mergeSort_release_clause(release_clause, 0, 12999);
    delete tempArray;

    tempArray = new player*[13000];
    mergeSort_height(height, 0, 12999);
    delete tempArray;

    tempArray = new player*[13000];
    mergeSort_weight(weight, 0, 12999);
    delete tempArray;

    tempArray = new player*[13000];
    mergeSort_wage(wage, 0, 12999);
    delete tempArray;

    //for (int i = 0; i < 13000; i++)
        //ui->listWidget->addItem((*height[i]).name + " , " + QString::number((*height[i]).height) + " inches");

    tree1 = new AVL_Tree_player;

    for (int i = 0; i < 13000; i++)
        tree1->insertnode(&array1[i],tree1->root);

    /*AVL_Node_NC *temp = club->search_NC("FC Barcelona", club->root);

    //ui->label_2->setText(temp->list->start->next->next->next->data->name);
    temp->list->Loc_ = temp->list->start;

    while (temp->list->Loc_ != NULL)
    {
        ui->listWidget->addItem(temp->list->Loc_->data->name);
        temp->list->Loc_ = temp->list->Loc_->next;
    }*/

    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit->setPlaceholderText("Enter name of player, club or country");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::parser(player* arr)
{
    QFile file("data.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "title", file.errorString()); return;
    }

    QString line, temp;

    QTextStream in(&file);
    int i = 0;

    QChar op;
    QStringList list;
    QString temp1;

    line = in.readLine();

    while (!file.atEnd())
    {
        line = in.readLine();

        list = line.split(',');

        //player id
        arr[i].ID = list.value(1).toInt();

        //name
        temp = list.value(2);
        for (int j = 0; j < temp.size(); j++)
        {
            if (temp.data()[j] == '.')
            {
                arr[i].name = temp.remove(0,3);
                break;
            }
        }

        if (arr[i].name == "") arr[i].name = temp;

        //age
        temp = list.value(3);
        arr[i].age = temp.toInt();

        //country
        temp = list.value(4);
        arr[i].nationality = temp;

        //overall
        temp = list.value(5);
        arr[i].overall = temp.toInt();

        //club
        temp = list.value(6);
        arr[i].club = temp;

        //value
        temp = list.value(7);
        op = temp.data()[temp.size() - 1];
        if (op == 'M')
        {
            temp.remove(0,1); temp.truncate(temp.size()-1);
            arr[i].value = temp.toDouble() * 1000000;
        }
        else if (op == 'K')
        {
            temp.remove(0,1); temp.truncate(temp.size()-1);
            arr[i].value = temp.toDouble() * 1000;
        }
        else if (op == '0')
        {
            arr[i].value = 0;
        }

        //wage
        temp = list.value(8);
        op = temp.data()[temp.size() - 1];
        if (op == 'K')
        {
            temp.remove(0,1); temp.truncate(temp.size()-1);
            arr[i].wage = temp.toDouble() * 1000;
        }
        else if (op == '0')
        {
            arr[i].wage = 0;
        }

        //preffered
        temp = list.value(9);
        if (temp == "Left")
            arr[i].preffered = false;
        else if (temp == "Right")
            arr[i].preffered = true;

        //position
        temp = list.value(10);
        arr[i].position = temp;

        //jersey no.
        temp = list.value(11);
        arr[i].jersey_no = temp.toInt();

        //height
        temp = list.value(12);
        temp.remove(1,1);
        temp1 = temp;
        temp.truncate(1);
        temp1.remove(0,1);
        arr[i].height += temp.toInt() * 12;
        arr[i].height += temp1.toInt();

        //weight
        temp = list.value(13);
        temp.truncate(3);
        arr[i].weight = temp.toInt();

        //release clause
        temp = list.value(14);
        op = temp.data()[temp.size() - 1];
        if (op == 'M')
        {
            temp.remove(0,1); temp.truncate(temp.size()-1);
            arr[i].release_clause = temp.toDouble() * 1000000;
        }
        else if (op == 'K')
        {
            temp.remove(0,1); temp.truncate(temp.size()-1);
            arr[i].release_clause = temp.toDouble() * 1000;
        }
        else if (op == '0')
        {
            arr[i].release_clause = 0;
        }
        else if (temp == "")
        {
            arr[i].release_clause = 0;
        }

        AVL_Node_NC *temp = club->search_NC(arr[i].club, club->root);

        if (temp == NULL)
        {
            club->insertnode(arr[i].club, club->root);
            temp = club->search_NC(arr[i].club, club->root);
        }

        temp->list->InsertAtEnd(&arr[i]);

        temp = country->search_NC(arr[i].nationality, country->root);

        if (temp == NULL)
        {
            country->insertnode(arr[i].nationality, country->root);
            temp = country->search_NC(arr[i].nationality, country->root);
        }

        temp->list->InsertAtEnd(&arr[i]);

        i++;
    }

    file.close();

}


//merge sort for age

void merge_age(player** arr, int leftFirst, int leftLast, int rightFirst, int rightLast);

void mergeSort_age(player** arr, int first, int last)	//function definition
{
    //dividing array till 1 element is remaining in each division

    if (last > first)
    {
        int middle = (first + last) / 2;	//to keep track of middle

        //breaking array till we reach base case, then merging the array accordingly using merge function

        mergeSort_age(arr, first, middle);
        mergeSort_age(arr, middle + 1, last);
        merge_age(arr, first, middle, middle + 1, last);
    }
}

void merge_age(player** arr, int leftFirst, int leftLast, int rightFirst, int rightLast)
{
    //to save the value of leftfirst as we will be updating it throughout the code.

    int saveFirst = leftFirst;

    int i = leftFirst;	//to keep index of array we need to update in temp array

    //going through given array indexes and updating values in temp array till we finish one of the lists

    while ((leftLast >= leftFirst) && (rightLast >= rightFirst))
    {
        if (arr[leftFirst]->age > arr[rightFirst]->age)
        {
            tempArray[i] = arr[leftFirst];
            leftFirst++;
        }
        else
        {
            tempArray[i] = arr[rightFirst];
            rightFirst++;
        }

        i++;
    }

    //moving values from left, if any are remaining

    while (leftFirst <= leftLast)
    {
        tempArray[i++] = arr[leftFirst++];
    }

    //moving values from right, if any are remaining

    while (rightFirst <= rightLast)
    {
        tempArray[i++] = arr[rightFirst++];
    }

//now updating orignal array according to tempArray, by using our left index saved in savefirst


    for (int x = saveFirst; x <= rightLast; x++)
    {
        arr[x] = tempArray[x];
    }
}


//merge sort for value

void merge_value(player** arr, int leftFirst, int leftLast, int rightFirst, int rightLast);

void mergeSort_value(player** arr, int first, int last)	//function definition
{
    //dividing array till 1 element is remaining in each division

    if (last > first)
    {
        int middle = (first + last) / 2;	//to keep track of middle

        //breaking array till we reach base case, then merging the array accordingly using merge function

        mergeSort_value(arr, first, middle);
        mergeSort_value(arr, middle + 1, last);
        merge_value(arr, first, middle, middle + 1, last);
    }
}

void merge_value(player** arr, int leftFirst, int leftLast, int rightFirst, int rightLast)
{
    //to save the value of leftfirst as we will be updating it throughout the code.

    int saveFirst = leftFirst;

    int i = leftFirst;	//to keep index of array we need to update in temp array

    //going through given array indexes and updating values in temp array till we finish one of the lists

    while ((leftLast >= leftFirst) && (rightLast >= rightFirst))
    {
        if (arr[leftFirst]->value > arr[rightFirst]->value)
        {
            tempArray[i] = arr[leftFirst];
            leftFirst++;
        }
        else
        {
            tempArray[i] = arr[rightFirst];
            rightFirst++;
        }

        i++;
    }

    //moving values from left, if any are remaining

    while (leftFirst <= leftLast)
    {
        tempArray[i++] = arr[leftFirst++];
    }

    //moving values from right, if any are remaining

    while (rightFirst <= rightLast)
    {
        tempArray[i++] = arr[rightFirst++];
    }

//now updating orignal array according to tempArray, by using our left index saved in savefirst


    for (int x = saveFirst; x <= rightLast; x++)
    {
        arr[x] = tempArray[x];
    }
}


//merge sort for release_clause

void merge_release_clause(player** arr, int leftFirst, int leftLast, int rightFirst, int rightLast);

void mergeSort_release_clause(player** arr, int first, int last)	//function definition
{
    //dividing array till 1 element is remaining in each division

    if (last > first)
    {
        int middle = (first + last) / 2;	//to keep track of middle

        //breaking array till we reach base case, then merging the array accordingly using merge function

        mergeSort_release_clause(arr, first, middle);
        mergeSort_release_clause(arr, middle + 1, last);
        merge_release_clause(arr, first, middle, middle + 1, last);
    }
}

void merge_release_clause(player** arr, int leftFirst, int leftLast, int rightFirst, int rightLast)
{
    //to save the value of leftfirst as we will be updating it throughout the code.

    int saveFirst = leftFirst;

    int i = leftFirst;	//to keep index of array we need to update in temp array

    //going through given array indexes and updating values in temp array till we finish one of the lists

    while ((leftLast >= leftFirst) && (rightLast >= rightFirst))
    {
        if (arr[leftFirst]->release_clause > arr[rightFirst]->release_clause)
        {
            tempArray[i] = arr[leftFirst];
            leftFirst++;
        }
        else
        {
            tempArray[i] = arr[rightFirst];
            rightFirst++;
        }

        i++;
    }

    //moving values from left, if any are remaining

    while (leftFirst <= leftLast)
    {
        tempArray[i++] = arr[leftFirst++];
    }

    //moving values from right, if any are remaining

    while (rightFirst <= rightLast)
    {
        tempArray[i++] = arr[rightFirst++];
    }

//now updating orignal array according to tempArray, by using our left index saved in savefirst


    for (int x = saveFirst; x <= rightLast; x++)
    {
        arr[x] = tempArray[x];
    }
}


//merge sort for height

void merge_height(player** arr, int leftFirst, int leftLast, int rightFirst, int rightLast);

void mergeSort_height(player** arr, int first, int last)	//function definition
{
    //dividing array till 1 element is remaining in each division

    if (last > first)
    {
        int middle = (first + last) / 2;	//to keep track of middle

        //breaking array till we reach base case, then merging the array accordingly using merge function

        mergeSort_height(arr, first, middle);
        mergeSort_height(arr, middle + 1, last);
        merge_height(arr, first, middle, middle + 1, last);
    }
}

void merge_height(player** arr, int leftFirst, int leftLast, int rightFirst, int rightLast)
{
    //to save the value of leftfirst as we will be updating it throughout the code.

    int saveFirst = leftFirst;

    int i = leftFirst;	//to keep index of array we need to update in temp array

    //going through given array indexes and updating values in temp array till we finish one of the lists

    while ((leftLast >= leftFirst) && (rightLast >= rightFirst))
    {
        if (arr[leftFirst]->height > arr[rightFirst]->height)
        {
            tempArray[i] = arr[leftFirst];
            leftFirst++;
        }
        else
        {
            tempArray[i] = arr[rightFirst];
            rightFirst++;
        }

        i++;
    }

    //moving values from left, if any are remaining

    while (leftFirst <= leftLast)
    {
        tempArray[i++] = arr[leftFirst++];
    }

    //moving values from right, if any are remaining

    while (rightFirst <= rightLast)
    {
        tempArray[i++] = arr[rightFirst++];
    }

//now updating orignal array according to tempArray, by using our left index saved in savefirst


    for (int x = saveFirst; x <= rightLast; x++)
    {
        arr[x] = tempArray[x];
    }
}


//merge sort for weight

void merge_weight(player** arr, int leftFirst, int leftLast, int rightFirst, int rightLast);

void mergeSort_weight(player** arr, int first, int last)	//function definition
{
    //dividing array till 1 element is remaining in each division

    if (last > first)
    {
        int middle = (first + last) / 2;	//to keep track of middle

        //breaking array till we reach base case, then merging the array accordingly using merge function

        mergeSort_weight(arr, first, middle);
        mergeSort_weight(arr, middle + 1, last);
        merge_weight(arr, first, middle, middle + 1, last);
    }
}

void merge_weight(player** arr, int leftFirst, int leftLast, int rightFirst, int rightLast)
{
    //to save the value of leftfirst as we will be updating it throughout the code.

    int saveFirst = leftFirst;

    int i = leftFirst;	//to keep index of array we need to update in temp array

    //going through given array indexes and updating values in temp array till we finish one of the lists

    while ((leftLast >= leftFirst) && (rightLast >= rightFirst))
    {
        if (arr[leftFirst]->weight > arr[rightFirst]->weight)
        {
            tempArray[i] = arr[leftFirst];
            leftFirst++;
        }
        else
        {
            tempArray[i] = arr[rightFirst];
            rightFirst++;
        }

        i++;
    }

    //moving values from left, if any are remaining

    while (leftFirst <= leftLast)
    {
        tempArray[i++] = arr[leftFirst++];
    }

    //moving values from right, if any are remaining

    while (rightFirst <= rightLast)
    {
        tempArray[i++] = arr[rightFirst++];
    }

//now updating orignal array according to tempArray, by using our left index saved in savefirst


    for (int x = saveFirst; x <= rightLast; x++)
    {
        arr[x] = tempArray[x];
    }
}


//merge sort for wage

void merge_wage(player** arr, int leftFirst, int leftLast, int rightFirst, int rightLast);

void mergeSort_wage(player** arr, int first, int last)	//function definition
{
    //dividing array till 1 element is remaining in each division

    if (last > first)
    {
        int middle = (first + last) / 2;	//to keep track of middle

        //breaking array till we reach base case, then merging the array accordingly using merge function

        mergeSort_wage(arr, first, middle);
        mergeSort_wage(arr, middle + 1, last);
        merge_wage(arr, first, middle, middle + 1, last);
    }
}

void merge_wage(player** arr, int leftFirst, int leftLast, int rightFirst, int rightLast)
{
    //to save the value of leftfirst as we will be updating it throughout the code.

    int saveFirst = leftFirst;

    int i = leftFirst;	//to keep index of array we need to update in temp array

    //going through given array indexes and updating values in temp array till we finish one of the lists

    while ((leftLast >= leftFirst) && (rightLast >= rightFirst))
    {
        if (arr[leftFirst]->wage > arr[rightFirst]->wage)
        {
            tempArray[i] = arr[leftFirst];
            leftFirst++;
        }
        else
        {
            tempArray[i] = arr[rightFirst];
            rightFirst++;
        }

        i++;
    }

    //moving values from left, if any are remaining

    while (leftFirst <= leftLast)
    {
        tempArray[i++] = arr[leftFirst++];
    }

    //moving values from right, if any are remaining

    while (rightFirst <= rightLast)
    {
        tempArray[i++] = arr[rightFirst++];
    }

//now updating orignal array according to tempArray, by using our left index saved in savefirst


    for (int x = saveFirst; x <= rightLast; x++)
    {
        arr[x] = tempArray[x];
    }
}



/*void MainWindow::on_pushButton_clicked()
{
    player* temporary_ptr = tree1->search_player(ui->lineEdit->text(), tree1->root);

    if (temporary_ptr == NULL)
    {
        QMessageBox::critical(this, "error", "no player with this name exists!");
    }
    else
    {
        ui->label_2->setText(temporary_ptr->name);
        ui->label->setText(QString::number(temporary_ptr->age));
    }
}*/


/*void MainWindow::on_pushButton_2_clicked()  //takes data of selected row in listwidget
{
    //QListWidgetItem *item1;

    //item1 = ui->listWidget->currentItem();

    //item1->data(0);

    //ui->listWidget->selectedItems();

    QModelIndexList selection = ui->listWidget->selectionModel()->selectedRows();

    if (selection.count() != 1)
    {
        qDebug() << "no row selected";
        return;
    }

    QModelIndex index = selection.at(0);

    //qDebug() << index.row();

    //int row_no = index.row();

    //QSqlRecord record = model->record(row_no);

    qDebug() << index.data();

    ui->label_2->setText(index.data().toString());

}*/


void MainWindow::on_pushButton_clicked()
{
    QString temp = ui->lineEdit->text();

    AVL_Node_NC *temp1 = club->search_NC(temp, club->root);
    AVL_Node_NC *temp2 = country->search_NC(temp, country->root);
    player *temp3 = tree1->search_player(temp, tree1->root);

    if (temp1 != NULL)
    {
        display_club(temp1);
    }
    else if (temp2 != NULL)
    {
        display_country(temp2);
    }
    else if (temp3 != NULL)
    {
        display_player(temp3);
    }
    else
    {
        QMessageBox::critical(this, "Error", "No player, club or country exists with this name!");
    }
}

void MainWindow::display_club(AVL_Node_NC* temp)
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->label_2->setText(temp->data);

    ui->listWidget->clear();

    temp->list->Loc_ = temp->list->start;

    while (temp->list->Loc_ != NULL)
    {
        ui->listWidget->addItem(temp->list->Loc_->data->name);
        temp->list->Loc_ = temp->list->Loc_->next;
    }
}

void MainWindow::display_country(AVL_Node_NC* temp)
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->label_3->setText(temp->data);

    ui->listWidget_2->clear();

    temp->list->Loc_ = temp->list->start;

    while (temp->list->Loc_ != NULL)
    {
        ui->listWidget_2->addItem(temp->list->Loc_->data->name);
        temp->list->Loc_ = temp->list->Loc_->next;
    }
}

void MainWindow::display_player(player* temp)
{
    ui->stackedWidget->setCurrentIndex(3);

    //qDebug() << temp->wage;
    ui->label_5->setText(temp->name);
    ui->label_7->setText(QString::number(temp->age));
    ui->label_13->setText("€" + QString::number(temp->wage));
    ui->label_17->setText(QString::number(temp->height) + "\"");
    ui->label_19->setText("€" + QString::number(temp->value));
    ui->label_21->setText("€" + QString::number(temp->release_clause));
    ui->label_9->setText(temp->club);
    ui->label_11->setText(temp->nationality);
    ui->label_15->setText(QString::number(temp->weight) + "lbs");
    if (temp->preffered == false)
        ui->label_25->setText("Left");
    else if (temp->preffered == true)
        ui->label_25->setText("Right");
    ui->label_27->setText(QString::number(temp->overall));
    ui->label_30->setText(temp->position);

}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit->setText("");
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit->setText("");
}


void MainWindow::on_pushButton_6_clicked()
{
    QModelIndexList selection = ui->listWidget_2->selectionModel()->selectedRows();

    if (selection.count() != 1)
    {
        QMessageBox::critical(this, "Error", "no row selected");
        return;
    }

    QModelIndex index = selection.at(0);

    //qDebug() << index.row();

    //int row_no = index.row();

    //QSqlRecord record = model->record(row_no);

    QString temp = index.data().toString();

    //ui->label_2->setText(index.data().toString());

    player* temp1 = tree1->search_player(temp, tree1->root);

    if (temp1 != NULL)
    {
        display_player(temp1);
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    QModelIndexList selection = ui->listWidget->selectionModel()->selectedRows();

    if (selection.count() != 1)
    {
        QMessageBox::critical(this, "Error", "no row selected");
        return;
    }

    QModelIndex index = selection.at(0);

    //qDebug() << index.row();

    //int row_no = index.row();

    //QSqlRecord record = model->record(row_no);

    QString temp = index.data().toString();

    //ui->label_2->setText(index.data().toString());

    player* temp1 = tree1->search_player(temp, tree1->root);

    if (temp1 != NULL)
    {
        display_player(temp1);
    }
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit->setText("");
}


void MainWindow::on_pushButton_8_clicked()
{
    AVL_Node_NC *temp = club->search_NC(ui->label_9->text(), club->root);

    if (temp != NULL)
        display_club(temp);
}


void MainWindow::on_pushButton_9_clicked()
{
    AVL_Node_NC *temp = country->search_NC(ui->label_11->text(), country->root);

    if (temp != NULL)
        display_country(temp);
}



void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

    ui->listWidget_3->clear();

    for (int i = 0; i < 13000; i++)
    {
        if (array1[i].name != "")
            ui->listWidget_3->addItem(array1[i].name);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

    ui->listWidget_3->clear();

    for (int i = 0; i < 13000; i++)
    {
        if ((*age[i]).name != "")
            ui->listWidget_3->addItem((*age[i]).name);
    }
}


void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

    ui->listWidget_3->clear();

    for (int i = 0; i < 13000; i++)
    {
        if ((*value[i]).name != "")
            ui->listWidget_3->addItem((*value[i]).name);
    }
}


void MainWindow::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

    ui->listWidget_3->clear();

    for (int i = 0; i < 13000; i++)
    {
        if ((*release_clause[i]).name != "")
            ui->listWidget_3->addItem((*release_clause[i]).name);
    }
}


void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

    ui->listWidget_3->clear();

    for (int i = 0; i < 13000; i++)
    {
        if ((*wage[i]).name != "")
            ui->listWidget_3->addItem((*wage[i]).name);
    }
}


void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

    ui->listWidget_3->clear();

    for (int i = 0; i < 13000; i++)
    {
        if ((*height[i]).name != "")
            ui->listWidget_3->addItem((*height[i]).name);
    }
}


void MainWindow::on_pushButton_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

    ui->listWidget_3->clear();

    for (int i = 0; i < 13000; i++)
    {
        if ((*weight[i]).name != "")
        ui->listWidget_3->addItem((*weight[i]).name);
    }
}


void MainWindow::on_pushButton_19_clicked()
{
    QModelIndexList selection = ui->listWidget_3->selectionModel()->selectedRows();

    if (selection.count() != 1)
    {
        QMessageBox::critical(this, "Error", "no row selected");
        return;
    }

    QModelIndex index = selection.at(0);

    //qDebug() << index.row();

    //int row_no = index.row();

    //QSqlRecord record = model->record(row_no);

    QString temp = index.data().toString();

    //ui->label_2->setText(index.data().toString());

    player* temp1 = tree1->search_player(temp, tree1->root);

    if (temp1 != NULL)
    {
        display_player(temp1);
    }
}


void MainWindow::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit->setText("");
}

