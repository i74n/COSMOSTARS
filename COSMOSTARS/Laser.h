#pragma once
#include "Player.h"
#include "Entity.h"

class Laser:public Entity{
	bool alive;
public:
	Laser(Player * player);
	Move_result move(float time);
	bool isAlive();
	void hit();
};