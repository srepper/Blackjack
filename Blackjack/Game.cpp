#include "blackjack.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Game.h"

Game::Game()
{
	quit = false;
	blackjack = false;
	screen = NULL;
	dealButton = new DealButton();
	hitButton = new HitButton();
	standButton = new StandButton();
	doubleButton = new DoubleButton();
	splitButton = new SplitButton();
	potButton = new PotButton();
	chip1 = new ChipButton();
	chip5 = new ChipButton();
	chip25 = new ChipButton();
	chip50 = new ChipButton();
	chip100 = new ChipButton();
}

Game::~Game()
{
	cleanUp();

	delete dealButton;
	delete hitButton;
	delete standButton;
	delete doubleButton;
	delete splitButton;
	delete potButton;

	delete chip1;
	delete chip5;
	delete chip25;
	delete chip50;
	delete chip100;

	delete lblBet;
	delete lblResults;
	delete lblBlackjack;

	delete deck;
	delete player;
	delete dealer;
}

/*  Load an image from a given filename string
 *  and return color keyed, optimized image
 */
SDL_Surface *Game::loadImage(std::string filename)
{
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *optimizedImage = NULL;
	loadedImage = IMG_Load(filename.c_str());

	if(loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);

		if(optimizedImage != NULL)
		{
			//Color key (pure yellow)
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0xFF, 0xFF, 0);
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
		}
	}

	return optimizedImage;
}

/*  Apply a surface to the screen  */
void Game::applySurface(int x, int y, SDL_Surface *source, 
				   SDL_Surface *destination, SDL_Rect *clip = NULL)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset);
}

/*  Initialize all SDL subsystems & set up the screen */
bool Game::init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen == NULL)
		return false;
	
	if(TTF_Init() == -1)
		return false;
	
	SDL_WM_SetCaption("Blackjack", NULL);

	return true;
}

/*  Load images used by the game */
bool Game::loadImages()
{
	deckImage = loadImage("Images/deckBlue.png");
	cards = loadImage("Images/playing_cards.png");
	dealButton->loadImage("Images/dealButton.png");
	hitButton->loadImage("Images/hitButton.png");
	standButton->loadImage("Images/standButton.png");
	doubleButton->loadImage("Images/doubleButton.png");
	splitButton->loadImage("Images/splitButton.png");
	potButton->loadImage("Images/potButton.png");
	chip1->loadImage("Images/chip-1.png");
	chip5->loadImage("Images/chip-5.png");
	chip25->loadImage("Images/chip-25.png");
	chip50->loadImage("Images/chip-50.png");
	chip100->loadImage("Images/chip-100.png");

	lblResults = new MyLabel("", SCREEN_WIDTH/2 - 50, 160);
	lblBlackjack = new MyLabel("Blackjack!", SCREEN_WIDTH/2 - 50, 135);
	lblBet = new MyLabel("Place a bet.",
			SCREEN_WIDTH - 260, SCREEN_HEIGHT - 155);
		
	if(deckImage == NULL || cards == NULL || !(dealButton->imageLoaded() &&
		hitButton->imageLoaded() &&	standButton->imageLoaded() &&
		doubleButton->imageLoaded() && splitButton->imageLoaded() && 
		potButton->imageLoaded() && chip1->imageLoaded() && 
		chip5->imageLoaded() &&	chip25->imageLoaded() && 
		chip50->imageLoaded() && chip100->imageLoaded()))
			return false;
	
	return true;
}

/*  Free images and quit SDL */
void Game::cleanUp()
{
	SDL_FreeSurface(deckImage);
	SDL_FreeSurface(cards);
	//SDL_FreeSurface(screen);

	//SDL_Quit();
}

/*  Draw the game board */
void Game::updateBoard(SDL_Surface *screen)
{
	// Green background
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x32, 0x8C, 0x32));

	// Buttons
	dealButton->applySurface(screen);
	hitButton->applySurface(screen);
	standButton->applySurface(screen);
	doubleButton->applySurface(screen);
	splitButton->applySurface(screen);
	potButton->applySurface(screen);

	chip1->applySurface(screen);
	chip5->applySurface(screen);
	chip25->applySurface(screen);
	chip50->applySurface(screen);
	chip100->applySurface(screen);

	// Deck, dealer, and player
	applySurface(SCREEN_WIDTH - 97, 20, deckImage, screen);
	player->update(screen);
	dealer->update(screen);

	// End-of-hand labels
	if(chip1->isActive())
	{
		lblBet->applySurface(screen, NULL);
		lblResults->applySurface(screen, NULL);
	}

	if(blackjack)
		lblBlackjack->applySurface(screen, NULL);

}

/*  Activate all betting chips; deactivate all buttons */
void Game::enableBetting()
{
	chip1->activate();
	chip5->activate();
	chip25->activate();
	chip50->activate();
	chip100->activate();
	potButton->deactivate();
	dealButton->deactivate();
	hitButton->deactivate();
	standButton->deactivate();
	splitButton->deactivate();
	doubleButton->deactivate();

}

