#include "MyLabel.h"

MyLabel::MyLabel(std::string msg, int xLoc, int yLoc)
{
	message = msg;
	font = TTF_OpenFont("Font/ariblk.ttf", 20);
	textColor = newColor(220, 220, 0);
	surface = TTF_RenderText_Solid(font, message.c_str(), textColor);
	pos.x = xLoc;
	pos.y = yLoc;
}

MyLabel::~MyLabel()
{
	cleanUp();
}

void MyLabel::setMessage(std::string msg)
{
	message = msg;
	SDL_FreeSurface(surface);
	surface = TTF_RenderText_Solid(font, message.c_str(), textColor);

}

void MyLabel::setColorRed()
{
	textColor = newColor(220, 0, 0);
	SDL_FreeSurface(surface);
	surface = TTF_RenderText_Solid(font, message.c_str(), textColor);
}

void MyLabel::setColorYellow()
{
	textColor = newColor(220, 220, 0);
	SDL_FreeSurface(surface);
	surface = TTF_RenderText_Solid(font, message.c_str(), textColor);
}

SDL_Color MyLabel::newColor(int r, int g, int b)
{
	SDL_Color c = {r, g, b};
	return c;
}