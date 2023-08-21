#include <algorithm>
#include <fstream>
#include <ostream>
#include <sstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <iomanip>

#include "Player.h"

using namespace std;

class Database
{
public:

	enum FIELD {
		FIELD_NAME,
		FIELD_TEAM,
		FIELD_AGENT,
		FIELD_ACS
	};

private:

	// separates fields
	const char DELIMITER = ',';

	// marks out ,'s inside a string
	const string ESCAPED_DELIMITER = "\\,\\";

	vector<Player> mPlayers;
	string mFilePath;

public:

	// default constructor
	Database()
	{
	}

	void addPlayer(Player& player)
	{
		mPlayers.push_back(player);
	}

	vector<Player> getPlayers() {
		return mPlayers;
	}

	vector<Player> findPlayer(const FIELD field, bool exactMatch, string& target, int lowBoundary = 0, int highBoundary = 0) const;

	const vector<Player> listPlayer(const FIELD field, bool ascend) const;


	// function for reading files
	bool init(const string& filename)
	{
		bool success = false;

		// make sure there is a file to be read
		if (filename.length() > 0)
		{
			fstream infile;

			infile.open(filename, ios::in);

			if (infile.is_open() == true)
			{
				mFilePath = filename;

				string strLine;

				while (getline(infile, strLine))
				{
					vector<string> terms;

					size_t pos = 0;
					string field;

					// find entry separator to find an individual db entry
					if (strLine.find(DELIMITER) != std::string::npos)
					{
						pos = strLine.find(DELIMITER);

						while (pos != string::npos && pos >= 1 && pos < strLine.size() - 1 &&
							strLine.at(pos - 1) == '\\' &&
							strLine.at(pos + 1) == '\\')
						{
							// if there's a comma in the middle of the string
							// (marked by \\\\), skip to next comma
							pos = strLine.find(DELIMITER, pos + 1);
						}

						while (pos != string::npos)
						{
							// make the field into a substring, add to 
							field = strLine.substr(0, pos);
							terms.push_back(field);
							strLine.erase(0, pos + 1);

							if (strLine.find(DELIMITER) == string::npos)
							{
								// store the final field
								terms.push_back(strLine);
								break;
							}

							pos = strLine.find(DELIMITER);

							while (pos != string::npos && pos >= 1 && pos < strLine.size() - 1 &&
								strLine.at(pos - 1) == '\\' &&
								strLine.at(pos + 1) == '\\')
							{
								// if there's a comma in the middle of the string
								// (marked by \\\\), skip to next comma
								pos = strLine.find(DELIMITER, pos + 1);
							}
						}

						// gathere very 4 terms together and use them as the player info
						if (terms.size() == 4)
						{
							// create a player with the data, push back into player database
							Player player(unescapeDelimiter(terms[0]), unescapeDelimiter(terms[1]), unescapeDelimiter(terms[2]), stoi(terms[3]));
							mPlayers.push_back(player);
						}
					}
				}

				infile.close();

				success = true;
			}
		}

		return success;
	}

	// function for saving database
	bool save()
	{
		bool success = false;

		if (mFilePath.length() > 0)
		{
			ofstream  outFile;

			outFile.open(mFilePath, ios::out);

			if (outFile.is_open() == true)
			{
				string record;

				// convert the database info into string
				for (size_t i = 0; i < mPlayers.size(); i++)
				{
					record = escapeDelimiter(mPlayers[i].getName()) + DELIMITER +
						escapeDelimiter(mPlayers[i].getTeam()) + DELIMITER +
						escapeDelimiter(mPlayers[i].getMPA()) + DELIMITER +
						to_string(mPlayers[i].getACS()) + "\n";

					outFile << record;
				}

				outFile.close();

				success = true;
			}
		}

		return success;
	}

	// getter for size of vector
	unsigned int getPlayerCount() const { return mPlayers.size(); }

