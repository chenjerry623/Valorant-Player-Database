#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <algorithm>
#include "Player.h";
#include "cmpt_error.h" 

using namespace std;

class Database {
private:
	vector<Player> arr;

	const int NAME = 0;
	const int TEAM = 1;
	const int AGENT = 2;

public:

	// default constructor
	Database() {

	}

	// destructor
	~Database() {
		cout << "Database destroyed" << endl;
	}

	void add_Record(const string& name, const string& team, const string& agent, const int& acs)
	{
		Player newPlayer = Player(name, team, agent, acs);
		arr.push_back(newPlayer);
	}

	// function that finds the index of the player
	int findPlayer(string target) {
		for (int i = 0; i < arr.size(); i++)
		{
			if (arr[i].getName() == target)
			{
				return i;
			}
		}
	return -1;
	}

	// function that takes in the type of field and name to be found
	vector<Player> findField(const int& type, const string& target) {

		vector<Player> results;

		// search for diff type of entry depending on type
		if (type == NAME)
		{
			for (int i = 0; i < arr.size(); i++)
			{
				if (arr[i].getName().find(target) != string::npos)
				{
					results.push_back(arr[i]);
				}
			}
		}

		else if (type == TEAM)
		{
			for (int i = 0; i < arr.size(); i++)
			{
				if (arr[i].getTeam() == target)
				{
					results.push_back(arr[i]);
				}
			}
		}

		else if (type == AGENT)
		{
			for (int i = 0; i < arr.size(); i++)
			{
				if (arr[i].getMPA() == target)
				{
					results.push_back(arr[i]);
				}
			}
		}

		else
		{
			cmpt::error("invalid type input for findField");
		}

		return results;
	}

	vector<Player> findACS(const int& target)
	{
		vector<Player> results;

		for (int i = 0; i < arr.size(); i++)
		{
			if (arr[i].getACS() == target)
			{
				results.push_back(arr[i]);
			}
		}

		return results;
	}

	vector<Player> findACSRange(const int& range1, const int& range2)
	{
		if (range2 < range1)
		{
			int temp = range2;
			range2 = range1;
			range1 = temp;
		}

		vector<Player> results;
		for (int i = 0; i < arr.size(); i++)
		{
			if (arr[i].getACS() >= range1 && arr[i].getACS() <= range2)
			{
				results.push_back(arr[i]);
			}
		}
	}


	// deletes a record at the given index
	void deleteRecord(const int& index) {
		arr.erase(arr.begin() + index - 1);
	}

	// HELPER FUNCTIONS FOR LISTING
	// lets the sort function know what to compare
	bool ascendingCompare(const string& a, const string& b)
	{
		return a < b;
	}
	bool descendingCompare(const string& a, const string& b)
	{
		return b > a;
	}

	vector<Player> listAscending(const vector<Player>& list, const int& type)
	{
		if (type == NAME)
		{
			vector<string> names;
			for (int i = 0; i < list.size(); i++)
			{
				names.push_back(list[i].getName());
			}

			sort(names.begin(), names.begin() + names.size(), ascendingCompare);

			
		}
		
	}

};


int main()
{
	Database test;
	test.add_Record();
	
	return 0;
}
