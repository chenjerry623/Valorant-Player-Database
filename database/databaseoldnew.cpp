#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "Player.h"
#include "cmpt_error.h" 

using namespace std;

class Database
{
public:

	// make a field value so that functions know which type is being passed in
	enum FIELD {
		FIELD_NAME,
		FIELD_TEAM,
		FIELD_AGENT,
		FIELD_ACS
	};

private:
	// the separator for values when reading file
	const char DELIMITER = ',';
	const string ESCAPED_DELIMITER = "\\,\\";

	vector<Player> mPlayers;
	string mFilePath;

public:

	// default constructor
	Database() {}

	void addPlayer(Player& player)
	{
		mPlayers.push_back(player);
	}

	vector<Player> findPlayer(const FIELD field, bool exactMatch, string& target, int lowBoundary = 0, int highBoundary = 0) const
	{
		vector<Player> result;

		// evaluate and determine which type to search for
		switch (field)
		{
		case FIELD_NAME:
			result = doFindPlayerByName(exactMatch, target);
			break;

		case FIELD_TEAM:
			result = doFindPlayerByTeam(exactMatch, target);
			break;

		case FIELD_AGENT:
			result = doFindPlayerByAgent(exactMatch, target);
			break;

		case FIELD_ACS:
			result = doFindPlayerByAcs(exactMatch, lowBoundary, highBoundary);
			break;

		default:
			break;
		}

		return result;
	}

	void deletePlayer(const FIELD field, bool exactMatch, string& target, int lowBoundary, int highBoundary)
	{

		// determine which type to search for and delete
		switch (field)
		{
		case FIELD_NAME:
			doDeletePlayerByName(exactMatch, target);
			break;

		case FIELD_TEAM:
			doDeletePlayerByTeam(exactMatch, target);
			break;

		case FIELD_AGENT:
			doDeletePlayerByAgent(exactMatch, target);
			break;

		case FIELD_ACS:
			doDeletePlayerByAcs(exactMatch, lowBoundary, highBoundary);
			break;

		default:
			break;
		}
	}

	const vector<Player> listPlayer(const FIELD field, bool ascend) const
	{

		// calls copy constructor of vector to make a copy of mPlayers
		vector<Player> result(mPlayers);

		// evaluate type
		switch (field)
		{

			// call ascending/descending depending on input
		case FIELD_NAME:
			if (ascend)
			{
				sort(result.begin(), result.end(), string_ascend_name());
			}
			else
			{
				sort(result.begin(), result.end(), string_descend_name());
			}
			break;

		case FIELD_TEAM:
			if (ascend)
			{
				std::sort(result.begin(), result.end(), string_ascend_team());
			}
			else
			{
				std::sort(result.begin(), result.end(), string_descend_team());
			}
			break;

		case FIELD_AGENT:
			if (ascend)
			{
				std::sort(result.begin(), result.end(), string_ascend_agent());
			}
			else
			{
				std::sort(result.begin(), result.end(), string_descend_agent());
			}
			break;

		case FIELD_ACS:
			if (ascend)
			{
				std::sort(result.begin(), result.end(), number_ascend_asc());
			}
			else
			{
				std::sort(result.begin(), result.end(), number_descend_asc());
			}
			break;
		}

		return result;
	}

private:

	// function for searching by name
	vector<Player> doFindPlayerByName(bool exactMatch, string& target) const
	{
		vector<Player> result;

		// searches for matches, adds them into result vector if found
		for (int i = 0; i < mPlayers.size(); i++)
		{
			// t/f of if the match exists
			bool found = false;

			if (exactMatch)
			{
				if (mPlayers[i].getName() == target)
				{
					found = true;
				}
			}
			else
			{
				if (mPlayers[i].getName().find(target) != std::string::npos)
				{
					found = true;
				}
			}

			if (found)
			{
				result.push_back(mPlayers[i]);
			}
		}

		return result;
	}

	// function for searching by team
	vector<Player> doFindPlayerByTeam(bool exactMatch, string& target) const
	{
		vector<Player> result;

		for (int i = 0; i < mPlayers.size(); i++)
		{
			bool found = false;

			if (exactMatch)
			{
				if (mPlayers[i].getTeam() == target)
				{
					found = true;
				}
			}
			else
			{
				if (mPlayers[i].getTeam().find(target) != std::string::npos)
				{
					found = true;
				}
			}

			if (found)
			{
				result.push_back(mPlayers[i]);
			}
		}

		return result;
	}

	// function for searching by most played agent
	vector<Player> doFindPlayerByAgent(bool exactMatch, string& target) const
	{
		vector<Player> result;

		for (int i = 0; i < mPlayers.size(); i++)
		{
			bool found = false;

			if (exactMatch)
			{
				if (mPlayers[i].getMPA() == target)
				{
					found = true;
				}
			}
			else
			{
				if (mPlayers[i].getMPA().find(target) != std::string::npos)
				{
					found = true;
				}
			}

			if (found)
			{
				result.push_back(mPlayers[i]);
			}
		}

		return result;
	}

