#include "CharacterLuigi.h"
#include "Texture2D.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{
	LuigiImage = new Texture2D(renderer);
	LuigiImage->LoadFromFile(imagePath);
	m_renderer = renderer;
	m_position = start_position;
}

CharacterLuigi::~CharacterLuigi()
{
	delete LuigiImage;
	LuigiImage = nullptr;
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_j:
			m_moving_left = true;
			break;
		case SDLK_l:
			m_moving_right = true;
			break;
		case SDLK_i:
			if (m_can_jump)
			{
				Jump(deltaTime);
			}
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_j:
			m_moving_left = false;
			break;
		case SDLK_l:
			m_moving_right = false;
			break;
		}
		break;
	}
	Character::Update(deltaTime, e);
}

