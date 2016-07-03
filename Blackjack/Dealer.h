#pragma once
#include "blackjack.h"
#include "Card.h"
#include "MyLabel.h"
#include <sstream>

#include "DoubleDeck.h"


class Dealer
{
	int pot;
	int score;
	int handPos;
	bool busted;
	Card *hand[11];
	MyLabel *dealerLabel;
	MyLabel *lblScore;
	MyLabel *lblPot;
	MyLabel *lblBust;
	SDL_Surface *cardBack;
	SDL_Rect *tempClip;

public:
	Dealer(SDL_Surface *surface);
	~Dealer();
	void clearPot();
	void updatePot(int bet);
	int getPot();
	int getScore();
	int checkBlackjack();
	std::string getPotString();
	std::string getScoreString();
	void setCardBack(SDL_Surface *blueCard);
	void dealCard(Card *newCard);
	void clearHand();
	void reduceAce();
	void bust();
	void clearBust();
	void showHidden(SDL_Surface *screen);
	void update(SDL_Surface *screen);
};