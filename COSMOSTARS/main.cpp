#include <SFML/Graphics.hpp>

int main(){
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(960, 540, desktop.bitsPerPixel), "Cosmo");

	// �������� (�����������) ����
	while (window.isOpen()){
		sf::Event event; //��������� �� ������
		while (window.pollEvent(event)) //����� �������
			if (event.type == sf::Event::Closed)
				window.close();

		window.clear(); //������� �����
		window.display(); 
	}
	return 0;
}
