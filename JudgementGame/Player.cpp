#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "Util.h"

using namespace std;
//using namespace util;

// constructor

Player::Player(int nPlayerNo)
{
	m_nPlayerNo = nPlayerNo;
}

void Player::addToHand(Card* pCard)
{
	m_pHand.push_back(pCard);
}

void Player::removeFromHand(Card* pCard)
{
	m_pHand.erase(std::remove(m_pHand.begin(), m_pHand.end(), pCard), m_pHand.end());
}

void Player::printHand()
{
	Util::printCards(m_pHand);
}



void Player::sortHand()
{
	sort(m_pHand.begin(), m_pHand.end(), Util::sortCards);
}




//return false;