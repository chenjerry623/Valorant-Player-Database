#include <iostream>
#include <numeric>
#include <string>

#include "Menu.h"



using namespace std;

Menu::Menu()
{
    bool result = db.init("database.txt");
    if (result == false)
    {
        cmpt::error("Failed to read database");
    }
    else
    {
        main_menu();
    }
}

Menu::~Menu()
{
    cout << "Menu destructor called...\n";
}

void Menu::main_menu()
{
    cout << "/------------------------------------\\" << endl;
    cout << "|Welcome to Valorant Player Database!|" << endl;
    cout << "\\------------------------------------/" << endl << endl;

    cout << "If you would like to: " << endl;
    cout << "(A) Add a player to the database" << endl;
    cout << "(B) Remove a player from the database" << endl;
    cout << "(C) Search for a player in the database" << endl;
    cout << "(D) List all records in database" << endl;
    cout << "(Q) Quit" << endl;

    cout << "Enter the corresponding letter: ";
    cin >> input;
    cout << endl;
    cin.ignore(1, '\n');

    while (input != "C" && input != "c" && input != "A" && input != "a"
        && input != "B" && input != "b" && input != "D" && input != "d"
        && input != "Q" && input != "q")
    {
        cout << "Please enter a corresponding letter: ";
        cin >> input;
        cout << endl;
        cin.ignore(1, '\n');
    }

    if (input == "C" || input == "c")
    {
        searchPlayer();
    }
    else if (input == "A" || input == "a")
    {
        addPlayer();
    }
    else if (input == "B" || input == "b")
    {
        deletePlayer();
    }
    else if (input == "D" || input == "d")
    {
        list();
    }
    else if (input == "Q" || input == "q")
    {
        quit();
    }
}

void Menu::list()
{
    vector<Player> sortedArr;
    Database::FIELD field;
    cout << "Which field would you like to list based on?" << endl;
    cout << "(N)ame" << endl;
    cout << "(T)eam" << endl;
    cout << "(M)ost Played Agent" << endl;
    cout << "(A)CS" << endl;
    cout << "(R)eturn to menu" << endl;

    while (input != "N" && input != "n" && input != "T" && input != "t"
        && input != "M" && input != "m" && input != "A" && input != "a"
        && input != "R" && input != "r")
    {
        cout << "Please enter a corresponding letter: ";
        cin >> input;
        cout << endl;
        cin.ignore(1, '\n');
    }

    if (input == "N" || input == "n")
    {
        field = Database::FIELD_NAME;
    }

    else if (input == "T" || input == "t")
    {
        field = Database::FIELD_TEAM;
    }

    else if (input == "M" || input == "m")
    {
        field = Database::FIELD_AGENT;
    }

    else if (input == "A" || input == "a")
    {
        field = Database::FIELD_ACS;
    }

    if (input == "N" || input == "n" || input == "T" || input == "t"
        || input == "M" || input == "m")
    {
        cout << "How do you want your players sorted: " << endl;
        cout << "(A)scending (alphabetical)" << endl;
        cout << "(D)escending (alphabetical)" << endl;
        cin >> input;
        cout << endl;
        cin.ignore(1, '\n');

        if (input == "A" || input == "a")
        {
            sortedArr = db.listPlayer(field, true);
            printPlayers(sortedArr);
            returnToMenu();
        }

        else if (input == "D" || input == "d")
        {
            sortedArr = db.listPlayer(field, false);
            printPlayers(sortedArr);
            returnToMenu();
        }
    }

    else if (input == "A" || input == "a")
    {
        cout << "How do you want your players sorted: " << endl;
        cout << "(A)scending" << endl;
        cout << "(D)escending" << endl;
        cin >> input;
        cout << endl;
        cin.ignore(1, '\n');

        if (input == "A" || input == "a")
        {
            sortedArr = db.listPlayer(field, true);
            printPlayers(sortedArr);
            returnToMenu();
        }

        else if (input == "D" || input == "d")
        {
            sortedArr = db.listPlayer(field, false);
            printPlayers(sortedArr);
            returnToMenu();
        }

    }

    else
    {
        main_menu();
    }
}

