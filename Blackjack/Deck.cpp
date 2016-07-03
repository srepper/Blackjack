#include <time.h>
#include "Deck.h"

//constructor puts together the deck; cards start in order
Deck::Deck(SDL_Surface *cardsImage)
{
	cardNum = 0;
	int i = 0;
	
	//outer loop for suit
	for(int s = 0; s < 4; s++)
	{
		//inner loop for rank
		for(int r = 0; r < 13; r++)
		{
			cards[i].setSurface(cardsImage);
			cards[i].setSuit(s);
			cards[i].setRank(r + 1);
			cards[i].setValue();
			cards[i].setClip(72 * r, 96 * s, 72, 96);
			i++;
		}
	}
}

//Get position in deck
int Deck::getCardNum()
{
	return cardNum;
}

//return the first card in the deck
Card *Deck::getFirstCard()
{
	return &cards[0];
}

//return the next card in the deck
Card *Deck::getNextCard()
{
	if(cardNum == 51)
	{
		cardNum = 0;
		return &cards[51];
	}
	
	return &cards[cardNum++];
}
	
//return the previous card in the deck
Card *Deck::getPrevCard()
{
	if(cardNum == 0)
	{
		cardNum = 51;
		return &cards[cardNum];
	}

	return &cards[--cardNum];
}

//return pointer to next deck
Deck *Deck::getNextDeck()
{
	return next;
}

//set pointer to next deck
void Deck::setNextDeck(Deck *nextDeck)
{
	next = nextDeck;
}

//shell function for shuffling - calls to further shuffle functions
void Deck::shuffleDeck()
{
	//randomize number of shuffles to take place (10-20)
	srand(time(NULL));
	int numShuffle = rand() % 11 + 10;

	//call next shuffle function numShuffle times
	for(int i = 0; i < numShuffle; i++)
	{
		splitDeck(false);
	}

	//final cut
	splitDeck(true);
}

//split the deck into two parts to prepare for realistic riffle shuffle or cut
void Deck::splitDeck(bool cut)
{
	//randomize where to split the deck; separate top & bottom halves
	int midCard = rand() % 16 + 18;
	
	std::vector<Card> upperHalf (midCard+1);
	std::vector<Card> lowerHalf (51 - midCard);
	for(int i = 0; i <= midCard; i++)
	{
		upperHalf[i] = cards[i];
	}

	midCard += 1;
	for(int i = midCard; i < 52; i++)
	{
		lowerHalf[i - midCard] = cards[i];
	}
	
	//check to see whether deck was sent for cut or shuffle
	if(!cut)
		riffleShuffle(upperHalf, lowerHalf, midCard);
	else
	{
		for(int i = 0; i < lowerHalf.size(); i++)
			cards[i] = lowerHalf[i];
		
		for(int i = 0; i < upperHalf.size(); i++)
			cards[lowerHalf.size() + i] = upperHalf[i];
	}
}

//perform "realistic" riffle shuffle to recombine deck halves
void Deck::riffleShuffle(std::vector<Card> upperHalf,
	std::vector<Card> lowerHalf, int midCard)
{
	int lowerLastCard;
	int numCardsFromBottom;
	int deckIterator = 0;

	lowerLastCard = (51 - midCard);
	midCard -= 1;					//marks the end of upperHalf

	while(deckIterator < 52)
	{
		//number of cards (1-3) from bottom of upper half
		numCardsFromBottom = rand() % 3 + 1;

		//while bottom cards exist & midCard isn't past 0 index
		while(numCardsFromBottom > 0 && midCard >= 0)
		{
			//put midCard in first available place in deck
			cards[51 - deckIterator] = upperHalf[midCard];
			numCardsFromBottom -= 1;
			midCard -= 1;
			deckIterator += 1;
		}

		//number of cards (1-3) from bottom of lower half
		numCardsFromBottom = rand() % 3 + 1;

		//while bottom cards exist & midCard isn't past 0 index
		while(numCardsFromBottom > 0 && lowerLastCard >= 0)
		{
			//put lowerLastCard in first available place in deck
			cards[51 - deckIterator] = lowerHalf[lowerLastCard];
			numCardsFromBottom -= 1;
			lowerLastCard -= 1;
			deckIterator += 1;
		}
	}
}

Deck::~Deck()
{
}