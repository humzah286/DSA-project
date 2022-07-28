#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "player.h"
#include "AVL_Tree_player.h"
#include "AVL_Tree_NC.h"

#include <QMainWindow>
#include <QString>
#include <QTextStream>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void parser(player*);
    void display_club(AVL_Node_NC* temp);
    void display_country(AVL_Node_NC* temp);
    void display_player(player*);

private slots:

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();


    void on_pushButton_19_clicked();

    void on_pushButton_17_clicked();

private:
    Ui::MainWindow *ui;
    player *array1;
    player **age;
    player **value;
    player **wage;
    player **release_clause;
    player **height;
    player **weight;
    AVL_Tree_player* tree1;
    AVL_Tree_NC* country;
    AVL_Tree_NC* club;
};


#endif // MAINWINDOW_H
