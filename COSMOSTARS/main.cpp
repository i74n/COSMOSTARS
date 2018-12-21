#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

enum Buff {HP, DEATHLESS, SPEEDUP};
enum Move_result {del, make, stay};
using namespace sf;

class Entity{
protected:	
	Texture texture;
	Sprite sprite;

public:
	Vector2f position;
	int width, height;

	Entity() {}

	void makeTexture(std::string path){
		texture.loadFromFile(path); // загружаем изображение игрока
		sprite.setTexture(texture);
	}

	void setPosition(float x, float y){
		position.x = x;
		position.y = y;
		sprite.setPosition(position);
	}

	Sprite getSprite(){
		return sprite;
	}

	virtual Move_result move(float) = 0;

	void getSize(){
		Vector2u size = texture.getSize();
		width = size.x;
		height = size.y;
	}
};

class Map:public Entity{
	float displace;
public:
	Map(){
		makeTexture("images/cosmos.png");
		displace = 0;
	}

	Move_result move(float time){
		if (int(displace += time*1000) >= 960) 
			displace = 0;

		setPosition(-displace, 0);

		return stay;
	}
};

class Asteroid:public Entity{
	int hp;
	float speed;
public:
	Asteroid(){
		std::string size = randSize();

		if (size == "M"){
			hp = 3;
			speed = 6;
		}
		else if (size == "L"){
			hp = 5;
			speed = 2;
		}
		else{
			hp = 1;
			speed = 10;
		}

		position.x = 900;
		position.y = rand()%540+0;

		makeTexture("images/asteroid_"+size+".png");
		getSize();
	}

	Move_result move(float time){
		position.x -= speed*time*500;
		sprite.setPosition(position);

		return (position.x < -96) ? del : stay;
	}

	std::string randSize(){
		std::string size;

		int dist = rand()%100;

		if (dist < 70)
			size = "M";
		else if (dist > 90)
			size = "L"; 
		else 
			size = "S";

		return size;
	}
};

class Bonus:public Entity{
public:
	Buff buff;
	Bonus(std::string path, Buff buff):buff(buff){

		makeTexture(path);
	}

	Move_result move(float time){
		return stay;
	}
};

class Laser:public Entity{
public:
	Laser(Vector2f player_position){
		position = player_position;
		position.x += 96;
		position.y += 37;

		makeTexture("images/bullet.png");
		getSize();
	}

	Move_result move(float time){
		position.x += 50*time*500;
		sprite.setPosition(position);

		return (position.x > 960) ? del : stay;
	}
};

class Player:public Entity{
	int hp;
public:
	Player(){
		position.x = 0;
		position.y = 270;

		makeTexture("images/ship.png");
		getSize();
	}

	Move_result move(float time){
		if (position.y > 0 && Keyboard::isKeyPressed(Keyboard::Up))
			position.y -= 0.5*time*10000;
		else if (position.y < 444 && Keyboard::isKeyPressed(Keyboard::Down)) 
			position.y += 0.5*time*10000;
		else if (Keyboard::isKeyPressed(Keyboard::Space))
			return make;
		sprite.setPosition(position);

		return stay;
	}

	void get_buff(Bonus bonus){
		switch (bonus.buff){
		case HP: 
			break;
		case DEATHLESS: 
			break;
		case SPEEDUP: 
			break;
		}
	}
};

int main(){
	srand(time(NULL));
	VideoMode desktop = VideoMode::getDesktopMode();
	RenderWindow window(VideoMode(960, 540, desktop.bitsPerPixel), "Cosmo");

	Player* player = new Player;
	Map* map = new Map;

	std::vector<Entity*> IFO, shots;

	Clock clock; 
	float shot_cooldown = 0, asteroid_cooldown = 0;

	while (window.isOpen()){
		bool flag = false;
		Event event; //ѕеременна¤ дл¤ событи¤
		while (window.pollEvent(event)) //ќпрос событий
			if (event.type == Event::Closed)
				window.close();

		window.clear();

		float time = clock.getElapsedTime().asSeconds();	

		map->move(time);
		
		window.draw(map->getSprite());
		window.draw(player->getSprite());
			

		asteroid_cooldown += time;
		if (asteroid_cooldown > 0.01){
			IFO.push_back(new Asteroid());
			asteroid_cooldown = 0;
		}

		for(std::vector<Entity*>::iterator it = IFO.begin(); it != IFO.end();){
			window.draw((*it)->getSprite());

			if ((*it)->move(time) == del)
					it = IFO.erase(it);
			else it++;
		}

		shot_cooldown += time;
		if ((player->move(time) == make) && (shot_cooldown > 0.01)){
			shots.push_back(new Laser(player->position));
			shot_cooldown = 0;
		}

		for(std::vector<Entity*>::iterator it = shots.begin(); it != shots.end();){
			window.draw((*it)->getSprite());

			if ((*it)->move(time) == del)
					it = shots.erase(it);
			else it++;

		}
		
		window.display(); 
		clock.restart();
	}

	return 0;
}
