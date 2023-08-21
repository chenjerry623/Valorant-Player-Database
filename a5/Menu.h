#include <iostream>
#include <numeric>
#include <string>

#include "Database.h"

using namespace std;

class Menu
{
private:

    string input;

    Database db;

public:

    Menu();
    virtual ~Menu();
    void main_menu();
    void list();
    void searchPlayer();
    void addPlayer();
    void deletePlayer();
    void listAll();
    void quit();

private:

    bool isNumber(const string& s);
    void printPlayers(vector<Player>& arr);
    bool deleteConfirm();
    void returnToMenu();
};