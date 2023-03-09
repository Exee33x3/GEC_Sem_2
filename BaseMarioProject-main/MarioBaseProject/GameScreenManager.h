#pragma once
#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H
#include "Commons.h"
#include <SDL.h>


class GameScreenManager
{
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

private:
	SDL_Renderer* m_renderer;
	GameScreen* m_current_screen;

};


void GameScreen();


#endif
