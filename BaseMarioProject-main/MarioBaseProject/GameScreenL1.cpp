#include "GameScreenL1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"

void GameScreenL1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
					  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	m_level_map = new LevelMap(map);

}

GameScreenL1::GameScreenL1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();

}

GameScreenL1::~GameScreenL1() 
{
	m_background_texture = nullptr;
	m_pow_block = nullptr;
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
	m_pow_block->Render();
}
void GameScreenL1::Update(float deltaTime, SDL_Event e)
{
	// my_character->Update(deltaTime, e);
	Mario->Update(deltaTime, e);
	Luigi->Update(deltaTime, e);

	if (Collisions::Instance()->Circle(Mario, Luigi))
	{
		cout << "Circle Hit!" << endl;
	}
	if (Collisions::Instance()->Box(Mario->GetCollisionsBox(), Luigi->GetCollisionsBox()))
	{
		cout << "Box Hit!" << endl;
	}

}

void GameScreenL1::UpdatePOWBlock()
{

}

bool GameScreenL1::SetUpLevel()
{
	SetLevelMap();
	// my_character = new Character(m_renderer, "Images/Mario.png", Vector2D(64, 100));
	Mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 100),m_level_map);
	if (Mario == nullptr)
	{
		std::cout << "Maroi is Nullptr: Error: " << SDL_GetError() << endl;
	}

	Luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 100),m_level_map);
	if (Luigi == nullptr)
	{
		std::cout << "Loogi is Nullptr: Error: " << SDL_GetError() << endl;
	}

	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	m_pow_block = new POWBlock(m_renderer, m_level_map);
}