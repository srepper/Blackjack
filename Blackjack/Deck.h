#pragma once
#include "Card.h"
#include <vector>

class Deck
{
	Deck *next;
	Card cards[52];
	int cardNum;

public:
	Deck(SDL_Surface *cardsImage);
	~Deck();
	int getCardNum();
	Card *getFirstCard();
	Card *getNextCard();
	Card *getPrevCard();
	Deck *getNextDeck();
	void setNextDeck(Deck *nextDeck);
	void shuffleDeck();
	void splitDeck(bool cut);
	void Deck::riffleShuffle(std::vector<Card> upperHalf,
		std::vector<Card> lowerHalf, int midCard);
};