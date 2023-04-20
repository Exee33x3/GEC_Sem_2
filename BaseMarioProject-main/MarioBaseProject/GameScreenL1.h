#pragma once
#ifndef _GAMESCREENL1_H
#define _GAMESCREENL1_H

#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"

class Texture2D;

class GameScreenL1 : GameScreen
{
private:
	Texture2D* m_background_texture;
	bool SetUpLevel();
	//Character* my_character;
	CharacterMario* Mario;
	CharacterLuigi* Luigi;

	void SetLevelMap();
	LevelMap* m_level_map;

public:
	GameScreenL1(SDL_Renderer* renderer);
	~GameScreenL1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;



};


#endif // _GAMESCREENL1_H
