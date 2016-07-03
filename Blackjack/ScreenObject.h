#pragma once
#include "SDL.h"
#include <string>

class ScreenObject
{
protected:
	SDL_Surface *surface;
	SDL_Rect thisClip;
	SDL_Rect pos;
public:
	ScreenObject();
	~ScreenObject();
	void loadImage(std::string filename);
	bool imageLoaded();
	void applySurface(SDL_Surface *destination);
	void applySurface(SDL_Surface *destination, SDL_Rect *newClip);
	void freeSurface();
	void setClip(SDL_Rect newClip);
	void setClip(int x, int y);
	void setClip(int x, int y, int w, int h);
	void setPos(int x, int y);
	void setSurface(SDL_Surface *newSurface);
	SDL_Surface *getSurface();
	SDL_Rect *getClip();
	SDL_Rect getPos();
	bool clipMatches(SDL_Rect inClip);
	void cleanUp();
};