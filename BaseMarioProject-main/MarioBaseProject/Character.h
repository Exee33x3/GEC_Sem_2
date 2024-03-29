#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include <string>
#include "LevelMap.h"
using namespace std;

class Texture2D;

class Character
{
	

protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	bool m_moving_left;
	bool m_moving_right;
	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;
	float m_collision_radius;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void Jump(float deltaTime);

public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
	void AddGravity(float deltaTime);
	float GetCollisionRadius();
	Rect2D GetCollisionsBox();
	void CancelJump() {  m_jumping = false;  };
	bool IsJumping() { return m_jumping; };
	FACING m_facing_direction;

private:

	LevelMap* m_current_level_map;

};



#endif
