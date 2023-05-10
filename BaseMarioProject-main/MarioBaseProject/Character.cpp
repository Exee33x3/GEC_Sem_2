#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"
#include "LevelMap.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map)
{
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		//o shit
		cout << "Failed to load texture!" << endl;
		return;
	}
	m_facing_direction = FACING_RIGHT;
	m_moving_left = false;
	m_moving_right = false;
	m_collision_radius = 15.0f;
	m_current_level_map = map;
}

Character::~Character() 
{
	m_renderer = nullptr;
}

void Character::Render() 
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{

	if (m_jumping)
	{
		m_position.y -= m_jump_force * deltaTime;
		m_jump_force -= deltaTime * JUMP_FORCE_DECREMENT;
		if (m_jump_force <= 0.0f)
		{
			m_jumping = false;
		}
	}

	int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;
	int head_position = (int)(m_position.y) / TILE_HEIGHT;

	if (m_current_level_map->GetTileAt(head_position, centralX_position) == 1)
	{
		CancelJump();
	}

	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		m_can_jump = true;
	}


	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}


}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}

void Character::MoveLeft(float deltaTime)
{
	m_facing_direction = FACING_LEFT;
	m_position.x -= deltaTime * MOVE_SPEED;
}

void Character::MoveRight(float deltaTime)
{
	m_facing_direction = FACING_RIGHT;
	m_position.x += deltaTime * MOVE_SPEED;
}

void Character::AddGravity(float deltaTime)
{
	if ((m_position.y + 64) <= (SCREEN_HEIGHT))
	{
		m_position.y += 200 * deltaTime;
	}
	else
	{
		m_can_jump = true;
	}
	

}

void Character::Jump(float deltaTime)
{
	m_jump_force = INITIAL_JUMP_FORCE;
	m_jumping = true;
	m_can_jump = false;
}
float Character::GetCollisionRadius()
{
	return m_collision_radius;
}

Rect2D Character::GetCollisionsBox()
{
	{ return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }
}
