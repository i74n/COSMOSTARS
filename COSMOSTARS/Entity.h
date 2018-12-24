#pragma once
#include <string>
#include <SFML/Graphics.hpp>

enum Move_result {del, make, stay};

using namespace sf;

class Entity{
protected:	
	Texture texture;
	Sprite sprite;

public:
	Vector2f position;
	Vector2u size;

	Entity();
	void makeTexture(std::string path);
	void setPosition(float x, float y);
	Sprite getSprite();
	virtual bool isAlive() = 0;
	bool intersects(Entity * obj);
	virtual Move_result move(float) = 0;

};