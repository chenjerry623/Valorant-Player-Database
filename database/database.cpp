#include "database.h"

vector<Player> Database::findPlayer(const FIELD field, bool exactMatch, string& target, int lowBoundary, int highBoundary) const
{
	vector<Player> result;

	switch (field)
	{
	case FIELD_NAME:
		result = doFindPlayerByStringField(FIELD_NAME, exactMatch, target);
		break;

	case FIELD_TEAM:
		result = doFindPlayerByStringField(FIELD_TEAM, exactMatch, target);
		break;

	case FIELD_AGENT:
		result = doFindPlayerByStringField(FIELD_AGENT, exactMatch, target);
		break;

	case FIELD_ACS:
		result = doFindPlayerByNumberField(FIELD_ACS, exactMatch, lowBoundary, highBoundary);
		break;

	default:
		break;
	}

	return result;
}

const vector<Player> Database::listPlayer(const FIELD field, bool ascend) const
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