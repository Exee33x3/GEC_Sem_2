#include "GameScreenL1.h"
#include <iostream>
#include "Texture2D.h"

GameScreenL1(SDL_Renderer* renderer);
~GameScreenL1();

void Render() override;
void Update(float deltaTime, SDL_Event e) override;
