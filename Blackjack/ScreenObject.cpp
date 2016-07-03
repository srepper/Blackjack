#include "ScreenObject.h"
#include "SDL_image.h"

ScreenObject::ScreenObject()
{
	//Surface set to null for later error checking
	surface = NULL;
}

ScreenObject::~ScreenObject(){}

/* Load image into object */
void ScreenObject::loadImage(std::string filename)
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

	surface = optimizedImage;
}

/* Used to verify image has been properly loaded into object */
bool ScreenObject::imageLoaded()
{
	if(surface == NULL)
		return false;

	return true;
}

/* Apply object's surface to the screen */
void ScreenObject::applySurface(SDL_Surface *destination)
{
	SDL_BlitSurface(surface, &thisClip/*clip*/, destination, &pos);
}

/* Specify clip for applySurface */
void ScreenObject::applySurface(SDL_Surface *destination, SDL_Rect *newClip)
{
	SDL_BlitSurface(surface, newClip, destination, &pos);
}

/* Fill surface with background color */
void ScreenObject::freeSurface()
{
	surface = NULL;
}

SDL_Surface *ScreenObject::getSurface()
{
	return surface;
}

void ScreenObject::setSurface(SDL_Surface *newSurface)
{
	surface = newSurface;
}

void ScreenObject::setClip(SDL_Rect newClip)
{
	thisClip.x = newClip.x;
	thisClip.y = newClip.y;
}

void ScreenObject::setClip(int x, int y)
{
	thisClip.x = x;
	thisClip.y = y;
}

void ScreenObject::setClip(int x, int y, int w, int h)
{
	thisClip.x = x;
	thisClip.y = y;
	thisClip.w = w;
	thisClip.h = h;
}

void ScreenObject::setPos(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

SDL_Rect *ScreenObject::getClip()
{
	return &thisClip;
}

SDL_Rect ScreenObject::getPos()
{
	return pos;
}

bool ScreenObject::clipMatches(SDL_Rect inClip)
{
	if(thisClip.x == inClip.x && thisClip.y == inClip.y)
		return true;
	return false;
}

void ScreenObject::cleanUp()
{
	if(surface != NULL)
		SDL_FreeSurface(surface);
}