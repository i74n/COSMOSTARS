#include "Entity.h"

Entity::Entity() {}

void Entity::makeTexture(std::string path){
	texture.loadFromFile(path); // загружаем изображение игрока
	sprite.setTexture(texture);
	size = texture.getSize();
}

void Entity::setPosition(float x, float y){
	position.x = x;
	position.y = y;
	sprite.setPosition(position);
}

Sprite Entity::getSprite(){
	return sprite;
}

bool Entity::intersects(Entity * obj){
	FloatRect thisRect = this->getSprite().getGlobalBounds();
	FloatRect objRect = obj->getSprite().getGlobalBounds();
	return thisRect.intersects(objRect);		 
}
 