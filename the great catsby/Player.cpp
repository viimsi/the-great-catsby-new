#include "Player.h"
#include "Definitions.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;

void Player::update() {
	bottom = player.getPosition().y + player.getSize().y / 2;
	left = player.getPosition().x;
	right = player.getPosition().x + player.getSize().x;
	top = player.getPosition().y;
	center.x = player.getPosition().x + 16;
	center.y = player.getPosition().y + 16;
}

void Player::movement() {
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		if (right < WINDOW_WIDTH + 2) {
			player.move(3.5f, 0);
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::A)) {
		if (left > 0) {
			player.move(-3.5f, 0);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		float nuoSuolioPr = timer.getElapsedTime().asSeconds();
		if (nuoSuolioPr < 0.2f) {
			player.move(0, -10.0f);
			jump_check = true;
		}
		else {
			jump_check = false;
		}
	}

	//gravitacijos logika
	if (bottom < platform_height && jump_check == false) {
		player.move(0, gravity_speed);
	}

	if (!collision_check) {
		platform_height = MAP_HEIGHT - 64;
		platform_right = MAP_WIDTH;
		platform_left = 0;
	}

	update();

	for (int i = 0; i < collision_level.size(); i++) {
		for (int j = 0; j < collision_level[i].size(); j++) {

			if (collision_level[i][j] == Vector2i(1, 1)) {
				int tbottom, ttop, tleft, tright; //tile objekto šonai
				tbottom = i * 64 + 64;
				ttop = i * 64;
				tright = j * 64 + 64;
				tleft = j * 64;

				if (right < tleft || left > tright || top > tbottom || bottom < ttop) {
					collision_check = false;
				}
				else if ((bottom == ttop || bottom == ttop + 1 || bottom == ttop + 2) && (right > tleft || left < tright)) { //kai top collision yra true
					platform_height = ttop;
					platform_right = tright;
					platform_left = tleft;
					collision_check = true;
				}
				else {
					collision_check = false;
				}
			}
			if (collision_level[i][j] == Vector2i(0, 0)) {
				int c_bottom, c_top, c_left, c_right; //coin objekto šonai
				c_bottom = i * 64 + 64;
				c_top = i * 64;
				c_right = j * 64 + 64;
				c_left = j * 64;

				if (center.x <= c_right && center.x >= c_left && center.y >= c_top && center.y <= c_bottom) {
					//taskai WIP
				}
			}
		}
	}

	//tikrinti ar YRA collision
	if ((bottom == platform_height || bottom == platform_height + 1 || bottom == platform_height + 2) && (right > platform_left && left < platform_right)) { //kai top collision yra true
		collision_check = true;
	}
}