#pragma once
#include "Entity.h"

class Map:public Entity{
	float displace;
public:
	Map();
	Move_result move(float time);
	bool isAlive();
};