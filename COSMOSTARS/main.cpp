#include <SFML/Graphics.hpp>

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
