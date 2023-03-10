//Be grateful for humble beginnings, because the next level will always require so much more of you

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include <iostream>
#include "Texture2D.h"
#include "GameScreenManager.h"
using namespace std;
SDL_Renderer* g_renderer = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;

//func prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();

//globals
SDL_Window* g_window = nullptr;

int main(int argc, char* args[])
{

	//sdl setup good?
	if (InitSDL())
	{
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
		g_old_time = SDL_GetTicks();
		bool quit = false;
		while (!quit)
		{
			Render();
			quit = Update();
		}
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

	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

	if (g_renderer != nullptr)
	{
		//init PNG Loading
		int imageFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imageFlags) & imageFlags))
		{
			cout << "SDL_Image didn't initialise. Error: " << IMG_GetError();
		}
	}
	else
	{
		cout << "Renderer didn't initialise. Error: " << SDL_GetError();
		return false;
	}


}
void CloseSDL()
{
	delete game_screen_manager;
	game_screen_manager = nullptr;
	//release window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
}

bool Update()
{
	Uint32 new_time = SDL_GetTicks();
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type)
	{
	case SDL_QUIT:
		return true;
		break;

	}
	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;
	return false;
}

void Render()
{

	SDL_SetRenderDrawColor(g_renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(g_renderer);
	//set texture location
	SDL_Rect renderLocation = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	//render to screen
	game_screen_manager->Render();
	//update screen
	SDL_RenderPresent(g_renderer);

}

