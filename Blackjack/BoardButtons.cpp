#include "blackjack.h"
#include "BoardButtons.h"

/* Button positions are set by their respective constructors*/

DealButton::DealButton()
{
	pos.x = 20;
	pos.y = SCREEN_HEIGHT - 50;
	deactivate();
}

DealButton::~DealButton(){}

HitButton::HitButton()
{
	pos.x = 145;
	pos.y = SCREEN_HEIGHT - 50;
	deactivate();
}

HitButton::~HitButton(){}

StandButton::StandButton()
{
	pos.x = SCREEN_WIDTH/2 - 50;
	pos.y = SCREEN_HEIGHT - 50;
	deactivate();
}

StandButton::~StandButton(){}

DoubleButton::DoubleButton()
{
	pos.x = SCREEN_WIDTH - 245;
	pos.y = SCREEN_HEIGHT - 50;
	deactivate();
}

DoubleButton::~DoubleButton(){}

SplitButton::SplitButton()
{
	pos.x = SCREEN_WIDTH - 120;
	pos.y = SCREEN_HEIGHT - 50;
	deactivate();
}

SplitButton::~SplitButton(){}

PotButton::PotButton()
{
	pos.x = SCREEN_WIDTH - 120;
	pos.y = SCREEN_HEIGHT - 160;
	deactivate();
}

PotButton::~PotButton(){}

ChipButton::ChipButton()
{
	//Modify values for ChipButton
	thisClip.w = thisClip.h = 48;

	buttonWidth = 48;
	buttonHeight = 48;
	
	clips[buttonOut].x = clips[buttonOut].y = 0;
	clips[buttonOut].w = clips[buttonOut].h = 48;

	clips[buttonOver].x = clips[buttonOver].y = 0;
	clips[buttonOver].w = clips[buttonOver].h = 48;

	clips[buttonDown].x = 48;
	clips[buttonDown].y = 0;
	clips[buttonDown].w = 48;
	clips[buttonDown].h = 48;

	clips[buttonDark].x = clips[buttonDark].y = 0;
	clips[buttonDark].w = clips[buttonDark].h = 48;
	

}

ChipButton::~ChipButton(){}

/*  Since Chip buttons all use one class, set positions individually */
void ChipButton::setPos(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

void ChipButton::activate()
{
	active = true;
	thisClip = clips[buttonOut];
}