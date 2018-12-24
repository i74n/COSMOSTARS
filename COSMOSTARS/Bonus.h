#pragma once
#include "Entity.h"

enum Buff {HP, DEATHLESS, SPEEDUP};

class Bonus:public Entity{
public:
	Buff buff;
	Bonus(std::string path, Buff buff);
	Move_result move(float time);
	bool isAlive();
};