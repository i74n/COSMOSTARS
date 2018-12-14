#include <SFML/Graphics.hpp>

class Entity{
protected:	
	Texture texture;
	Sprite sprite;
public:
	Entity(std::string path){}

	Sprite getSprite() {}
	void setPosition(float x, float y) {}
};

class Player:public Entity{
	int hp;
public:
	Player(std::string path):Entity(path){}
	void move(){}
	void attack(){}
};

int main(){
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(960, 540, desktop.bitsPerPixel), "Cosmo");

	// ќсновной (бесконечный) цикл
	while (window.isOpen()){
		sf::Event event; //ѕеременна¤ дл¤ событи¤
		while (window.pollEvent(event)) //ќпрос событий
			if (event.type == sf::Event::Closed)
				window.close();

		window.clear(); //ќчищаем экран
		window.display(); 
	}
	return 0;
}
