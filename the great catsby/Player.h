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
	int bottom, left, right, top;
	float gravity;
	int platform_height, platform_left, platform_right;
	Vector2f center;
	Texture player_texture;
	View player_view;
	bool collision_check;
	Clock& timer;
	bool &jump_check;
	RectangleShape player;

public:
	Player(Clock& clock, bool& check) : timer(clock), jump_check(check), player_view(Vector2f(MAP_WIDTH / 2.f, MAP_HEIGHT / 2.f), Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)) , Methods(game){
		player_texture.loadFromFile("Resources/player.png");

		player.setPosition(MAP_WIDTH / 2.f, MAP_HEIGHT - 128);
		player.setSize(Vector2f(64, 128));
		player.setTexture(&player_texture);
	}
	~Player() {}

	void update();
	bool get_collision_check();
	void movement();
};

