#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Card.h"

using namespace std;

class Player
{
private:
	vector<Card*> m_pHand;
	vector<Card*> m_pWinPile;
	int m_nPlayerNo;

public:
	//constructors
	Player(int nPlayerNo);

	//other functions
	void addToHand(Card* pCard);
	void removeFromHand(Card* pCard);
	void playCard(Card* pCard);
	void printHand();
	void printWinPile();
	void sortHand();

	//get functions
	vector<Card*>& getHand() { return m_pHand; }
	int getPlayerNo() { return m_nPlayerNo; }
};