#pragma once
#include "SDL.h"
#include "MyButton.h"

class DealButton : public MyButton
{
public:
	DealButton();
	~DealButton();
};

class HitButton : public MyButton
{
public:
	HitButton();
	~HitButton();
};

class StandButton : public MyButton
{
public:
	StandButton();
	~StandButton();
};

class DoubleButton : public MyButton
{
public:
	DoubleButton();
	~DoubleButton();
};

class SplitButton : public MyButton
{
public:
	SplitButton();
	~SplitButton();
};

class PotButton : public MyButton
{
public:
	PotButton();
	~PotButton();
};

class ChipButton : public MyButton
{
	int value;
public:
	ChipButton();
	~ChipButton();
	void setPos(int x, int y);
	void blankSurface(SDL_Surface *screen);
	void activate();
};