/*  Deactivate all betting chips */
void Game::disableBetting()
{
	blackjack = false;
	chip1->deactivate();
	chip5->deactivate();
	chip25->deactivate();
	chip50->deactivate();
	chip100->deactivate();
	potButton->deactivate();
}

/*  Deal starting hands to player & dealer */
void Game::dealHands()
{
	for(int i = 0; i < 2; i++)
	{
		player->dealCard(deck->getNextCard());
		dealer->dealCard(deck->getNextCard());
	}

	if(player->hasPair())
		splitButton->activate();

	if(player->getCash() < dealer->getPot())
	{
		doubleButton->deactivate();
		splitButton->deactivate();
	}

	checkBlackjack();
}

/*  Check for blackjack after deal */
void Game::checkBlackjack()
{
	int dScore = dealer->checkBlackjack();
	int pScore = player->getHandScore();
	if(pScore == 21 || dScore == 21)
	{
		blackjack = true;
		dealer->showHidden(cards);
		
		if(pScore == dScore)
		{
			lblResults->setMessage("Push (tie)");
			player->win(dealer->getPot());
		}
		else if(pScore > dScore)
		{
			lblResults->setMessage("You win!");
			player->win(dealer->getPot() * 2.5);
		}
		else if(pScore < dScore)
		{
			lblResults->setMessage("You lose.");
		}

		dealer->clearPot();
		enableBetting();
	}
}

/*  Process hands for winnings/losses */
void Game::handResults()
{
	dealer->showHidden(cards);
	
	int pScore = player->getHandScore();
	int psScore = player->getSplitScore();
	
	if(pScore <= 21 || (psScore <= 21 && psScore != 0))
	{
		if(dealer->getScore() > 21)
			dealer->reduceAce();

		while(dealer->getScore() < 17)
			dealer->dealCard(deck->getNextCard());
	}

	int dScore = dealer->getScore();
	if(dScore > 21)
		dealer->bust();

	int winnings = dealer->getPot();

	if(psScore != 0)
	{
		int bet = winnings / 2;

		if((dScore <= 21 && dScore > psScore) || psScore > 21)
			winnings -= bet;
		else if(psScore == dScore)
			winnings -= bet / 2;

		if((dScore <= 21 && dScore > pScore) || pScore > 21)
			winnings -= bet;
		else if(pScore == dScore)
			winnings -= bet / 2;

		if(winnings < bet)
			lblResults->setMessage("You lose.");
		else if(winnings == bet)
			lblResults->setMessage("Break even.");
		else
			lblResults->setMessage("You win!");
	}
	else
	{
		if(pScore == dScore)
		{
			lblResults->setMessage("Push (tie)");
			winnings /= 2;
		}
		else if((dScore <= 21 && dScore > pScore) || pScore > 21)
		{
			winnings = 0;
			lblResults->setMessage("You lose.");
		}
		else
			lblResults->setMessage("You win!");
	}

	player->win(winnings * 2);
	dealer->clearPot();
	
	if(player->getCash() == 0)
	{
		lblResults->setMessage("Bankrupt!  $500 restored.");
		player->win(500);
	}

	enableBetting();
}


int Game::run()
{
	if(init() == false)
		return 1;

	if(loadImages() == false)
		return 1;

	deck = new DoubleDeck(cards);
	player = new Player(cards);
	dealer = new Dealer(cards);
	dealer->setCardBack(loadImage("Images/cardBackBlue.png"));

	// Set individual chip positions
	chip1->setPos(SCREEN_WIDTH - 300, SCREEN_HEIGHT - 110);
	chip5->setPos(SCREEN_WIDTH - 242, SCREEN_HEIGHT - 110);
	chip25->setPos(SCREEN_WIDTH - 184, SCREEN_HEIGHT - 110);
	chip50->setPos(SCREEN_WIDTH - 126, SCREEN_HEIGHT - 110);
	chip100->setPos(SCREEN_WIDTH - 68, SCREEN_HEIGHT - 110);

	updateBoard(screen);
	
	// Draw to screen
	if(SDL_Flip(screen) == -1)
		return 1;

	// Game loop
	while(quit == false)
	{
		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				quit = true;
				continue;
			}

			handleEvents();
		}

		//Update screen each iteration
		if(SDL_Flip(screen) == -1)
			return 1;
	}

    //Quit SDL
    //SDL_Quit();

	return 0;
}


