#include "Map.h"

Map::Map(){
	makeTexture("images/cosmos.png");
	displace = 0;
}

Move_result Map::move(float time){
	if (int(displace += time*1000) >= 960) 
		displace = 0;

	setPosition(-displace, 0);

	return stay;
}
bool Map::isAlive(){ return true;}
 