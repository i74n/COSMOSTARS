#include "Asteroid.h"

Asteroid::Asteroid():Entity(){
	explosionFrame = 0; 
	setScale();

	hp = 4*scale;
	speed = 2/scale;
	reward = 12*scale;

	makeTexture("images/asteroid"+std::to_string((unsigned long long)rand()%2)+".png");
	sprite.setScale(scale, scale);

	position.x = 900;
	position.y = rand()%(540-size.y)+0;

	explosionTexture.loadFromFile("images/explosion.png");
	

	explosionSprite.setTexture(explosionTexture);
	explosionSprite.setPosition(position);
}

Move_result Asteroid::move(float time){
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
		scale = 0.7;
	else if (dist > 90)
		scale = 1; 
	else 
		scale = 0.3;
}

bool Asteroid::isAlive(){
	return hp > 0;
}

void Asteroid::getDamage(){
	hp--;
}

int Asteroid::getReward(){
	return reward;
}

bool Asteroid::isExploded(){
	return explosionFrame >= 34;
}

Sprite Asteroid::explosion(float time){
	int x = (int)explosionFrame%5;
	int y = explosionFrame/5;
	explosionSprite.setTextureRect(IntRect(x * 92, y * 92, 92, 92));
	explosionSprite.setPosition(position);
	explosionFrame += time*1000;

	return explosionSprite;
}
 