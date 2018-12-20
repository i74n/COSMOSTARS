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
	}

	Move_result move(float time){
		position.x -= speed*time*500;
		sprite.setPosition(position);

		return (position.x < -96) ? del : stay;
	}

	std::string randSize(){
		std::string size;
		int dist = rand()%100;
		if (dist < 70) size = "M";
		else if (dist >90) 	size = "L"; 
		else size = "S";
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

	static Entity* arr[] = {new Map(), new Player()};
	std::vector<Entity*> entities(arr, arr + sizeof(arr)/sizeof(arr[0]));

	Clock clock; 
	float bullet_cooldown = 0, asteroid_cooldown = 0;

	while (window.isOpen()){
		bool flag = false;
		Event event; //ѕеременна¤ дл¤ событи¤
		while (window.pollEvent(event)) //ќпрос событий
			if (event.type == Event::Closed)
				window.close();

		window.clear();

		float time = clock.getElapsedTime().asSeconds();
		  
		for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it){
			window.draw((*it)->getSprite());

			switch ((*it)->move(time)){
				case del: 
					entities.erase(it--);
					break;
				case make: 
					flag = true;
					break;
				case stay: 
					break;
			}
		}

		bullet_cooldown += time;
		if (flag && (bullet_cooldown > 0.01)){
			entities.push_back(new Laser((entities[1])->position));
			bullet_cooldown = 0;
		}

		asteroid_cooldown += time;
		if (asteroid_cooldown > 0.1){
			entities.push_back(new Asteroid());
			asteroid_cooldown = 0;
		}
		
		window.display(); 
		clock.restart();
	}

	return 0;
}
