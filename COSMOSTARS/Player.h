#pragma once
#include "Entity.h"
#include "Bonus.h"

class Player:public Entity{
	int scores;
	float shot_cooldown;
public:
	Player();
	Move_result move(float time);
	void get_buff(Bonus bonus);
	bool isAlive();
	std::string getScores();
	void setScores(int crement);
};