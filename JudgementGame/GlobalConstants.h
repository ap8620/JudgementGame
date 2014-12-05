#pragma once

#include <string>

using namespace std;

static const string LOGFILE = "log.txt";

enum Suit {SPADES, CLUBS, DIAMONDS, HEARTS, ROOK};

//strings for suits
//static const string STRING_SUIT_SPADES = "\x06"; 
//static const string STRING_SUIT_CLUBS = "\x05";
//static const string STRING_SUIT_DIAMONDS = "\x04";
//static const string STRING_SUIT_HEARTS = "\x03";
static const string STRING_SUIT_SPADES = "SPADES"; 
static const string STRING_SUIT_CLUBS = "CLUBS";
static const string STRING_SUIT_DIAMONDS = "DIAMONDS";
static const string STRING_SUIT_HEARTS = "HEARTS";

//strings for ranks
static const string STRING_RANK_JACK = "J";
static const string STRING_RANK_QUEEN = "Q";
static const string STRING_RANK_KING = "K";
static const string STRING_RANK_ACE = "A";
