#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Definitions.h"
#include "Methods.h"

using namespace sf;
using namespace std;

class Player: public Methods {
protected:
	float bottom, left, right, top, gravity;
	int platform_height, platform_left, platform_right;
	Vector2f center;
	Texture player_texture;
	View player_view;
	bool collision_check, jump_check;

public:
	RectangleShape player;

	Player() : player_view(Vector2f(MAP_WIDTH / 2.f, MAP_HEIGHT / 2.f), Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)) {
		player_texture.loadFromFile("Resources/player.png");

		player.setPosition(MAP_WIDTH / 2.f, MAP_HEIGHT - 132);
		player.setSize(Vector2f(64, 128));
		player.setTexture(&player_texture);
	}
	~Player() {}

	void update();
	void movement();
};

