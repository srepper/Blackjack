#pragma once
#include "Deck.h"

class DoubleDeck
{
	Deck *deck;
	int cardNum;
	
public:
	DoubleDeck(SDL_Surface *cardsImage);
	~DoubleDeck();
	Card *getNextCard();
	void swap();
};