void Menu::searchPlayer()
{
    string choice;

    // reset the input every time a new function is entered
    cout << "Find a Player\n-----------" << endl << endl;
    cout << "You can search by their: " << endl << endl;
    cout << "(N)ame" << endl;
    cout << "(T)eam" << endl;
    cout << "(M)ost played agent" << endl;
    cout << "(A)CS/average combat score" << endl;
    cout << "or" << endl;
    cout << "(R)eturn to main menu" << endl << endl;
    cout << "Enter the letter of your choice: ";
    cin >> input;

    // cin ignore needs to be placed after every cin to remove whitespace
    cin.ignore(1, '\n');

    while (input != "N" && input != "T" && input != "M" && input != "A" && input != "R"
        && input != "n" && input != "t" && input != "m" && input != "a" && input != "r")
    {
        cout << "Please enter a letter corresponding to your choice: " << endl;
        cin >> input;
        cin.ignore(1, '\n');
    }

    if (input == "N" || input == "n")
    {
        cout << endl;
        cout << "Would you like to search for an exact match or any name which contains your search?" << endl;
        cout << "(E)xact match of my input" << endl;
        cout << "(A)ny name which has my input in it" << endl;
        cout << "Enter the letter of your choice: ";
        cin >> choice;
        cin.ignore(1, '\n');

        while (choice != "E" && choice != "A"
            && choice != "e" && choice != "a")
        {
            cout << "Please enter a letter corresponding to your choice: " << endl;
            cin >> choice;
            cin.ignore(1, '\n');
        }

        cout << "Please enter the name you wish to search for: ";
        getline(cin, input);

        vector<Player> searchResults;

        if (choice == "E" || choice == "e")
        {
            searchResults = db.doFindPlayerByStringField(Database::FIELD_NAME, true, input);
        }

        else if (choice == "A" || choice == "a")
        {
            searchResults = db.doFindPlayerByStringField(Database::FIELD_NAME, false, input);
        }
        cout << endl;
        cout << "Here are the results of your search: " << endl;
        printPlayers(searchResults);

        cout << "(R) to return to menu: ";
        cin >> input;
        cin.ignore(1, '\n');
        if (input == "R" || input == "r")
        {
            main_menu();
        }
    }

    else if (input == "T" || input == "t")
    {
        cout << endl;
        cout << "Would you like to search for an exact match or any name which contains your search?" << endl;
        cout << "(E)xact match of my input" << endl;
        cout << "(A)ny name which has my input in it" << endl;
        cout << "Enter the letter of your choice: ";
        cin >> choice;
        cin.ignore(1, '\n');

        while (choice != "E" && choice != "A"
            && choice != "e" && choice != "a")
        {
            cout << "Please enter a letter corresponding to your choice: " << endl;
            cin >> choice;
            cin.ignore(1, '\n');
        }

        cout << "Please enter the team you wish to search for: ";
        getline(cin, input);

        vector<Player> searchResults;

        if (choice == "E" || choice == "e")
        {
            searchResults = db.doFindPlayerByStringField(Database::FIELD_TEAM, true, input);
        }

        else if (choice == "A" || choice == "a")
        {
            searchResults = db.doFindPlayerByStringField(Database::FIELD_TEAM, false, input);
        }
        cout << endl;
        cout << "Here are the results of your search: " << endl;
        printPlayers(searchResults);

        cout << "(R) to return to menu: ";
        cin >> input;
        cin.ignore(1, '\n');
        if (input == "R" || input == "r")
        {
            main_menu();
        }
    }

    else if (input == "M" || input == "m")
    {
        cout << endl;
        cout << "Would you like to search for an exact match or any name which contains your search?" << endl;
        cout << "(E)xact match of my input" << endl;
        cout << "(A)ny name which has my input in it" << endl;
        cout << "Enter the letter of your choice: ";
        cin >> choice;
        cin.ignore(1, '\n');

        while (choice != "E" && choice != "A"
            && choice != "e" && choice != "a")
        {
            cout << "Please enter a letter corresponding to your choice: " << endl;
            cin >> choice;
            cin.ignore(1, '\n');
        }

        cout << "Please enter the agent you wish to search for: ";
        getline(cin, input);

        vector<Player> searchResults;

        if (choice == "E" || choice == "e")
        {
            searchResults = db.doFindPlayerByStringField(Database::FIELD_AGENT, true, input);
        }

        else if (choice == "A" || choice == "a")
        {
            searchResults = db.doFindPlayerByStringField(Database::FIELD_AGENT, false, input);
        }
        cout << endl;
        cout << "Here are the results of your search: " << endl;
        printPlayers(searchResults);

        cout << "(R) to return to menu: ";
        cin >> input;
        cin.ignore(1, '\n');
        if (input == "R" || input == "r")
        {
            main_menu();
        }
    }

    else if (input == "A" || input == "a")
    {
        cout << endl;
        cout << "Would you like to search for an exact number or values between a range of numbers?" << endl;
        cout << "(E)xact number" << endl;
        cout << "(R)ange of numbers" << endl;
        cout << "Enter the letter of your choice: ";
        cin >> choice;
        cin.ignore(1, '\n');

        while (choice != "E" && choice != "R"
            && choice != "e" && choice != "r")
        {
            cout << "Please enter a letter corresponding to your choice: " << endl;
            cin >> choice;
            cin.ignore(1, '\n');
        }

        vector<Player> searchResults;

        if (choice == "E" || choice == "e")
        {
            cout << "Please enter the ACS you wish to search for: ";
            getline(cin, input);
            searchResults = db.doFindPlayerByNumberField(Database::FIELD_ACS, true, stoi(input), 0);
        }

        else if (input == "A" || input == "a")
        {
            int low;
            int high;
            cout << "Please enter the minimum ACS: ";
            cin >> low;
            cin.ignore(1, '\n');
            cout << endl;
            cout << "Please enter the maximum ACS: ";
            cin >> high;
            cin.ignore(1, '\n');
            searchResults = db.doFindPlayerByNumberField(Database::FIELD_ACS, false, low, high);
        }
        cout << endl;
        cout << "Here are the results of your search: " << endl;
        printPlayers(searchResults);

        cout << "(R) to return to menu: ";
        cin >> input;
        cin.ignore(1, '\n');
        if (input == "R" || input == "r")
        {
            main_menu();
        }
    }
}

