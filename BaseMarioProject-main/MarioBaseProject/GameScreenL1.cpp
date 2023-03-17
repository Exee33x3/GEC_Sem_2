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
	// delete my_character;
	// my_character = nullptr;

	delete Mario;
	Mario = nullptr;

	delete Luigi;
	Luigi = nullptr;
}

void GameScreenL1::Render() 
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	// my_character->Render();
	Mario->Render();
	Luigi->Render();
}
void GameScreenL1::Update(float deltaTime, SDL_Event e)
{
	// my_character->Update(deltaTime, e);
	Mario->Update(deltaTime, e);
	Luigi->Update(deltaTime, e);
}

bool GameScreenL1::SetUpLevel()
{
	// my_character = new Character(m_renderer, "Images/Mario.png", Vector2D(64, 100));
	Mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 100));
	if (Mario == nullptr)
	{
		std::cout << "Maroi is Nullptr: Error: " << SDL_GetError() << endl;
	}

	Luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 100));
	if (Luigi == nullptr)
	{
		std::cout << "Loogi is Nullptr: Error: " << SDL_GetError() << endl;
	}

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