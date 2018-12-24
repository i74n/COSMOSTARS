#include "Bonus.h"

Bonus::Bonus(std::string path, Buff buff):Entity(){
	this->buff = buff;
	makeTexture(path);
}

Move_result Bonus::move(float time){
	return stay;
}

bool Bonus::isAlive(){return true;}
 