void Menu::addPlayer()
{
    string  name;
    string  team;
    string  agent;
    int     score;

    /////////////////// Enter Name ///////////////////

    cout << "please enter the player's name: ";
    getline(cin, name);
    cout << endl;

    while (name.length() == 0 || db.findPlayer(Database::FIELD_NAME, true, name).size() > 0 || name.length() > 19)
    {
        if (name.length() == 0)
        {
            cout << "please enter a valid player name: ";
        }

        else if (name.length() > 19)
        {
            cout << "please enter a shorter player name(19 characters or less): ";
        }
        else
        {
            cout << "the player already exists in the database, please enter another player name: ";
        }

        getline(cin, name);
        cout << endl;
    }

    /////////////////// Enter Team ///////////////////

    cout << "please enter the player's team: ";
    getline(cin, team);
    cout << endl;

    while (team.length() == 0 || team.length() > 19)
    {

        if (team.length() == 0)
        {
            cout << "please enter a valid player team: ";
        }

        else if (team.length() > 19)
        {
            cout << "please enter a shorter team name(19 characters or less): ";
        }

        getline(cin, team);
        cout << endl;
    }

    /////////////////// Enter Agent ///////////////////

    cout << "please enter the player's favorite agent: ";
    getline(cin, agent);
    cout << endl;

    while (agent.length() == 0 || agent.length() > 19)
    {
        if (agent.length() == 0)
        {
            cout << "please enter a valid player's favorite agent: ";
        }

        else if (agent.length() > 19)
        {
            cout << "please enter a shorter agent name(19 characters or less): ";
        }

        getline(cin, agent);
        cout << endl;
    }

    /////////////////// Enter ACS ///////////////////

    cout << "please enter the player's ACS (Average Combat Score): ";
    cin >> score;
    cin.ignore(1, '\n');
    cout << endl;

    while (score <= 0)
    {
        cout << "please enter a valid player's ACS which must be greater than 0: ";
        cin >> score;
        cin.ignore(1, '\n');
        cout << endl;
    }

    // add player to database
    Player player(name, team, agent, score);
    db.addPlayer(player);

    cout << "Player Added" << endl;
    cout << "(R) to return to menu: ";
    cin >> input;
    cin.ignore(1, '\n');

    if (input == "R" || input == "r")
    {
        cout << endl;
        cout << endl;
        main_menu();
    }
}

