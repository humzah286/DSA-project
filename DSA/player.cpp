#include "player.h"
using namespace std;

player::player()
{
    ID = 0;
    name = "";
    age = 0;
    nationality = "";		//
    overall = 0;
    club = "";			//
    value = 0;
    wage = 0;
    preffered = true;			//0 left
    position = "";
    jersey_no = 0;
    height = 0;
    weight = 0;
    release_clause = 0;
}


/*void parser(player* arr)
{
    ifstream myfile;
    myfile.open("data.csv");
    string line;
    string temp;
    getline(myfile, line, '\n');

    for (int i = 0; i < 1; i++)
    {
        player* newplayer = new player;

        getline(myfile, line, ',');

        //ID
        getline(myfile, line, ',');
        newplayer->ID = stoi(line);

        //name
        getline(myfile, line, ',');

        for (int j = 0; j < int(line.length()); j++)
        {
            if (line[j] == '.')
            {
                newplayer->name = line.substr(3, line.length() - 1);
                break;
            }
        }

        if (newplayer->name == "") newplayer->name = line;

        //age
        getline(myfile, line, ',');
        newplayer->age = stoi(line);

        //country
        getline(myfile, line, ',');
        newplayer->nationality = line;

        //overall
        getline(myfile, line, ',');
        newplayer->overall = stoi(line);

        //club
        getline(myfile, line, ',');
        newplayer->club = line;

        //value
        getline(myfile, line, ',');
        cout << line << endl;
        if (line[line.length() - 1] == 'M')
            newplayer->value += stof(line.substr(1, line.length() - 2)) * 1000000;
        else if (line[line.length() - 1] == 'K')
            newplayer->value += stof(line.substr(1, line.length() - 2)) * 1000;


        arr[i] = *newplayer;
    }

}*/



