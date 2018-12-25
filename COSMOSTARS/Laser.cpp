#include "Laser.h"
#include "Player.h"

Laser::Laser(Player * player){
	alive = true;
	makeTexture("images/bullet.png");

	setPosition(player->position.x + player->size.x,
		player->position.y + player->size.y/2 - this->size.y/2
	);
}

MoveResult Laser::move(float time){
	position.x += 50*time*500;
	sprite.setPosition(position);

	return (position.x > 960) ? del : stay;
}

bool Laser::isAlive(){return alive;}
void Laser::hit(){alive = false;}