void Menu::deletePlayer()
{
    bool exact;
    string choice;
    cout << "Delete a Player\n-----------" << endl << endl;
    cout << "You can delete by their: " << endl << endl;
    cout << "(N)ame" << endl;
    cout << "(T)eam" << endl;
    cout << "(M)ost played agent" << endl;
    cout << "(A)CS/average combat score" << endl;
    cout << "or" << endl;
    cout << "(R)eturn to main menu" << endl << endl;
    cout << "Enter the letter of your choice: ";
    cin >> input;
    cin.ignore(1, '\n');

    while (input != "N" && input != "T" && input != "M" && input != "A" && input != "R"
        && input != "n" && input != "t" && input != "m" && input != "a" && input != "r")
    {
        cout << "Please enter a letter corresponding to your choice: " << endl;
        cin >> input;
        cin.ignore(1, '\n');
    }

    if (input == "N" || input == "n")
    {
        cout << endl;
        cout << "Would you like to search for an exact match or any name which contains your search?" << endl;
        cout << "(E)xact match of my input" << endl;
        cout << "(A)ny name which has my input in it" << endl;
        cout << "Enter the letter of your choice: ";
        cin >> choice;
        cin.ignore(1, '\n');

        while (choice != "E" && choice != "A"
            && choice != "e" && choice != "a")
        {
            cout << "Please enter a letter corresponding to your choice: " << endl;
            cin >> choice;
            cin.ignore(1, '\n');
        }

        cout << "Please enter the name you wish to search for: ";
        getline(cin, input);

        vector<Player> searchResults;

        // keep track of whether the user wants specific or substring

        if (choice == "E" || choice == "e")
        {
            exact = true;
            searchResults = db.doFindPlayerByStringField(Database::FIELD_NAME, true, input);
        }

        else if (choice == "A" || choice == "a")
        {
            exact = false;
            searchResults = db.doFindPlayerByStringField(Database::FIELD_NAME, false, input);
        }
        cout << endl;
        cout << "Here are the results of your search: " << endl;
        printPlayers(searchResults);

        bool confirm = deleteConfirm();

        if (confirm)
        {
            db.doDeletePlayerByStringField(Database::FIELD_NAME, exact, input);
            cout << "Player(s) deleted" << endl;
            returnToMenu();
        }

        else
        {
            main_menu();
        }
    }

    else if (input == "T" || input == "t")
    {
        cout << endl;
        cout << "Would you like to search for an exact match or any name which contains your search?" << endl;
        cout << "(E)xact match of my input" << endl;
        cout << "(A)ny name which has my input in it" << endl;
        cout << "Enter the letter of your choice: ";
        cin >> choice;
        cin.ignore(1, '\n');

        while (choice != "E" && choice != "A"
            && choice != "e" && choice != "a")
        {
            cout << "Please enter a letter corresponding to your choice: " << endl;
            cin >> choice;
            cin.ignore(1, '\n');
        }

        cout << "Please enter the team you wish to search for: ";
        getline(cin, input);

        vector<Player> searchResults;

        // keep track of whether the user wants specific or substring

        if (choice == "E" || choice == "e")
        {
            exact = true;
            searchResults = db.doFindPlayerByStringField(Database::FIELD_TEAM, true, input);
        }

        else if (choice == "A" || choice == "a")
        {
            exact = false;
            searchResults = db.doFindPlayerByStringField(Database::FIELD_TEAM, false, input);
        }
        cout << endl;
        cout << "Here are the results of your search: " << endl;
        printPlayers(searchResults);

        bool confirm = deleteConfirm();

        if (confirm)
        {
            db.doDeletePlayerByStringField(Database::FIELD_TEAM, exact, input);
            cout << "Player(s) deleted" << endl;
            returnToMenu();
        }

        else
        {
            main_menu();
        }
    }

    else if (input == "M" || input == "m")
    {
        cout << endl;
        cout << "Would you like to search for an exact match or any name which contains your search?" << endl;
        cout << "(E)xact match of my input" << endl;
        cout << "(A)ny name which has my input in it" << endl;
        cout << "Enter the letter of your choice: ";
        cin >> choice;
        cin.ignore(1, '\n');

        while (choice != "E" && choice != "A"
            && choice != "e" && choice != "a")
        {
            cout << "Please enter a letter corresponding to your choice: " << endl;
            cin >> choice;
            cin.ignore(1, '\n');
        }

        cout << "Please enter the agent you wish to search for: ";
        getline(cin, input);

        vector<Player> searchResults;

        // keep track of whether the user wants specific or substring

        if (choice == "E" || choice == "e")
        {
            exact = true;
            searchResults = db.doFindPlayerByStringField(Database::FIELD_AGENT, true, input);
        }

        else if (choice == "A" || choice == "a")
        {
            exact = false;
            searchResults = db.doFindPlayerByStringField(Database::FIELD_AGENT, false, input);
        }
        cout << endl;
        cout << "Here are the results of your search: " << endl;
        printPlayers(searchResults);

        bool confirm = deleteConfirm();

        if (confirm)
        {
            db.doDeletePlayerByStringField(Database::FIELD_AGENT, exact, input);
            cout << "Player(s) deleted" << endl;
            returnToMenu();
        }

        else
        {
            main_menu();
        }
    }

    else if (input == "A" || input == "a")
    {
        cout << endl;
        cout << "Would you like to search for an exact number or values between a range of numbers?" << endl;
        cout << "(E)xact number" << endl;
        cout << "(R)ange of numbers" << endl;
        cout << "Enter the letter of your choice: ";
        cin >> choice;
        cin.ignore(1, '\n');

        while (choice != "E" && choice != "R"
            && choice != "e" && choice != "r")
        {
            cout << "Please enter a letter corresponding to your choice: " << endl;
            cin >> choice;
            cin.ignore(1, '\n');
        }

        vector<Player> searchResults;

        int low;
        int high;

        if (choice == "E" || choice == "e")
        {
            cout << "Please enter the ACS you wish to search for: ";
            cin >> low;
            cin.ignore(1, '\n');
            exact = true;
            high = 0;
            searchResults = db.doFindPlayerByNumberField(Database::FIELD_ACS, true, stoi(input), 0);
        }

        else if (input == "A" || input == "a")
        {
            cout << "Please enter the minimum ACS: ";
            cin >> low;
            cin.ignore(1, '\n');
            cout << endl;
            cout << "Please enter the maximum ACS: ";
            cin >> high;
            cin.ignore(1, '\n');
            exact = false;
            searchResults = db.doFindPlayerByNumberField(Database::FIELD_ACS, false, low, high);
        }
        cout << endl;
        cout << "Here are the results of your search: " << endl;
        printPlayers(searchResults);

        bool confirm = deleteConfirm();

        if (confirm)
        {
            db.doDeletePlayerByNumberField(Database::FIELD_AGENT, exact, low, high);
            cout << "Player(s) deleted" << endl;
            returnToMenu();
        }

        else
        {
            main_menu();
        }
    }

}

