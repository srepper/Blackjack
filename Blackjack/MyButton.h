#pragma once
#include "ScreenObject.h"

class MyButton : public ScreenObject
{
protected:
	enum {buttonOut, buttonOver, buttonDown, buttonDark};
	SDL_Rect clips[4];
	int buttonWidth;
	int buttonHeight;
	bool active;
	bool clipChange;
	
public:
	MyButton();
	~MyButton();
	void activate();
	void deactivate();
	bool isActive();
	bool clipChanged();
	bool mouseMotion(int x, int y);
	bool mouseClick(int x, int y);
};