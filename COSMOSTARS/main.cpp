#include <list>
#include <cstdlib>
#include <ctime>

#include "Main.h"

int main(){
	srand(time(NULL));
	VideoMode desktop = VideoMode::getDesktopMode();
	RenderWindow window(VideoMode(960, 540, desktop.bitsPerPixel), "Cosmo");

	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 35);//создаем объект текст
	text.setColor(Color::Red);//покрасили текст в красный	


	float FRAME = 0; 
	Player* player = new Player;
	Map* map = new Map;

	std::list<Asteroid*> IFO;
	std::list<Laser*> shots;

	Clock clock; 
	float shot_cooldown = 0, asteroid_cooldown = 0;

	while (window.isOpen() && player->isAlive()){
		bool flag = false;
		Event event;
		while (window.pollEvent(event)) 
			if (event.type == Event::Closed)
				window.close();

		window.clear();

		float time = clock.getElapsedTime().asSeconds();	

		map->move(time);

		window.draw(map->getSprite());
		window.draw(player->getSprite());

		if (player->move(time) == make)
			shots.push_back(new Laser(player));

		for(std::list<Laser*>::iterator shot = shots.begin(); shot != shots.end();){
			window.draw((*shot)->getSprite());

			for(std::list<Asteroid*>::iterator asteroid = IFO.begin(); asteroid != IFO.end(); asteroid++){
				if ((*shot)->intersects(*asteroid)){
					(*asteroid)->getDamage();
					(*shot)->hit();
				}
			}
			if ((*shot)->move(time) == del || !(*shot)->isAlive())
				shot = shots.erase(shot);
			else shot++;

		}

		asteroid_cooldown += time;
		if (asteroid_cooldown > 0.2){
			IFO.push_back(new Asteroid());
			asteroid_cooldown = 0;
		}

		for(std::list<Asteroid*>::iterator asteroid = IFO.begin(); asteroid != IFO.end();){
			if (!(*asteroid)->isAlive() && !(*asteroid)->isExploded()) {
				window.draw((*asteroid)->explosion(time));
				asteroid++;
			}else if ((*asteroid)->move(time) == del){
				player->setScores(-(*asteroid)->getReward());
				asteroid = IFO.erase(asteroid);	
			}else if ((*asteroid)->isExploded()) {
				player->setScores((*asteroid)->getReward());
				asteroid = IFO.erase(asteroid);	
			}else if (player->intersects(*asteroid)){
				player->setScores(-2*(*asteroid)->getReward());
				(*asteroid) -> hp = 0;	
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
