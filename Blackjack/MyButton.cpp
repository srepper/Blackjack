#include "MyButton.h"

MyButton::MyButton()
{
	buttonWidth = 100;
	buttonHeight = 30;
	
	surface = NULL;
	thisClip.x = thisClip.y = 0;
	thisClip.w = 100;
	thisClip.h = 30;

	clips[buttonOut].x = 0;
	clips[buttonOut].y = 0;
	clips[buttonOut].w = 100;
	clips[buttonOut].h = 30;

	clips[buttonOver].x = 100;
	clips[buttonOver].y = 0;
	clips[buttonOver].w = 100;
	clips[buttonOver].h = 30;

	clips[buttonDown].x = 0;
	clips[buttonDown].y = 30;
	clips[buttonDown].w = 100;
	clips[buttonDown].h = 30;

	clips[buttonDark].x = 100;
	clips[buttonDark].y = 30;
	clips[buttonDark].w = 100;
	clips[buttonDark].h = 30;

	active = true;
	clipChange = false;
}

MyButton::~MyButton()
{
	cleanUp();
}

bool MyButton::clipChanged()
{
	return clipChange;
}

bool MyButton::isActive()
{
	return active;
}

void MyButton::activate()
{
	active = true;
	thisClip = clips[buttonOut];
}

void MyButton::deactivate()
{
	active = false;
	thisClip = clips[buttonDark];
}

/*  mouseMotion() also handles MOUSEBUTTONUP events */
bool MyButton::mouseMotion(int x, int y)
{
	//If the mouse is over the button
	if((x > pos.x) && (x < pos.x + buttonWidth) &&
		(y > pos.y) && (y < pos.y + buttonHeight))
	{
		//check for clip change
		if(!clipMatches(clips[buttonOver]))
			thisClip = clips[buttonOver];
		
		return true;
	}

	//else check for clip change
	if(!clipMatches(clips[buttonOut]))
		thisClip = clips[buttonOut];
	
	return false;
}

bool MyButton::mouseClick(int x, int y)
{
	//If the mouse is over the button
	if((x > pos.x) && (x < pos.x + buttonWidth) &&
		(y > pos.y) && (y < pos.y + buttonHeight))
	{
		//check for clip change
		if(!clipMatches(clips[buttonDown]))
			thisClip = clips[buttonDown];
		
		return true;
	}

	//else check for clip change
	if(!clipMatches(clips[buttonOut]))
		thisClip = clips[buttonOut];
	
	return false;
}