	// function for searching by acs
	vector<Player> doFindPlayerByAcs(bool exactMatch, int low, int high) const
	{
		vector<Player> result;

		for (int i = 0; i < mPlayers.size(); i++)
		{
			bool found = false;

			if (exactMatch)
			{
				if (mPlayers[i].getACS() == low)
				{
					found = true;
				}
			}
			else
			{
				if (mPlayers[i].getACS() >= low && mPlayers[i].getACS() <= high)
				{
					found = true;
				}
			}

			if (found)
			{
				result.push_back(mPlayers[i]);
			}
		}

		return result;
	}

	// DELETE FUNCTIONS

	// function for deleting by name
	void doDeletePlayerByName(bool exactMatch, string& target)
	{
		for (int i = mPlayers.size(); i >= 0; i--)
		{
			bool found = false;

			if (exactMatch)
			{
				if (mPlayers[i].getName() == target)
				{
					found = true;
				}
			}
			else
			{
				if (mPlayers[i].getName().find(target) != std::string::npos)
				{
					found = true;
				}
			}

			if (found)
			{
				mPlayers.erase(mPlayers.begin() + i);
			}
		}
	}

	// function for deleting by team
	void doDeletePlayerByTeam(bool exactMatch, string& target)
	{
		for (int i = mPlayers.size(); i >= 0; i--)
		{
			bool found = false;

			if (exactMatch)
			{
				if (mPlayers[i].getTeam() == target)
				{
					found = true;
				}
			}
			else
			{
				if (mPlayers[i].getTeam().find(target) != std::string::npos)
				{
					found = true;
				}
			}

			if (found)
			{
				mPlayers.erase(mPlayers.begin() + i);
			}
		}
	}

	// function for deleting by most played agent
	void doDeletePlayerByAgent(bool exactMatch, string& target)
	{
		for (int i = mPlayers.size(); i >= 0; i--)
		{
			bool found = false;

			if (exactMatch)
			{
				if (mPlayers[i].getMPA() == target)
				{
					found = true;
				}
			}
			else
			{
				if (mPlayers[i].getMPA().find(target) != std::string::npos)
				{
					found = true;
				}
			}

			if (found)
			{
				mPlayers.erase(mPlayers.begin() + i);
			}
		}
	}

	// function for deleting by acs
	void doDeletePlayerByAcs(bool exactMatch, int low, int high)
	{
		for (int i = mPlayers.size(); i >= 0; i--)
		{
			bool found = false;

			if (exactMatch)
			{
				if (mPlayers[i].getACS() == low)
				{
					found = true;
				}
			}
			else
			{
				if (mPlayers[i].getACS() >= low && mPlayers[i].getACS() <= high)
				{
					found = true;
				}
			}

			if (found)
			{
				mPlayers.erase(mPlayers.begin() + i);
			}
		}
	}

	// function for returning a data value
	string getStringField(const Player& player, const FIELD field) const
	{
		string result;

		switch (field)
		{
		case FIELD_NAME:
			result = player.getName();
			break;

		case FIELD_TEAM:
			result = player.getTeam();
			break;

		case FIELD_AGENT:
		default:
			result = player.getMPA();
			break;
		}

		return result;
	}

	// helper functions for listing
	struct number_ascend_asc
	{
		inline bool operator() (const Player& player1, const Player& player2)
		{
			return (player1.getACS() < player2.getACS());
		}
	};

	struct number_descend_asc
	{
		inline bool operator() (const Player& player1, const Player& player2)
		{
			return (player1.getACS() > player2.getACS());
		}
	};

	struct string_ascend_name
	{
		inline bool operator() (const Player& player1, const Player& player2)
		{
			return (player1.getName() < player2.getName());
		}
	};

	struct string_descend_name
	{
		inline bool operator() (const Player& player1, const Player& player2)
		{
			return (player1.getName() > player2.getName());
		}
	};

	struct string_ascend_team
	{
		inline bool operator() (const Player& player1, const Player& player2)
		{
			return (player1.getTeam() < player2.getTeam());
		}
	};

	struct string_descend_team
	{
		inline bool operator() (const Player& player1, const Player& player2)
		{
			return (player1.getTeam() > player2.getTeam());
		}
	};

	struct string_ascend_agent
	{
		inline bool operator() (const Player& player1, const Player& player2)
		{
			return (player1.getMPA() < player2.getMPA());
		}
	};

	struct string_descend_agent
	{
		inline bool operator() (const Player& player1, const Player& player2)
		{
			return (player1.getMPA() > player2.getMPA());
		}
	};
};