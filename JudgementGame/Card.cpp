#include "Card.h"
#include "Util.h"
#include <iostream>
#include <string>

// constructors
Card::Card()
{
}

Card::Card(Suit suit, int nRank)
{
	m_eSuit = suit;
	m_nRank = nRank;
	m_sCardImageFile = determineCardImageFile(suit, nRank);
	m_spSprite = new sf::Sprite();
	createSprite(m_sCardImageFile);
}

Card::Card(const Card& card)
{
	m_eSuit = card.m_eSuit;
	m_nRank = card.m_nRank;
	m_sCardImageFile = card.m_sCardImageFile;
	m_spSprite = new sf::Sprite();
	createSprite(m_sCardImageFile);
}


bool Card::operator < (const Card& rhs)
{
	if (Util::getSuitCompareValue(m_eSuit) < Util::getSuitCompareValue(rhs.m_eSuit))
	{
		return true;
	}
	else if (Util::getSuitCompareValue(m_eSuit) == Util::getSuitCompareValue(rhs.m_eSuit))
	{
		if(m_nRank < rhs.m_nRank)
		{
			return true;
		}
	}
	
	return false;
}

bool Card::operator > (const Card& rhs)
{
	if (Util::getSuitCompareValue(m_eSuit) > Util::getSuitCompareValue(rhs.m_eSuit))
	{
		return true;
	}
	else if (Util::getSuitCompareValue(m_eSuit) == Util::getSuitCompareValue(rhs.m_eSuit))
	{
		if(m_nRank > rhs.m_nRank)
		{
			return true;
		}
	}

	return false;
}

bool Card::operator = (const Card& rhs)
{
	if (Util::getSuitCompareValue(m_eSuit) == Util::getSuitCompareValue(rhs.m_eSuit))
	{
		if(m_nRank == rhs.m_nRank)
		{
			return true;
		}
	}

	return false;
}

void Card::printCard()
{
	Util::printCard(this);
}

string Card::determineCardImageFile(Suit suit, int nRank)
{
	string sCardImageFile = "pics/cards/";

	switch (suit)
	{
		case SPADES:
			sCardImageFile += "spades/";
			break;
		case CLUBS:
			sCardImageFile += "clubs/";
			break;
		case DIAMONDS:
			sCardImageFile += "diamonds/";
			break;
		case HEARTS:
			sCardImageFile += "hearts/";
			break;
		case ROOK:
			sCardImageFile += "joker/";
		default:
			break;
	}

	switch (nRank)
	{
		case 11:
			sCardImageFile += "jack.png";
			break;
		case 12:
			sCardImageFile += "queen.png";
			break;
		case 13:
			sCardImageFile += "king.png";
			break;
		case 14:
			sCardImageFile += "ace.png";
			break;
		case 15:
			sCardImageFile += "joker_black.png";
			break;
		default:
			sCardImageFile += to_string(nRank) + ".png";
			break;
	}
	
	return sCardImageFile;
}

void Card::createSprite(string sCardImageFile)
{
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(sCardImageFile))
	{
		cout << "cant load image" << endl;
	}
	
	//sf::Sprite sprite;
	m_spSprite->setTexture(*texture);
	//xpos += 20;
	//sprite.setPosition(xpos,500);	
	//return sprite;
}