#include "Asteroid.h"
#include <iostream>

Asteroid::Asteroid(float prescale):Entity(){
	explosionFrame = 0; 
	if (!(scale = prescale)) 
		setScale();

	hp = 4*scale;
	speed = 2/scale;
	reward = 12*scale;

	makeTexture("images/asteroid"+std::to_string((unsigned long long)rand()%2)+".png", scale);

	setPosition(900, rand()%(540-size.y));

	explosionTexture.loadFromFile("images/explosion.png");
	explosionSprite.setTexture(explosionTexture);
	explosionSprite.setScale(3*scale, 3*scale); 
}

MoveResult Asteroid::move(float time){
	position.x -= speed*time*500;
	sprite.setPosition(position);

	if (position.x < -96){
		hp = 0;
		return del;
	}
	return stay;
}

void Asteroid::setScale(){
	int dist = rand()%100;

	if (dist < 70)
		scale = 0.5;
	else 
		scale = 1; 
}

bool Asteroid::isAlive(){
	return hp > 0;
}

void Asteroid::getDamage(){
	hp--;
}

float Asteroid::getScale(){
	return scale;
}

int Asteroid::getReward(){
	return reward;
}

bool Asteroid::isExploded(){
	return explosionFrame >= 34;
}

Sprite Asteroid::explosion(float time){
	int x = (int)explosionFrame%5;
	int y = (int)(explosionFrame/5);
	explosionSprite.setTextureRect(IntRect(x * 96, y * 96, 96, 96));
	explosionSprite.setPosition(position.x-size.x, position.y-size.y);
	explosionFrame += time*500;

	return explosionSprite;
}
 