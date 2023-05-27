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
	int platform_height, platform_left, platform_right;
	float jump_height, speed;
	Vector2f center, velocity;
	Texture player_texture;
	View player_view;
	bool collision_check, & jump_check, is_standing;
	Clock& timer;
	RectangleShape player;

public:
	Player(Clock& clock, bool& check) : timer(clock), jump_check(check), player_view(Vector2f(MAP_WIDTH / 2.f, MAP_HEIGHT / 2.f), Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)) , Methods(game){
		player_texture.loadFromFile("Resources/player.png");

		player.setPosition(MAP_WIDTH / 2.f, MAP_HEIGHT - 128);
		player.setSize(Vector2f(64, 128));
		player.setTexture(&player_texture);
		velocity.x = 0.f;
		velocity.y = 0.f;
		jump_height = 150.f;
		speed = 150.f;
		collision_check = true;
		is_standing = true;
		jump_check = false;

		platform_height = MAP_HEIGHT - 64;
		platform_right = MAP_WIDTH;
		platform_left = 0;
	}
	~Player() {}

	void update();
	void get_collision_check();
	void load_collision_level();
	void movement(float delta_time);
};

