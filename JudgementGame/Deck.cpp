#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "Deck.h"
#include "Util.h"

using namespace std;

// constructor
Deck::Deck()
{
	m_pDeck.reserve(52);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 2; j < 15; j++)
		{
				Card *cCard = NULL;
				switch (i)
				{
					case SPADES:
						cCard = new Card(SPADES, j);
						break;
					case CLUBS:
						cCard = new Card(CLUBS, j);
						break;
					case DIAMONDS:
						cCard = new Card(DIAMONDS, j);
						break;
					case HEARTS:
						cCard = new Card(HEARTS, j);
						break;
					default:
						break;
				}
				m_pDeck.push_back(cCard);		
		}
	}
}

void Deck::shuffle()
{
	random_shuffle(m_pDeck.begin(), m_pDeck.end());
}

void Deck::printDeck()
{
	Util::printCards(m_pDeck);
}

Card* Deck::dealCard()
{
	Card* pCardToDeal = m_pDeck.back();
	m_pDeck.pop_back();
	return pCardToDeal;
}
