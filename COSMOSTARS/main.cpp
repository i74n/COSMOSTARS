#include <list>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Main.h"

int main(){
	srand(time(NULL));
	VideoMode desktop = VideoMode::getDesktopMode();
	RenderWindow window(VideoMode(960, 540, desktop.bitsPerPixel), "COSMOSTARS");


	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 35);//создаем объект текст
	text.setColor(Color::Red);//покрасили текст в красный	

	Player* player = new Player;
	Map* map = new Map;

	std::list<Asteroid*> asteroids;
	std::list<Laser*> lasers;
	std::list<Bonus*> bonuses;

	Clock clock; 
	float asteroid_cooldown = 0;

	while (window.isOpen() && player->isAlive()){
		
		Event event;
		while (window.pollEvent(event)) 
			if (event.type == Event::Closed)
				window.close();

		window.clear();

		float time = clock.getElapsedTime().asSeconds()*3;	

		map->move(time);

		window.draw(map->getSprite());
		window.draw(player->getSprite());

		if (player->move(time) == make)
			lasers.push_back(new Laser(player));

		for(auto bonus = bonuses.begin(); bonus != bonuses.end();){
			window.draw((*bonus)->getSprite());
			if ((*bonus)->move(time) == del || !(*bonus)->isAlive())
				bonus = bonuses.erase(bonus);
			else if (player->intersects(*bonus)){
				player->setBuff((*bonus)->getBuff());
				bonus = bonuses.erase(bonus);
			}else bonus++;
		}

		for(auto laser = lasers.begin(); laser != lasers.end();){
			window.draw((*laser)->getSprite());

			for(auto asteroid = asteroids.begin(); asteroid != asteroids.end(); asteroid++){
				if ((*laser)->intersects(*asteroid)){
					(*asteroid)->getDamage();
					(*laser)->hit();
				}
			}
			if ((*laser)->move(time) == del || !(*laser)->isAlive())
				laser = lasers.erase(laser);
			else laser++;
		}

		asteroid_cooldown += time;
		if (asteroid_cooldown > 0.2){
			asteroids.push_back(new Asteroid());
			asteroid_cooldown = 0;
		}

		for(auto asteroid = asteroids.begin(); asteroid != asteroids.end();){
			if (!(*asteroid)->isAlive() && !(*asteroid)->isExploded()) {
				window.draw((*asteroid)->explosion(time));
				asteroid++;
			}else if ((*asteroid)->isExploded()) {
				player->setScores((*asteroid)->getReward());
				if (!(*asteroid)->isAlive() && (*asteroid)->getScale() == 0.25) 
					bonuses.push_back(new Bonus((*asteroid)->position));
				asteroid = asteroids.erase(asteroid);	
			}else if ((*asteroid)->move(time) == del){
				player->setScores(-(*asteroid)->getReward());
				asteroid = asteroids.erase(asteroid);	
			}else if (player->intersects(*asteroid)){
				player->setScores(-2*(*asteroid)->getReward());
				(*asteroid) -> hp = 0;	
				asteroid++;
			}else{
				window.draw((*asteroid)->getSprite());
				asteroid++;
			}
		}

		text.setString("SCORES: " + player->getScores());
		text.setPosition(390, 0);
		window.draw(text);//

		window.display(); 
		clock.restart();
	}

	return 0;
}
