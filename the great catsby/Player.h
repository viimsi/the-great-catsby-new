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
	Vector2i center;
	Vector2f velocity;
	int platform_height, platform_left, platform_right;
	Texture player_texture, hurt_player_texture;
	View player_view;
	bool collision_check, &jump_check;
	Clock& timer;
	RectangleShape player;
	int total_coins;

public:
	Player(Clock& clock, bool& check) : timer(clock), jump_check(check), player_view(Vector2f(MAP_WIDTH / 2.f, MAP_HEIGHT / 2.f), Vector2f(VIEW_WIDTH, VIEW_HEIGHT)) , Methods(game) {
		player_texture.loadFromFile("Resources/player1.png");
		hurt_player_texture.loadFromFile("Resources/player2.png");

		player.setPosition(MAP_WIDTH / 2.f, MAP_HEIGHT - 66);
		player.setSize(Vector2f(player_width, player_height));
		player.setTexture(&player_texture);
		collision_check = true;
		jump_check = false;

		velocity.x = 0.f;
		velocity.y = 0.f;

		platform_height = MAP_HEIGHT - 32;
		platform_right = MAP_WIDTH;
		platform_left = 0;

		total_coins = 0;
	}

	void array_to_zero();
	void update();
	void load_collision_map();
	bool get_collision_check();
	void movement();
};