void Game::handleEvents()
{
	int x = 0;
	int y = 0;

	
	//If mouse moved
	if(event.type == SDL_MOUSEMOTION)
	{
		x = event.motion.x;
		y = event.motion.y;

		if(dealButton->isActive())
			dealButton->mouseMotion(x, y);
		
		if(hitButton->isActive())
			hitButton->mouseMotion(x,y);
		
		if(standButton->isActive())
			standButton->mouseMotion(x, y);
		
		if(doubleButton->isActive())
			doubleButton->mouseMotion(x, y);
		
		if(splitButton->isActive())
			splitButton->mouseMotion(x, y);

		if(potButton->isActive())
			potButton->mouseMotion(x, y);
	}
	//If mouse click
	else if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		x = event.button.x;
		y = event.button.y;
		
		if(dealButton->isActive() && dealButton->mouseClick(x, y))
		{
			player->clearHands();
			player->stopSplit();
			dealer->clearHand();
			disableBetting();
			player->clearBust();
			dealer->clearBust();
			dealButton->deactivate();
			hitButton->activate();
			standButton->activate();
			doubleButton->activate();
			dealHands();
		}
		
		if(hitButton->isActive() && hitButton->mouseClick(x,y))
		{
			doubleButton->deactivate();
			if(player->isSplit())
			{
				player->dealSplit(deck->getNextCard());
				
				if(player->getSplitScore() > 21)
				{
					player->splitBust();
					player->stopSplit();
					player->dealCard(deck->getNextCard());
				}
				else if(player->getSplitScore() == 21)
				{
					player->stopSplit();
					player->dealCard(deck->getNextCard());

					if(player->getHandScore() == 21)
						handResults();
				}
				
			}
			else
			{
				splitButton->deactivate();
				player->dealCard(deck->getNextCard());
				
				if(player->getHandScore() > 21)
				{
					player->handBust();
					handResults();
				}
				else if(player->getHandScore() == 21)
					handResults();
			}
		}
		
		if(standButton->isActive() && standButton->mouseClick(x, y))
		{

			if(player->isSplit())
			{
				player->stopSplit();
				player->dealCard(deck->getNextCard());

				if(player->getHandScore() == 21)
					handResults();
			}
			else
				handResults();
			
		}
		
		if(doubleButton->isActive() && doubleButton->mouseClick(x, y))
		{
			dealer->updatePot(player->bet(dealer->getPot()));
			player->dealCard(deck->getNextCard());
			handResults();
		}
		
		if(splitButton->isActive() && splitButton->mouseClick(x, y))
		{
			doubleButton->deactivate();
			splitButton->deactivate();

			dealer->updatePot(player->bet(dealer->getPot()));
			player->splitCurrentHand();
			player->dealSplit(deck->getNextCard());

			if(player->getSplitScore() == 21)
			{
				player->stopSplit();
				player->dealCard(deck->getNextCard());
			}

		}

		if(potButton->isActive() && potButton->mouseClick(x, y))
		{
			player->win(dealer->getPot());
			dealer->clearPot();
			dealButton->deactivate();
			potButton->deactivate();
		}
		
		if(chip1->isActive() && chip1->mouseClick(x, y))
		{
			if(!dealButton->isActive())
				dealButton->activate();

			if(!potButton->isActive())
				potButton->activate();

			dealer->updatePot(player->bet(1));
		}
	
		if(chip5->isActive() && chip5->mouseClick(x, y))
		{
			if(!dealButton->isActive())
				dealButton->activate();
			
			if(!potButton->isActive())
				potButton->activate();

			dealer->updatePot(player->bet(5));
		}
		
		if(chip25->isActive() && chip25->mouseClick(x, y))
		{
			if(!dealButton->isActive())
				dealButton->activate();
			
			if(!potButton->isActive())
				potButton->activate();

			dealer->updatePot(player->bet(25));
		}
		
		if(chip50->isActive() && chip50->mouseClick(x, y))
		{
			if(!dealButton->isActive())
				dealButton->activate();
			
			if(!potButton->isActive())
				potButton->activate();

			dealer->updatePot(player->bet(50));
		}
		
		if(chip100->isActive() && chip100->mouseClick(x, y))
		{
			if(!dealButton->isActive())
				dealButton->activate();
			
			if(!potButton->isActive())
				potButton->activate();

			dealer->updatePot(player->bet(100));
		}
	}
	//If mouse is released
	else if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
	{
		x = event.button.x;
		y = event.button.y;

		if(dealButton->isActive())
			dealButton->mouseMotion(x, y);
		
		if(hitButton->isActive())
			hitButton->mouseMotion(x,y);
				
		if(standButton->isActive())
			standButton->mouseMotion(x, y);
		
		if(doubleButton->isActive())
			doubleButton->mouseMotion(x, y);
			
		if(splitButton->isActive())
			splitButton->mouseMotion(x, y);

		if(potButton->isActive())
			potButton->mouseMotion(x, y);
		
		if(chip1->isActive())
			chip1->mouseMotion(x, y);
		
		if(chip5->isActive())
			chip5->mouseMotion(x, y);
		
		if(chip25->isActive())
			chip25->mouseMotion(x, y);
		
		if(chip50->isActive())
			chip50->mouseMotion(x, y);
		
		if(chip100->isActive())
			chip100->mouseMotion(x, y);
	}

	updateBoard(screen);
}