#pragma once
#include "Player.h"
#include "Entity.h"

class Laser:public Entity{
	bool alive;
public:
	Laser(Player * player);
	MoveResult move(float time);
	bool isAlive();
	void hit();
};