#include "Methods.h"
#include "Definitions.h"
#include "Player.h"
#include "Game.h"
#include "Enemy.h"

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

float get_random_number(int min, int max) {
	if (min < 64) min = 64;
	else if (max > MAP_WIDTH - 64) max = MAP_WIDTH - 64;

	return min + (rand() % (max - min + 1));
}

void Game::text(Text& t, float pos_x, float pos_y, Color color, unsigned int size, string content) {
	t.setFont(font_name);
	t.setString(content);
	t.setCharacterSize(size);
	t.setFillColor(color);
	t.setOutlineThickness(10);
	t.setOutlineColor(Color::Black);
	t.setPosition(pos_x, pos_y);
}

void Game::spawn_text() {
	//score text
	text(score_text, 550, 10.f, Color(252, 87, 147), 100, "0");

	//game over text
	text(finished_text, 250, 300, Color(255, 212, 37), 85, "FINISHED!");
	text(leave_text, 425, 500, Color(119, 235, 169), 60, "Leave.");
}

void Game::render() {
	game.setFramerateLimit(60);
	spawn_text();

	//žaidimo eiga
	while (game.isOpen())
	{
		//set view
		float ceiling_y = 32.f;
		float floor_y = MAP_HEIGHT - 32.f;
		float view_y = player.getPosition().y;

		if (top - 96 <= ceiling_y) {
			view_y = ceiling_y + 96;
		}
		else if (top + 64 >= floor_y) {
			view_y = floor_y - 64;
		}
		else {
			view_y = player.getPosition().y;
		}

		player_view.setCenter(VIEW_WIDTH / 2.f, view_y - 16);
		game.setView(player_view);

		//atnaujinama (update)
		game.clear(Color(123, 205, 233)); //prieš tai ėjęs frame ištrinamas
		game.draw(Methods::background);

		//load'inu map'ą
		Methods::render_map();

		//judejimas
		if(!game_finished) {
			movement();
		}

		Event ev;
		game.setKeyRepeatEnabled(false);
		while (game.pollEvent(ev)) {
			switch (ev.type) {
			case Event::Closed:
				game.close();
				break;
			case Event::KeyPressed:
				if (ev.key.code == Keyboard::Space) {
					if (get_collision_check()) {
						timer.restart();
					}
				}
				break;
			case Event::KeyReleased:
				if (ev.key.code == Keyboard::Space) {
					jump_check = false;
				}
			}
			break;
		}

		if (!game_finished) {
			float view_top_y = player_view.getCenter().y - player_view.getSize().y / 2.f;
			float player_x = get_random_number(player.getPosition().x - 32, player.getPosition().x + 32);
			int book_bottom = 0, book_top = 0, book_left = 0, book_right = 0;

			if (enemy_clock.getElapsedTime().asSeconds() >= penalty_value && player_view.getCenter().y - 64 > 60 && player_view.getCenter().y + 64 < MAP_HEIGHT - 80) {
				Vector2f position(player_x, view_top_y - 64);
				Vector2f size(32, 32);

				Enemy new_book(position, size, book_texture);

				Enemy* temp = new Enemy[enemy_amount + 1];
				for (int i = 0; i < enemy_amount; i++) {
					temp[i] = books[i];
				}
				temp[enemy_amount] = new_book;

				delete[] books;
				books = temp;
				enemy_amount++;

				enemy_clock.restart();
			}

			float book_delta_time = enemy_movement_clock.restart().asSeconds();

			for (int i = 0; i < enemy_amount; i++) {
				books[i].update(book_delta_time);
				books[i].display(game);

				book_bottom = books[i].get_bottom();
				book_top = books[i].get_top();
				book_left = books[i].get_left();
				book_right = books[i].get_right();

				if (book_bottom >= top && book_top <= bottom && book_right >= left + 10 && book_left <= right - 10) {

					if (!is_player_hurt) {
						is_player_hurt = true;
						if (total_coins > 0) {
							array_to_zero();
							total_coins--;
						}

						if (penalty_value > 0.04f) {
							penalty_value -= 0.08f;
						}

						player.setTexture(&hurt_player_texture);
						sprite_change_clock.restart();
					}
				}
			}

			if (is_player_hurt && sprite_change_clock.getElapsedTime().asSeconds() > 0.5f) {
				is_player_hurt = false;
				player.setTexture(&player_texture);
			}
		}

		if (total_coins == Player::MAX_score) {
			game_finished = true;
		}

		game.draw(player);



		game.setView(game.getDefaultView());
		game.draw(Methods::foreground);

		if(!game_finished) {
			score_text.setString(to_string(total_coins));
			game.draw(score_text);
		}
		if (game_finished) {
			game.draw(Methods::gameover);
			game.draw(finished_text);
			game.draw(leave_text);
		}

		game.display();
	}
}

void Game::run() {
	Methods::create_window();
	Methods::visual_map();
	Player::load_collision_map();
	render();
}