void Menu::listAll()
{
    cout << setw(20) << "NAME" << setw(20) << "TEAM" << setw(20) << "MOST PLAYED AGENT" << setw(20) << "ACS" << endl;
    for (int i = 0; i < db.getPlayers().size(); i++)
    {
        cout << setw(20) << db.getPlayers()[i].getName() << setw(20) << db.getPlayers()[i].getTeam() << setw(20) << db.getPlayers()[i].getMPA() << setw(20) << db.getPlayers()[i].getACS() << endl;
    }

    cout << "(R) to return to menu: ";
    cin >> input;
    cin.ignore(1, '\n');
    if (input == "R" || input == "r")
    {
        main_menu();
    }
}

void Menu::quit() {

    string yesno;
    cout << "are you sure you want to quit?" << endl;
    cout << "(Y)es to quit" << endl;
    cout << "(N)o to return to menu" << endl;
    cin >> yesno;
    cout << endl;
    cin.ignore(1, '\n');
    while (yesno != "Y" && yesno != "y"
        && yesno != "N" && yesno != "n")
    {
        cout << "Please enter either Y or N: ";
        cin >> yesno;
        cout << endl;
        cin.ignore(1, '\n');
    }

    if (yesno == "Y" || yesno == "y")
    {
        bool success = db.save();
        cout << "Saving database..." << endl;
        if (success)
        {
            cout << "Database successfully saved, closing program...";
            exit(0);
        }

        else
        {
            cout << "Database save failed, closing program...";
            exit(0);
        }

    }

}

//////////////// Helper functions /////////////////

bool Menu::isNumber(const string& s)
{
    for (char const& ch : s)
    {
        if (std::isdigit(ch) == 0)
        {
            return false;
        }
    }

    return true;
}

void Menu::printPlayers(vector<Player>& arr)
{
    cout << setw(20) << "NAME" << setw(20) << "TEAM" << setw(20) << "MOST PLAYED AGENT" << setw(20) << "ACS" << endl;
    for (int i = 0; i < arr.size(); i++)
    {
        cout << setw(20) << arr[i].getName() << setw(20) << arr[i].getTeam() << setw(20) << arr[i].getMPA() << setw(20) << arr[i].getACS() << endl;
    }
}

bool Menu::deleteConfirm()
{
    string yesno;
    cout << "Are you sure you want to delete these?" << endl;
    cout << "(Y)es" << endl;
    cout << "(N)o, return to menu";
    cin >> yesno;
    cout << endl;
    cin.ignore(1, '\n');

    while (yesno != "N" && yesno != "n"
        && yesno != "Y" && yesno != "y")
    {
        cout << "please enter either y or n";
        cin >> yesno;
        cout << endl;
        cin.ignore(1, '\n');
    }

    if (yesno == "N" || yesno == "n")
    {
        return false;
    }

    else {
        return true;
    }
}

void Menu::returnToMenu()
{
    cout << "(R) to return to menu: ";
    cin >> input;
    cin.ignore(1, '\n');

    if (input == "R" || input == "r")
    {
        cout << endl;
        cout << endl;
        main_menu();
    }
}
