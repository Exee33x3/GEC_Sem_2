#include "GameScreenL1.h"
#include <iostream>
#include "Texture2D.h"

GameScreenL1::GameScreenL1(SDL_Renderer* renderer)  : GameScreen(renderer)
{
	SetUpLevel();

}

GameScreenL1::~GameScreenL1() 
{
	m_background_texture = nullptr;
}

void Render() 
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}
void Update(float deltaTime, SDL_Event e)
{

}

bool SetUpLevel()
{
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
	else
	{
		return true;
	}
}