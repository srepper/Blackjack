#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "ScreenObject.h"

class MyLabel : public ScreenObject
{
protected:
	TTF_Font *font;
	SDL_Color textColor;
	std::string message;
	
public:
	MyLabel();
	MyLabel(std::string message, int xLoc, int yLoc);
	~MyLabel(void);
	void setMessage(std::string message);
	void setColorRed();
	void setColorYellow();
	SDL_Color newColor(int r, int g, int b);
};