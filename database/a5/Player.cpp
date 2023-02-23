#include <iostream>
#include <string>
#include "cmpt_error.h" 
#include "Player.h"

using namespace std;

string Player::getName()const { return mName; }
string Player::getTeam()const { return mTeam; }
string Player::getMPA()const { return mAgent; }
int Player::getACS()const { return mAcs; }
