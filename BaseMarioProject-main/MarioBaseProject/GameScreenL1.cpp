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
			if (Luigi->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				Luigi->CancelJump();
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
	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}

	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
}

void GameScreenL1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to the left / right?
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionsBox().width * 0.5f) || m_enemies[
					i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionsBox().width * 0.55f))
					m_enemies[i]->SetAlive(false);
			}
			//now do the update

			m_enemies[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->
				GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], Mario))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						//kill mario  //no
					}

				}
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update

		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}

}

void GameScreenL1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	m_enemies.push_back( new CharacterKoopa(m_renderer, "Images/Koopa.png", m_level_map, position, direction, speed));
}
