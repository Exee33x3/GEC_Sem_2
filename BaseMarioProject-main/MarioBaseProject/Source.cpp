//Be grateful for humble beginnings, because the next level will always require so much more of you

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include <iostream>
#include "Texture2D.h"
using namespace std;
SDL_Renderer* g_renderer = nullptr;
Texture2D* g_texture = nullptr;

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

	//load texture
	g_texture = new Texture2D(g_renderer);
	if (!g_texture->LoadFromFile("Images/test.bmp"))
	{
		return false;
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
	delete g_texture;
	g_texture = nullptr;
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
}

bool Update()
{
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type)
	{
	case SDL_QUIT:
		return true;
		break;

	}
	return false;
}

void Render()
{
	SDL_SetRenderDrawColor(g_renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(g_renderer);
	//set texture location
	SDL_Rect renderLocation = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	//render to screen
	g_texture->Render(Vector2D(), SDL_FLIP_NONE);
	//update screen
	SDL_RenderPresent(g_renderer);

}

