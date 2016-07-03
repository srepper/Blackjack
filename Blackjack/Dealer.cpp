#include "Dealer.h"

Dealer::Dealer(SDL_Surface *surface)
{
	pot = 0;
	score = 0;
	handPos = 0;
	busted = false;

	dealerLabel = new MyLabel("Dealer:", 20, 130);
	lblScore = new MyLabel("", 105, 130);
	lblPot = new MyLabel("", SCREEN_WIDTH/2 - 50, 185);
	lblBust = new MyLabel("BUST", 25, 50);
	lblBust->setColorRed();

	hand[0] = new Card();
	hand[0]->setPos(20, 20);
	hand[0]->setSurface(surface);

	for(int i = 1; i < 11; i++)
	{
		SDL_Rect tempPos = hand[i-1]->getPos();
		hand[i] = new Card();
		hand[i]->setPos(tempPos.x + 15, tempPos.y + 4);
		hand[i]->setSurface(surface);
	}
}

Dealer::~Dealer()
{
	delete dealerLabel;
	delete lblScore;
	delete lblPot;
	delete lblBust;
	delete[] hand;
}

void Dealer::clearPot()
{
	pot = 0;
}

void Dealer::updatePot(int bet)
{
	pot += bet;
}

int Dealer::getPot()
{
	return pot;
}

int Dealer::checkBlackjack()
{
	return score + hand[0]->getValue();
}

int Dealer::getScore()
{
	return score;
}

std::string Dealer::getPotString()
{
	std::string retString;
	std::stringstream ss;
	ss << pot;
	retString = "$" + ss.str();

	return retString;
}

std::string Dealer::getScoreString()
{
	if(score == 0)
		return "-";

	std::string retString;
	std::stringstream ss;
	ss << score;
	retString = ss.str();

	return retString;
}

void Dealer::setCardBack(SDL_Surface *blueCard)
{
	cardBack = blueCard;
}

void Dealer::dealCard(Card *newCard)
{
	if(handPos != 0)
	{
		hand[handPos]->setClip(newCard->getClip()->x, newCard->getClip()->y);
		hand[handPos]->setRank(newCard->getRank());
		hand[handPos]->setValue(newCard->getValue());
		score += hand[handPos]->getValue();
	}
	else
	{
		tempClip = newCard->getClip();
		hand[handPos]->setSurface(cardBack);
		hand[handPos]->setClip(0, 0);
		hand[handPos]->setRank(newCard->getRank());
		hand[handPos]->setValue(newCard->getValue());
	}

	if(score > 21)
		reduceAce();

	handPos++;
}

void Dealer::clearHand()
{
	for(int i = 0; i < 11; i++)
	{
		hand[i]->setValue(0);
	}

	handPos = 0;
	score = 0;
}

/*  Checks for and reduces one Ace from 11 to 1 value within hand */
void Dealer::reduceAce()
{
	for(int i = 0; i < 11; i++)
	{
		if(hand[i]->getRank() == ACE && hand[i]->getValue() != 1)
		{
			hand[i]->setValue(1);
			score -= 10;
			break;
		}
		else if(hand[i]->getRank() == 0)
			break;
	}
}

void Dealer::bust()
{
	busted = true;
}

void Dealer::clearBust()
{
	busted = false;
}

/*  "Flip" the dealer's hidden card */
void Dealer::showHidden(SDL_Surface *cards)
{
	hand[0]->setSurface(cards);
	hand[0]->setClip(*tempClip);
	score += hand[0]->getValue();
}

/*  Updates all screen information for dealer */
void Dealer::update(SDL_Surface *screen)
{
	dealerLabel->applySurface(screen, NULL);
	lblScore->setMessage(getScoreString());
	lblScore->applySurface(screen, NULL);
	lblPot->setMessage("Pot: " + getPotString());
	lblPot->applySurface(screen, NULL);

	for(int i = 0; i < 11; i++)
	{
		if(hand[i]->getValue() != 0)
		{
			hand[i]->applySurface(screen);
		}
	}

	if(busted)
		lblBust->applySurface(screen, NULL);
}