	// searches for a player given a string and type of field to search for
	vector<Player> doFindPlayerByStringField(const FIELD field, bool exactMatch, string& target) const
	{
		vector<Player> result;
		string curField;

		// run through array and find matches
		for (int i = 0; i < mPlayers.size(); i++)
		{
			curField = getStringField(mPlayers[i], field);

			if ((exactMatch && curField == target) ||
				(!exactMatch && curField.find(target) != std::string::npos))
			{
				result.push_back(mPlayers[i]);
			}
		}

		return result;
	}

	// searches for a player given an int and the type of field to search for
	vector<Player> doFindPlayerByNumberField(const FIELD field, bool exactMatch, int low, int high) const
	{
		vector<Player> result;
		int data = 0;

		for (int i = 0; i < mPlayers.size(); i++)
		{
			bool found = getNumberField(mPlayers[i], field, data);

			if (found == true)
			{
				if ((exactMatch && data == low) ||
					(!exactMatch && data >= low && data <= high))
				{
					result.push_back(mPlayers[i]);
				}
			}
		}

		return result;
	}

	// gets a field from a player depending on the input field
	string getStringField(const Player& player, const FIELD field) const
	{
		string data;

		switch (field)
		{
		case FIELD_NAME:
			data = player.getName();
			break;

		case FIELD_TEAM:
			data = player.getTeam();
			break;

		case FIELD_AGENT:
			data = player.getMPA();
			break;

		default:
			break;
		}

		return data;
	}

	// gets an int field from a player
	bool getNumberField(const Player& player, const FIELD field, int& data) const
	{
		bool found = false;

		switch (field)
		{
		case FIELD_ACS:
			data = player.getACS();
			found = true;
			break;

		default:
			break;
		}

		return found;
	}

	/////////////////////
	// DELETE FUNCTIONS:
	////////////////////

	// search for and delete a string field, depending on field input
	void doDeletePlayerByStringField(FIELD field, bool exactMatch, string& target)
	{
		for (int i = mPlayers.size() - 1; i >= 0; i--)
		{

			string fieldData = getStringField(mPlayers[i], field);

			if ((exactMatch && fieldData == target) ||
				(!exactMatch && fieldData.find(target) != std::string::npos))
			{
				mPlayers.erase(mPlayers.begin() + i);
			}
		}
	}

	// search for and delete an int field
	void doDeletePlayerByNumberField(FIELD field, bool exactMatch, int low, int high)
	{
		for (int i = mPlayers.size() - 1; i >= 0; i--)
		{
			int data;
			bool found = false;

			switch (field)
			{
			case FIELD_ACS:
				found = getNumberField(mPlayers[i], FIELD_ACS, data);
				break;

			default:
				break;
			}

			if (found == true)
			{
				if ((exactMatch && data == low) ||
					(!exactMatch && data >= low && data <= high))
				{
					mPlayers.erase(mPlayers.begin() + i);
				}
			}
		}
	}

	//////////////////////
	//DELIMITER FUNCTIONS:
	//////////////////////

	// if there's a ',' in the middle of a string, replace with "//,//"
	string escapeDelimiter(const string& source) const
	{
		string result;

		if (source.length() > 0)
		{
			result = source;

			for (int i = source.length(); i >= 0; i--)
			{
				if (result[i] == DELIMITER)
				{
					result.replace(i, 1, ESCAPED_DELIMITER);
				}
			}
		}

		return result;
	}

	// remove "////" when reading out
	string unescapeDelimiter(const string& source) const
	{
		string result;

		if (source.length() > 0)
		{
			result = source;

			string delimiterString;
			delimiterString.push_back(DELIMITER);

			while (result.find(ESCAPED_DELIMITER) != string::npos)
			{
				result.replace(result.find(ESCAPED_DELIMITER), ESCAPED_DELIMITER.length(), delimiterString);
			}
		}

		return result;
	}

	// helper functions for sorting

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

	// Helper function for printing out players

	
};