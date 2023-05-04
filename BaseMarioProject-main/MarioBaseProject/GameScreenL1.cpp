#include "GameScreenL1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"

void GameScreenL1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = 
					{ { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
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

	for (int i = 0; i < m_enemies.size(); i++)
	{
		delete m_enemies[i];
	}
	m_enemies.clear();

}

void GameScreenL1::Render() 
{
	//draw the enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}


	m_background_texture->Render(Vector2D(0, m_backgrould_yPos), SDL_FLIP_NONE);
	// my_character->Render();
	Mario->Render();
	Luigi->Render();
	m_pow_block->Render();
}
void GameScreenL1::Update(float deltaTime, SDL_Event e)
{
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_backgrould_yPos = sin(m_wobble);
		m_backgrould_yPos *= 3.0f;
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_backgrould_yPos = 0.0f;
		}
	}

	UpdateEnemies(deltaTime, e);

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

	UpdatePOWBlock();
}

void GameScreenL1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(Mario->GetCollisionsBox(), m_pow_block->GetCollisionBox()))
	{            //WARNING: PROBABLY ONLY WORKS FOR MARIO
		if (m_pow_block->IsAvailable())
		{
			if (Mario->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				Mario->CancelJump();
			}

		}
	}
}

bool GameScreenL1::SetUpLevel()
{
	m_screenshake = false;
	m_backgrould_yPos = 0.0f;
	SetLevelMap();
	m_pow_block = new POWBlock(m_renderer, m_level_map);
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


}
void GameScreenL1::DoScreenShake() 
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
}

void GameScreenL1::UpdateEnemies(float deltaTime, SDL_Event e)
{

}

void GameScreenL1::CreateKoopa(Vector2D position, FACING direction, float speed)
{

}
