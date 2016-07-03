#pragma once
#include "DoubleDeck.h"
#include "BoardButtons.h"
#include "Player.h"
#include "Dealer.h"
#include "SDL.h"
#include <string>

class Game
{
	DoubleDeck *deck;
	Player *player;
	Dealer *dealer;
	SDL_Surface *screen;
	SDL_Surface *deckImage;
	SDL_Surface *cards;
	SDL_Event event;

	bool quit;
	bool blackjack;

	MyLabel *lblBet;
	MyLabel *lblResults;
	MyLabel *lblBlackjack;
		
	DealButton *dealButton;
	HitButton *hitButton;
	StandButton *standButton;
	DoubleButton *doubleButton;
	SplitButton *splitButton;
	PotButton *potButton;

	ChipButton *chip1;
	ChipButton *chip5;
	ChipButton *chip25;
	ChipButton *chip50;
	ChipButton *chip100;

public:
	Game();
	~Game();
	
	SDL_Surface *loadImage(std::string filename);
	void applySurface(int x, int y, SDL_Surface* source, 
				   SDL_Surface* destination, SDL_Rect* clip);		   
	bool init();
	bool loadImages();
	void cleanUp();
	void updateBoard(SDL_Surface *screen);
	void enableBetting();
	void disableBetting();
	void dealHands();
	void checkBlackjack();
	void handResults();
	void displayWin();
	void displayLoss();
	int run();
	void handleEvents();
};