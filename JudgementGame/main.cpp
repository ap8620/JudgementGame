#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "GlobalConstants.h"

using namespace std;

void playCard(Player* pPlayer, Card* pCard, vector<Card*>* vecTablePile, sf::RenderWindow &window);
void displayPlayerHand(Player* pPlayer, sf::RenderWindow &window);
fstream logFile;

int main()
{
	logFile = fstream(LOGFILE, fstream::in | fstream::out | fstream::trunc);
	logFile.close();
	logFile = fstream(LOGFILE, fstream::in | fstream::out | fstream::app);
	logFile << "test writing to this log 4564\n";

	// create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	sf::Font font;
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		// error...
		bool fail = true;
		cout << "cant load font" << endl;
	}

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
			{
				window.close();
			}
        }

		//////////game logic
		srand(unsigned(time(0)));

		//create new deck of 52 cards and shuffle
		Deck* pDeck = new Deck();
		pDeck->printDeck();
		pDeck->shuffle();
		cout << endl << endl << "shuffled: " << endl;
		logFile << endl << endl << "shuffled: " << endl;
		pDeck->printDeck();
	
		//create 5 players and deal cards to all players
		vector<Player*> vecPlayers;
		vecPlayers.reserve(5);

		for (int i = 0; i < 5; i++)
		{
			Player* pPlayer = new Player(i);
	
			for(int k = 0; k < 10; k++)
			{
				Card* pCard = pDeck->dealCard();
				pPlayer->addToHand(pCard);
			}

			vecPlayers.push_back(pPlayer);

			cout << endl << endl << "player hand: " << endl;
			logFile << endl << endl << "player hand: " << endl;
			pPlayer->printHand();

			pPlayer->sortHand();
			cout << endl << endl << "player hand sorted: " << endl;
			logFile << endl << endl << "player hand sorted: " << endl;
			pPlayer->printHand();

			/*cout << endl << endl << "remaining deck: " << endl;
			logFile << endl << endl << "remaining deck: " << endl;
			pDeck->printDeck();*/
		}
		
		

		//system("PAUSE");
		//////////end game logic


        

        // draw everything here...
        // window.draw(...);

		/*
		sf::Text text;
		text.setFont(font);
		text.setString("click to continue");
		text.setCharacterSize(50);
		text.setColor(sf::Color::Red);
		window.draw(text);
		window.display();
		*/

		//player 0 is the player, rest are cpu
		Player* pPlayer0 = vecPlayers.at(0);
		
		// clear the window with black color
		window.clear(sf::Color::Black);
		
		for (int i = 0; i < 5; i++)
		{
			Player* pPlayerDisplay = vecPlayers.at(i);
			displayPlayerHand(pPlayerDisplay, window);
		}		
		
		window.display();		

		while (pPlayer0->getHand().size() != 0)
		{
			vector<Card*> vecTablePile;
			vecTablePile.reserve(5);
			for (int i = 0; i < 5; i++)
			{
				Player* pPlayer = vecPlayers.at(i);
				bool bCardClicked = false;
				while (!bCardClicked)
				{
					while(window.pollEvent(event))
					{
						// "close requested" event: we close the window
						if (event.type == sf::Event::Closed)
						{
							window.close();
						}
						if (event.type == sf::Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == sf::Mouse::Left)
							{
								//determine which card was clicked
								cout << "clicked at x: " << sf::Mouse::getPosition(window).x << " y: " << sf::Mouse::getPosition(window).y;
								logFile << "clicked at x: " << sf::Mouse::getPosition(window).x << " y: " << sf::Mouse::getPosition(window).y;
								Card* pCardClicked = NULL;
								for(vector<Card*>::iterator it = pPlayer->getHand().begin(); it != pPlayer->getHand().end(); ++it)
								{
									Card* pCard = *it;
									sf::Sprite* sprite = pCard->getSprite();
									float xpos = sprite->getPosition().x;
									float ypos = sprite->getPosition().y;
			
									if((it - pPlayer->getHand().begin()) == (pPlayer->getHand().size() - 1))
									{
										//this is last card
										if ((sf::Mouse::getPosition(window).x >= sprite->getGlobalBounds().left) && (sf::Mouse::getPosition(window).x <= (sprite->getGlobalBounds().left + sprite->getGlobalBounds().width)) && 
											(sf::Mouse::getPosition(window).y >= sprite->getGlobalBounds().top) && (sf::Mouse::getPosition(window).y <= (sprite->getGlobalBounds().top + sprite->getGlobalBounds().height)))
										{
											bCardClicked = true;
											pCardClicked = pCard;
										}
									}
									else
									{
										if ((sf::Mouse::getPosition(window).x >= sprite->getGlobalBounds().left) && (sf::Mouse::getPosition(window).x < (sprite->getGlobalBounds().left + 20)) && 
											(sf::Mouse::getPosition(window).y >= sprite->getGlobalBounds().top) && (sf::Mouse::getPosition(window).y <= (sprite->getGlobalBounds().top + sprite->getGlobalBounds().height)))
										{
											bCardClicked = true;
											pCardClicked = pCard;
										}
									}
						
									cout << "vector card " << " x pos: " << xpos << " y pos: " << ypos << " top: " << sprite->getGlobalBounds().top << " left: " << sprite->getGlobalBounds().left << endl;
									logFile << "vector card " << " x pos: " << xpos << " y pos: " << ypos << " top: " << sprite->getGlobalBounds().top << " left: " << sprite->getGlobalBounds().left << endl;
								}
		
								//if card was clicked, then move to table
								cout << " cardClicked: " << bCardClicked << endl;
								logFile << " cardClicked: " << bCardClicked << endl;
								if (bCardClicked)
								{
									window.clear();
									playCard(pPlayer, pCardClicked, &vecTablePile, window);

									//display everyone's hand
									for (int j = 0; j < 5; j++)
									{
										displayPlayerHand(vecPlayers.at(j), window);
									}
									
									//now cpus play cards
									/*for (int i = 1; i < 5; i++)
									{
										Player* pPlayerCPU = vecPlayers.at(i);
										Card* pCardCPU = pPlayerCPU->getHand().at(0);
										playCard(pPlayerCPU, pCardCPU, window);
									}*/
									window.display();

									//while(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
									//{
									//cout << "mouse button not pressed" << endl;
									//}
								}
								else
								{
									cout << " no card was clicked " << endl;
									logFile << " no card was clicked " << endl;
								}
							}

							for(vector<Card*>::iterator it = pPlayer->getHand().begin(); it != pPlayer->getHand().end(); ++it)
							{
								Card* pCard = *it;
								sf::Sprite* sprite = pCard->getSprite();
								float xpos = sprite->getPosition().x;
								float ypos = sprite->getPosition().y;
								cout << "card " << pCard->getCardImageFile() << " x pos: " << xpos << " y pos: " << ypos << endl;
								logFile << "card " << pCard->getCardImageFile() << " x pos: " << xpos << " y pos: " << ypos << endl;
							}
						}
					}
				}
			}
		}
		while(!sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			//cout << "mouse button not pressed" << endl;
		}
		logFile.close();
		
    } //window open
	
    return 0;
}

