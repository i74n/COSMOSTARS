#pragma once
#include "Entity.h"

class Asteroid:public Entity{
	float speed;
	int reward;
	Texture explosionTexture;
	Sprite explosionSprite;
	float explosionFrame;
	float scale;
public:
	int hp;
	Asteroid(float prescale = 0);
	MoveResult move(float time);
	void setScale();
	bool isAlive();
	void getDamage();
	float getScale();
	int getReward();
	bool isExploded();
	Sprite explosion(float time);
};