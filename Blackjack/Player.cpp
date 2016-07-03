#include "Player.h"

Player::Player(SDL_Surface *surface)
{
	cash = 500;
	handScore = 0;
	splitScore = 0;
	handPos = 0;
	splitPos = 0;
	split = false;
	handBusted = false;
	splitBusted = false;
	
	lblCash = new MyLabel("", 20, SCREEN_HEIGHT - 90);
	playerLabel = new MyLabel("Player:", 20, 160);
	splitLabel = new MyLabel("Split:", 20, 190);
	lblHandScore = new MyLabel("", 105, 160);
	lblSplitScore = new MyLabel("", 105, 190);
	lblHandBust = new MyLabel("BUST", 25, 250);
	lblSplitBust = new MyLabel("BUST", 255, 250);

	lblHandBust->setColorRed();
	lblSplitBust->setColorRed();

	hand[0] = new Card();
	hand[0]->setPos(20, 220);
	hand[0]->setSurface(surface);

	splitHand[0] = new Card();
	splitHand[0]->setPos(250, 220);
	splitHand[0]->setSurface(surface);

	// Assign empty cards to hands for positioning
	for(int i = 1; i < 11; i++)
	{
		SDL_Rect handPos = hand[i-1]->getPos();
		SDL_Rect splitPos = splitHand[i-1]->getPos();

		hand[i] = new Card();
		hand[i]->setPos(handPos.x + 15, handPos.y + 4);
		hand[i]->setSurface(surface);

		splitHand[i] = new Card();
		splitHand[i]->setPos(splitPos.x + 15, splitPos.y + 4);
		splitHand[i]->setSurface(surface);
	}
}

Player::~Player()
{
	delete lblCash;
	delete playerLabel;
	delete splitLabel;
	delete lblHandScore;
	delete lblSplitScore;
	delete lblHandBust;
	delete lblSplitBust;
	delete[] hand;
	delete[] splitHand;
}

int Player::bet(int amount)
{
	if(cash >=amount)
	{
		cash -= amount;
		return amount;
	}
	else
	{
		amount = cash;
		cash = 0;
		return amount;
	}
}

void Player::win(int amount)
{
	cash += amount;
}

int Player::getCash()
{
	return cash;
}

int Player::getHandScore()
{
	return handScore;
}

int Player::getSplitScore()
{
	return splitScore;
}

std::string Player::getCashString()
{
	std::string retString;
	std::stringstream ss;
	ss << cash;
	retString = "$" + ss.str();

	return retString;
}

std::string Player::getHandScoreString()
{
	if(handScore == 0)
		return "-";

	std::string retString;
	std::stringstream ss;
	ss << handScore;
	retString = ss.str();

	return retString;
}

std::string Player::getSplitScoreString()
{
	std::string retString;
	std::stringstream ss;
	ss << splitScore;
	retString = ss.str();

	return retString;
}

void Player::dealCard(Card *newCard)
{
	hand[handPos]->setClip(newCard->getClip()->x, newCard->getClip()->y);
	hand[handPos]->setValue(newCard->getValue());
	hand[handPos]->setRank(newCard->getRank());
	handScore += hand[handPos]->getValue();

	if(handScore > 21)
		handReduceAce();
	handPos++;
}

/*  Splits current two-card hand into two one-card hands
	and deals one extra card to the split hand */
void Player::splitCurrentHand()
{
	handScore -= hand[--handPos]->getValue();
	dealSplit(hand[handPos]);
	hand[handPos]->setValue(0);
	split = true;
}

void Player::dealSplit(Card *newCard)
{
	splitHand[splitPos]->setClip(newCard->getClip()->x, newCard->getClip()->y);
	splitHand[splitPos]->setValue(newCard->getValue());
	splitHand[splitPos]->setRank(newCard->getRank());
	splitScore += splitHand[splitPos]->getValue();

	if(splitScore > 21)
		splitReduceAce();

	splitPos++;
}

void Player::clearHands()
{
	for(int i = 0; i < 11; i++)
	{
		hand[i]->setValue(0);
		splitHand[i]->setValue(0);
	}

	handPos = 0;
	splitPos = 0;
	handScore = 0;
	splitScore = 0;
}

/*  Checks for and reduces one Ace from 11 to 1 value within hand */
void Player::handReduceAce()
{
	for(int i = 0; i < 11; i++)
	{
		if(hand[i]->getRank() == ACE && hand[i]->getValue() != 1)
		{
			hand[i]->setValue(1);
			handScore -= 10;
			break;
		}
		else if(hand[i]->getRank() == 0)
			break;
	}
}

/*  Checks for and reduces one Ace from 11 to 1 value within split */
void Player::splitReduceAce()
{
	for(int i = 0; i < 11; i++)
	{
		if(splitHand[i]->getRank() == ACE && splitHand[i]->getValue() != 1)
		{
			splitHand[i]->setValue(1);
			splitScore -= 10;
			break;
		}
		else if(splitHand[i]->getRank() == 0)
			break;
	}
}

void Player::handBust()
{
	handBusted = true;
}

void Player::splitBust()
{
	splitBusted = true;
	split = false;
}

void Player::clearBust()
{
	handBusted = false;
	splitBusted = false;
}

bool Player::hasPair()
{
	return (hand[0]->getRank() == hand[1]->getRank() ? true : false);
}

bool Player::isSplit()
{
	return split;
}

void Player::stopSplit()
{
	split = false;
}

/*  Updates all screen information for player */
void Player::update(SDL_Surface *screen)
{
	playerLabel->applySurface(screen, NULL);
	lblHandScore->setMessage(getHandScoreString());
	lblHandScore->applySurface(screen, NULL);
	lblCash->setMessage("Cash: " + getCashString());
	lblCash->applySurface(screen, NULL);

	for(int i = 0; i < 11; i++)
	{
		if(hand[i]->getValue() != 0)
		{
			hand[i]->applySurface(screen);
		}
		else
			break;
	}

	if(splitHand[0]->getValue() != 0)
	{
		splitLabel->applySurface(screen, NULL);
		lblSplitScore->setMessage(getSplitScoreString());//getSplitScoreString());
		lblSplitScore->applySurface(screen, NULL);

		for(int i = 0; i < 11; i++)
		{
			if(splitHand[i]->getValue() != 0)
			{
				splitHand[i]->applySurface(screen);
			}
			else
				break;
		}
	}

	if(handBusted)
		lblHandBust->applySurface(screen, NULL);

	if(splitBusted)
		lblSplitBust->applySurface(screen, NULL);
}