void playCard(Player* pPlayer, Card* pCard, vector<Card*>* vecTablePile, sf::RenderWindow &window)
{
	Card* pCardPlayed =  new Card(*pCard);
	//*pCardPlayed = *pCard;
	vecTablePile->push_back(pCardPlayed);

	pCardPlayed->printCard();

	////move position of played card depending on player num
	//sf::Sprite* pSprite = pCardPlayed->getSprite();
	//int nPlayerNo = pPlayer->getPlayerNo();

	//switch (nPlayerNo)
	//{
	//	case 0:
	//		pSprite->setPosition(550,500);
	//		break;
	//	case 1:
	//		pSprite->setPosition(550,400);
	//		break;
	//	case 2:
	//		pSprite->setPosition(550,300);
	//		break;
	//	case 3:
	//		pSprite->setPosition(550,200);
	//		break;
	//	case 4:
	//		pSprite->setPosition(550,100);
	//		break;
	//	default:
	//		break;
	//}

	float xpos = 550;
	float ypos = 600;
	
	for(vector<Card*>::iterator it = vecTablePile->begin(); it != vecTablePile->end(); ++it)
	{
		Card* pCard = *it;
		sf::Sprite* sprite = pCard->getSprite();
		ypos -= 100;
		sprite->setPosition(xpos,ypos);
		float xpos = sprite->getPosition().x;
		float ypos = sprite->getPosition().y;
		cout << "card " << pCard->getCardImageFile() << " x pos: " << xpos << " y pos: " << ypos << endl;
		logFile << "card " << pCard->getCardImageFile() << " x pos: " << xpos << " y pos: " << ypos << endl;
		window.draw(*sprite);
	}
	
	//window.draw(*pSprite);

	//remove card from player's hand and display remaining hand
	pPlayer->removeFromHand(pCard);

	//displayPlayerHand(pPlayer, window);	
}

void displayPlayerHand(Player* pPlayer, sf::RenderWindow &window)
{
	int playerNo = pPlayer->getPlayerNo();
	float xpos = 0;
	float ypos = 0;

	switch (playerNo)
	{
		case 0:
			xpos = 200;
			ypos = 500;
			break;
		case 1:
			xpos = 10;
			ypos = 400;
			break;
		case 2:
			xpos = 10;
			ypos = 300;
			break;
		case 3:
			xpos = 10;
			ypos = 200;
			break;
		case 4:
			xpos = 10;
			ypos = 100;
			break;
		default:
			break;
	}
				
	for(vector<Card*>::iterator it = pPlayer->getHand().begin(); it != pPlayer->getHand().end(); ++it)
	{
		Card* pCard = *it;
		sf::Sprite* sprite = pCard->getSprite();
		xpos += 20;
		sprite->setPosition(xpos,ypos);
		float xpos = sprite->getPosition().x;
		float ypos = sprite->getPosition().y;
		cout << "card " << pCard->getCardImageFile() << " x pos: " << xpos << " y pos: " << ypos << endl;
		logFile << "card " << pCard->getCardImageFile() << " x pos: " << xpos << " y pos: " << ypos << endl;
		window.draw(*sprite);
	}
}