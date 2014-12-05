#pragma once

#include <SFML/Graphics.hpp>
#include "GlobalConstants.h"
#include <string>

class Card
{
private:
	Suit m_eSuit;
	int m_nRank;
	string m_sCardImageFile;
	sf::Sprite* m_spSprite;

public:
	//constructors
	Card();
	Card(Suit suit, int nRank);
	Card(const Card& card);

	//other functions
	string determineCardImageFile(Suit suit, int nRank);
	void createSprite(string sCardImageFile);
	bool operator < (const Card& rhs);
	bool operator > (const Card& rhs);
	bool operator = (const Card& rhs);
	void printCard();

	//get functions
	Suit getSuit() { return m_eSuit; }
	int getRank() { return m_nRank; }
	string getCardImageFile() { return m_sCardImageFile; }
	sf::Sprite* getSprite() { return m_spSprite; }
};