#include "Map.h"

Map::Map(){
	makeTexture("images/cosmos.png");
	sprite.setScale(2, 2);
	displace = 0;
}

MoveResult Map::move(float time){
	if (int(displace -= time*5000) <= -1920)
		displace = 0;

	setPosition(displace, 0);

	return stay;
}
bool Map::isAlive(){ return true;}
 