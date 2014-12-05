#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "Card.h"
#include "Deck.h"
#include "Player.h"

namespace Util
{
	int getSuitCompareValue(Suit eSuit);
	void printCard(Card* pCard);
	void printCards(vector<Card*> vCards);
	bool sortCards(Card* lhs, Card* rhs);
}