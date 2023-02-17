//Be grateful for humble beginnings, because the next level will always require so much more of you

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include <iostream>
using namespace std;

//globals
SDL_Window* g_window = nullptr;

int main(int argc, char* args[])
{



	//func prototypes
	bool InitSDL();
	void CloseSDL();

	//sdl setup good?
	if (InitSDL())
	{
		SDL_Delay(5000);
	}
	CloseSDL();


	return 0;
}
bool InitSDL() 
{
	//setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL Didn't initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//setup functioned, creating window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//did it work?
		if (g_window == nullptr)
		{
			//failed
			cout << "Window didn't create. Error: " << SDL_GetError();
			return false;
		}
	}
}
void CloseSDL()
{
	//release window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}