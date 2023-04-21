#pragma once
#ifndef _POWBLOCK_H
#define _POWBLICK_H
#include "Texture2D.h"
#include "LevelMap.h"
#include <SDL.h>
#include "Commons.h"
#include <iostream>

class POWBlock
{
public:
	POWBlock(SDL_Renderer* renderer, LevelMap* map);
	~POWBlock();
	void Render();
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_single_sprite_w, m_texture->GetHeight()); }
	void TakeHit();
	bool IsAvailable() { return m_num_hits_left > 0; };

private:
	SDL_Renderer* m_renderer;
	Vector2D m_position; 
	Texture2D* m_texture;
	LevelMap* m_level_map;

	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_num_hits_left;


};

#endif