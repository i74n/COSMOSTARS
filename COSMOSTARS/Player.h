#pragma once
#include "Entity.h"
#include "Bonus.h"

class Player:public Entity{
	int scores;
	float shot_cooldown;
public:
	Player();
	MoveResult move(float time);
	void setBuff(Buff buff);
	bool isAlive();
	std::string getScores();
	void setScores(int crement);
};