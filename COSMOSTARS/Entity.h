#pragma once
#include <string>
#include <SFML/Graphics.hpp>

enum Buff {x2, demolisher, shield};
enum MoveResult {del, make, stay};

using namespace sf;

class Entity{
protected:	
	Texture texture;
	Sprite sprite;

public:
	Vector2f position;
	Vector2u size;

	Entity();
	void makeTexture(std::string path, float scale = 1);
	void setPosition(float x, float y);
	Sprite getSprite();
	virtual bool isAlive() = 0;
	bool intersects(Entity * obj);
	virtual MoveResult move(float) = 0;

};