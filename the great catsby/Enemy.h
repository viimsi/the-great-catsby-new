#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Definitions.h"
#include "Methods.h"
#include "Player.h"

using namespace sf;
using namespace std;

class Enemy {
private:
	Vector2f position, size;
	int bottom, top, right, left;

public:
	Enemy() {
		position = Vector2f(0, 0);
		size = Vector2f(0, 0);

		bottom = 0;
		top = 0;
		right = 0;
		left = 0;
	}
	Enemy(Vector2f position, Vector2f size) {
		this->position = position;
		this->size = size;

		bottom = 0;
		top = 0;
		right = 0;
		left = 0;
	}
	~Enemy() {}

	void update(float delta_time);
	void display(RenderWindow& game);
	int get_bottom();
	int get_top();
	int get_left();
	int get_right();
};