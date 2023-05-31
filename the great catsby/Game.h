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
	Font font_name;
	bool jump_check, is_player_hurt;
	float penalty_value;
	RenderWindow game;
	int enemy_amount;
	Enemy* books;
	Texture book_texture;

	Text score_text;
	Text finished_text;
	Text leave_text;

	bool game_finished;

public:
	Game() : jump_check(false), Player(timer, jump_check), Methods(game), enemy_amount(0), is_player_hurt(false), penalty_value(2.f), game_finished(false) {
		books = new Enemy[enemy_amount + 1];
		font_name.loadFromFile("Resources/Daydream.ttf");
		book_texture.loadFromFile("Resources/book.png");
	}
	~Game() {
		delete[] books;
	}

	void text(Text& t, float pos_x, float pos_y, Color color, unsigned int size, string content);
	void spawn_text();
	void render();
	void run();
};