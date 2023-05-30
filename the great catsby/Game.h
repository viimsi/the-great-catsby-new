#pragma once
#include "Player.h"
#include "Methods.h"
#include "Enemy.h"

#include "Definitions.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Game: public Player, public Methods {
private:
	Clock timer, enemy_clock, sprite_change_clock, enemy_movement_clock;
	bool jump_check, is_player_hurt;
	float penalty_value;
	RenderWindow game;
	int enemy_amount, coin_coordinates[24][10];
	Enemy* books;
public:
	Game() : jump_check(false), Player(timer, jump_check), Methods(game), enemy_amount(0), is_player_hurt(false), penalty_value(2.f) {
		books = new Enemy[enemy_amount + 1];
	}
	~Game() {
		delete[] books;
	}

	void text();
	void render();
	void run();
};