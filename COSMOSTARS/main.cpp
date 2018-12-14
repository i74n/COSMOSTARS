#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

enum Buff {HP, DEATHLESS, SPEEDUP};
using namespace sf;

class Entity{
protected:	
	Texture texture;
public:
	Sprite sprite;
	
	Entity() {}
	Entity(std::string path){
		texture.loadFromFile(path); // загружаем изображение игрока
		sprite.setTexture(texture);
	}

	Sprite getSprite() {
		return sprite;
	}
	void setPosition(float x, float y) {
		sprite.setPosition(x, y);
	}
};

class Asteroid:public Entity{
	int hp;
public:
	Asteroid(std::string path):Entity(path){}
	void move(){}
};



class Bonus:public Entity{
public:
	Buff buff;
	Bonus(std::string path, Buff buff):Entity(path), buff(buff){}
	void move(){}
};

class Player:public Entity{
	int hp;
public:
	Player(std::string path):Entity(path){}
	void move(){
		Vector2f position = sprite.getPosition();
		if (position.y > 0 && Keyboard::isKeyPressed(Keyboard::Up))
			sprite.move(0, -0.5); 
		else if (position.y < 444 && Keyboard::isKeyPressed(Keyboard::Down)) 
			sprite.move(0, 0.5);
		else if (Keyboard::isKeyPressed(Keyboard::Space))
			this->attack();
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
	VideoMode desktop = VideoMode::getDesktopMode();
	RenderWindow window(VideoMode(960, 540, desktop.bitsPerPixel), "Cosmo");

	Player player("images/ship.png");
	Entity map("images/cosmos.png");
	Clock clock; 

	player.setPosition(0, 270);//

	float i = 0;

	// ќсновной (бесконечный) цикл
	while (window.isOpen()){
		Event event; //ѕеременна¤ дл¤ событи¤
		while (window.pollEvent(event)) //ќпрос событий
			if (event.type == Event::Closed)
				window.close();

		float time = clock.getElapsedTime().asSeconds();
		if (int(i += time*1000) >= 960) 
			i = 0;

		map.setPosition(-i, 0);
		player.move();
		
		window.clear();
		window.draw(map.sprite);
		window.draw(player.sprite);
		window.display(); 
		clock.restart();
	}

	return 0;
}
