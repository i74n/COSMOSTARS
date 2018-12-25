#pragma once
#include "Entity.h"

class Map:public Entity{
	float displace;
	float crement;
public:
	Map();
	MoveResult move(float time);
	bool isAlive();
};