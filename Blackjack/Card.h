#pragma once
#include "ScreenObject.h"
#include <string>
#include "SDL.h"

enum RANK {ACE = 1, JACK = 11, QUEEN, KING};

class Card : public ScreenObject
{	
	int suit;
	int rank;	
	int value;

public:
	Card();
	~Card();
	void setSuit(int s);
	void setRank(int r);
	void setValue();
	void setValue(int val);
	int getValue();
	int getRank();
};