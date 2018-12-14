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
	
	Image map_image;//������ ���������� �� �����
	map_image.loadFromFile("images/cosmos.png");//��������� ���� �� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//������� �������� ���������
	Sprite mapSprite;//������� ������ �� �����
	mapSprite.setTexture(map);//�������� �������� ��������
	
	Clock clock; 
	
	float i = 0;

	// �������� (�����������) ����
	while (window.isOpen()){
		sf::Event event; //��������� �� ������
		while (window.pollEvent(event)) //����� �������
			if (event.type == sf::Event::Closed)
				window.close();
			
		float time = clock.getElapsedTime().asSeconds();
		if (int(i += time*1000) >= 960) 
			i = 0;

		mapSprite.setPosition(-i, 0);
		clock.restart();
		window.clear(); //������� �����
		window.display(); 
	}
	return 0;
}
