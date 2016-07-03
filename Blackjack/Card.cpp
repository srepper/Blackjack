#include "blackjack.h"
#include "Card.h"

Card::Card()
{
	suit = NULL;
	rank = NULL;
	value = 0;
	surface = NULL;

	thisClip.x = thisClip.y = 0;
	thisClip.w = 72;
	thisClip.h = 96;
}

Card::~Card()
{
	return;
}

void Card::setSuit(int s)
{
	suit = s;
}

void Card::setRank(int r)
{
	rank = r;
}

// Assign card value based on rank
void Card::setValue()
{
	if(rank == JACK || rank == QUEEN || rank == KING)
		value = 10;
	else if(rank == ACE)
		value = 11;
	else
		value = rank;
}

void Card::setValue(int val)
{
	value = val;
}

int Card::getValue()
{
	return value;
}

int Card::getRank()
{
	return rank;
}