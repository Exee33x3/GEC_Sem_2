#include "GameScreenL1.h"
#include <iostream>
#include "Texture2D.h"

GameScreenL1::GameScreenL1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();

}

GameScreenL1::~GameScreenL1() 
{
	m_background_texture = nullptr;
	delete my_character;
	my_character = nullptr;
}

void GameScreenL1::Render() 
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	my_character->Render();
}
void GameScreenL1::Update(float deltaTime, SDL_Event e)
{
	my_character->Update(deltaTime, e);
}

bool GameScreenL1::SetUpLevel()
{
	my_character = new Character(m_renderer, "Images/Mario.png", Vector2D(64, 330));
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