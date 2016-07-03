#include "DoubleDeck.h"

DoubleDeck::DoubleDeck(SDL_Surface *cardsImage)
{
	deck = new Deck(cardsImage);
	deck->setNextDeck(new Deck(cardsImage));
	deck->getNextDeck()->setNextDeck(deck);

	//Thoroughly shuffle decks, since they begin ordered
	for(int i = 0; i < 20; i++)
	{
		deck->shuffleDeck();
		deck->getNextDeck()->shuffleDeck();
	}
	
	cardNum = 0;
}

DoubleDeck::~DoubleDeck()
{
	delete deck;
}

void DoubleDeck::swap()
{
	deck->shuffleDeck();
	deck = deck->getNextDeck();
}

Card *DoubleDeck::getNextCard()
{
	if(cardNum == 52)
	{
		swap();
		cardNum = 0;
	}

	cardNum++;
	
	return deck->getNextCard();
}
