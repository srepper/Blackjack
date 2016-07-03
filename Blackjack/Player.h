#pragma once
#include "blackjack.h"
#include "Card.h"
#include "MyLabel.h"
#include "DoubleDeck.h"
#include <sstream>

class Player
{
	int cash;
	int handScore;
	int splitScore;
	int handPos;
	int splitPos;
	bool handBusted;
	bool splitBusted;
	bool split;
	Card *hand[11];
	Card *splitHand[11];
	MyLabel *playerLabel;
	MyLabel *splitLabel;
	MyLabel *lblHandScore;
	MyLabel *lblSplitScore;
	MyLabel *lblCash;
	MyLabel *lblHandBust;
	MyLabel *lblSplitBust;

public:
	Player(SDL_Surface *surface);
	~Player();
	int bet(int amount);
	void win(int amount);
	int getCash();
	int getHandScore();
	int getSplitScore();
	std::string getCashString();
	std::string getHandScoreString();
	std::string getSplitScoreString();
	void dealCard(Card *newCard);
	void splitCurrentHand();
	void dealSplit(Card *newCard);
	void clearHands();
	void Player::handReduceAce();
	void Player::splitReduceAce();
	void handBust();
	void splitBust();
	void clearBust();
	bool hasPair();
	bool isSplit();
	void stopSplit();
	void update(SDL_Surface *screen);
};