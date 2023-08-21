#include <iostream>
#include <string>
#include "cmpt_error.h" 
using namespace std;


class Player
{
private:

    string mName;
    string mTeam;
    string mAgent;
    int mAcs;

public:

    // default constructor
    Player() :mName(""), mTeam(""), mAgent(""), mAcs(0) {};

    Player(string name, string team, string mpa, int acs)
        : mName(name),
        mTeam(team),
        mAgent(mpa),
        mAcs(acs)
    {};

    string getName()const;
    string getTeam()const;
    string getMPA()const;
    int getACS()const;

    ~Player(){};
};