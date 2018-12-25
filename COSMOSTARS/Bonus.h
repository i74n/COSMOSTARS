#pragma once
#include "Entity.h"

class Bonus:public Entity{
public:
	Buff buff;
	Bonus(Vector2f playerPose);
	MoveResult move(float time);
	bool isAlive();
	Buff getBuff();
};