#pragma once

#include "Character.h"




class CharacterKoopa : public Character
{
private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;
	float m_movement_speed;


protected:
	bool m_alive = true;

public:
	~CharacterKoopa();
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	void TakeDamage();
	void Jump();
	void FlipUp();
	void Render();
	void Update(float deltaTime, SDL_Event e);
	void SetAlive(bool isAlive);
	bool GetAlive() { return m_alive; };
	bool GetInjured() { return m_injured; };

};

