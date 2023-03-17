#pragma once
#include "Character.h"

class Texture2D;

class CharacterMario : public Character
{
private:

	Texture2D* MarioImage;



public:

	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~CharacterMario();

	void Update(float deltaTime, SDL_Event e);
};

