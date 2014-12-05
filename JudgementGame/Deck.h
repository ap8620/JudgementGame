#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Card.h"

using namespace std;

class Deck
{
private:
	vector<Card*> m_pDeck;

public:
	//constructors
	Deck();

	//other functions
	void shuffle();
	void printDeck();
	Card* dealCard();

	//get functions
	
};