#include "Player.h"
#include "Definitions.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;

void Player::update() {
	bottom = player.getPosition().y + player.getSize().y / 2.f;
	left = player.getPosition().x;
	right = player.getPosition().x + player.getSize().x;
	top = player.getPosition().y;
	center.x = player.getPosition().x + 32;
	center.y = player.getPosition().y + 32;
}

void Player::load_collision_map() {
	collision_map();
}

bool Player::get_collision_check() {
	return collision_check;
}

void Player::movement() {

	velocity.x *= 0.05f;

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		if (right < VIEW_WIDTH + 2) {
			velocity.x += 3.5f;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::A)) {
		if (left > 0) {
			velocity.x -= 3.5f;
		}
	}

	player.move(velocity);

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		float since_jump_start = timer.getElapsedTime().asSeconds();
		if (since_jump_start < 0.15f) {
			player.move(0, -12.0f);
			jump_check = true;
		}
		else {
			jump_check = false;
		}
	}

	//gravitacijos logika
	if (bottom < platform_height && !jump_check) {
		player.move(0, gravity_speed);
	}

	if (!collision_check) {
		platform_height = MAP_HEIGHT - 32;
		platform_right = MAP_WIDTH;
		platform_left = 0;
	}

	update();


	for (int i = 0; i < collision_level.size(); i++) {
		for (int j = 0; j < collision_level[i].size(); j++) {

			if (collision_level[i][j] == Vector2i(1, 1)) {
				int t_bottom, t_top, t_left, t_right; //tile objekto šonai
				t_bottom = i * 32 + 32;
				t_top = i * 32;
				t_right = j * 32 + 32;
				t_left = j * 32;

				if (right < t_left || left > t_right || top > t_bottom || bottom < t_top) {
					collision_check = false;
				}
				else if ((bottom == t_top || bottom == t_top + 1 || bottom == t_top + 2) && (right > t_left || left < t_right)) { //kai top collision yra true
					platform_height = t_top;
					platform_right = t_right;
					platform_left = t_left;
					collision_check = true;
				}
				else {
					collision_check = false;
				}
			}
			if (collision_level[i][j] == Vector2i(0, 0)) {
				int c_bottom, c_top, c_left, c_right; //coin objekto šonai
				c_bottom = i * 32 + 32;
				c_top = i * 32;
				c_right = j * 32 + 32;
				c_left = j * 32;

				if (center.x <= c_right && center.x >= c_left && center.y >= c_top && center.y <= c_bottom) {
					//taskai WIP
				}
			}
		}
	}

	if ((bottom == platform_height || bottom == platform_height + 1 || bottom == platform_height + 2) && (right > platform_left && left < platform_right)) { //kai top collision yra true
		collision_check = true;
	}
}