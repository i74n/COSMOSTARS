#include "Player.h"
#include <sstream>

Player::Player(){
	position.x = 0;
	position.y = 270;
	scores = 100;
	shot_cooldown = 0;
	makeTexture("images/ship.png");
}

Move_result Player::move(float time){
	shot_cooldown += time;

	if (position.y > 0 && Keyboard::isKeyPressed(Keyboard::Up))
		position.y -= 0.5*time*10000;
	else if (position.y + size.y < 540 && Keyboard::isKeyPressed(Keyboard::Down)) 
		position.y += 0.5*time*10000;
	else if (Keyboard::isKeyPressed(Keyboard::Space) && shot_cooldown > 0.05){
		shot_cooldown = 0;
		return make;
	}
	sprite.setPosition(position);

	return stay;
}

void Player::get_buff(Bonus bonus){
	switch (bonus.buff){
	case HP: 
		break;
	case DEATHLESS: 
		break;
	case SPEEDUP: 
		break;
	}
}

bool Player::isAlive(){return scores>0;}

std::string Player::getScores(){
	std::stringstream ss;
	ss << scores;
	return ss.str();
}

void Player::setScores(int crement){
	scores += crement;
}
