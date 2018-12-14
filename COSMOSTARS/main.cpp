#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

enum Buff {HP, DEATHLESS, SPEEDUP};
using namespace sf;

class Entity{
protected:	
	Texture texture;
	Sprite sprite;

public:
	Vector2f position;
	
	Entity() {}
	Entity(std::string path){
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

	virtual bool move(float) = 0;
};

class Map:public Entity{
	float displace;
public:
	Map(std::string path):Entity(path){
		displace = 0;
	}
	bool move(float time){
		if (int(displace += time*1000) >= 960) 
			displace = 0;
		setPosition(-displace, 0);

		return false;
	}
};

class Asteroid:public Entity{
	int hp;
	float speed;
public:
	Asteroid(std::string path):Entity(path){
		speed = rand()%10+1;
		position.x = 900;
		position.y = rand()%540+0;
		sprite.setPosition(position);
	}

	bool move(float time){
		position.x -= speed*time*500;
		sprite.setPosition(position);

		return (position.x < -96) ? true : false;
	}
};

class Bonus:public Entity{
public:
	Buff buff;
	Bonus(std::string path, Buff buff):Entity(path), buff(buff){}
	bool move(float time){
		return false;
	}
};

class Player:public Entity{
	int hp;
public:
	Player(std::string path):Entity(path){
		position.x = 0;
		position.y = 270;
	}
	bool move(float time){
		if (position.y > 0 && Keyboard::isKeyPressed(Keyboard::Up))
			position.y -= 0.5*time*10000;
		else if (position.y < 444 && Keyboard::isKeyPressed(Keyboard::Down)) 
			position.y += 0.5*time*10000;
		else if (Keyboard::isKeyPressed(Keyboard::Space))
			this->attack();
		sprite.setPosition(position);

		return false;
	}

	void attack(){
		std::cout << "ATTACK";
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

	static Entity* arr[] = {new Map("images/cosmos.png"), new Player("images/ship.png")};
	std::vector<Entity*> entities(arr, arr + sizeof(arr)/sizeof(arr[0]));

	for(int j = 0; j <= rand()%4; j++)
		entities.push_back(new Asteroid("images/asteroid.png"));

	Clock clock; 

	while (window.isOpen()){
		Event event; //ѕеременна¤ дл¤ событи¤
		while (window.pollEvent(event)) //ќпрос событий
			if (event.type == Event::Closed)
				window.close();
		
		window.clear();

		float time = clock.getElapsedTime().asSeconds();

		for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ){
			window.draw((*it)->getSprite());
			if ((*it)->move(time)) 
				entities.erase(it);
			else
				++it;
			std::cout << entities.size();
		}

		window.display(); 
		clock.restart();
	}
	
	return 0;
}
