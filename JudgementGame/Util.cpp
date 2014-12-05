#include "Util.h"
#include "GlobalConstants.h"
#include <string>
#include <fstream>

namespace Util
{
	int getSuitCompareValue(Suit eSuit)
	{
		int iSuitValue = 0;
		switch (eSuit)
		{
			case SPADES:
				iSuitValue = 1;
				break;
			case DIAMONDS:
				iSuitValue = 2;
				break;
			case CLUBS:
				iSuitValue = 3;
				break;
			case HEARTS:
				iSuitValue = 4;
				break;
			default:
				break;
		}
		
		return iSuitValue;
	}
	
	void printCard(Card* pCard)
	{
		int nRank = pCard->getRank();
		string sRank;
		Suit eSuit = pCard->getSuit();
		string sSuit;

		switch (eSuit)
		{
			case SPADES:
				sSuit = STRING_SUIT_SPADES;
				break;
			case CLUBS:
				sSuit = STRING_SUIT_CLUBS;
				break;
			case DIAMONDS:
				sSuit = STRING_SUIT_DIAMONDS;
				break;
			case HEARTS:
				sSuit = STRING_SUIT_HEARTS;
				break;
			default:
				break;
		}

		switch (nRank)
		{
			case 11:
				sRank = STRING_RANK_JACK;
				break;
			case 12:
				sRank = STRING_RANK_QUEEN;
				break;
			case 13:
				sRank = STRING_RANK_KING;
				break;
			case 14:
				sRank = STRING_RANK_ACE;
				break;
			default:
				sRank = to_string(nRank);
				break;
		}
	
		cout << sRank << sSuit << endl;
		fstream logFile = fstream(LOGFILE, fstream::in | fstream::out | fstream::app);
		logFile << sRank << " " << sSuit << endl;
	}

	void printCards(vector<Card*> vCards)
	{
		for(vector<Card*>::iterator it = vCards.begin(); it != vCards.end(); ++it)
		{
			Card* pCard = *it;
			printCard(pCard);
		}
	}

	bool sortCards(Card* lhs, Card* rhs)
	{
		return *lhs < *rhs;	
	}
}