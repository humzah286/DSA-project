#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QFile>
#include <QMessageBox>

class player
{
public:
    unsigned int ID;
    QString name;
    int age;
    QString nationality;		//
    char overall;
    QString club;			//
    long value;
    int wage;
    bool preffered;			//0 left
    QString position;
    char jersey_no;
    int height;
    short int weight;
    unsigned int release_clause;

public:
    player();
};

#endif // PLAYER_H
