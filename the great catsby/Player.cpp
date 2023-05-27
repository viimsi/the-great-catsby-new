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
	center.x = player.getPosition().x + 32;
	center.y = player.getPosition().y + 32;
}

void Player::get_collision_check() {

	for (int i = 0; i < collision_level.size(); i++) {
		for (int j = 0; j < collision_level[i].size(); j++) {

			if (collision_level[i][j] == Vector2i(1, 1)) {
				int t_bottom, t_top, t_left, t_right; //tile objekto šonai
				t_bottom = i * 64 + 64;
				t_top = i * 64;
				t_right = j * 64 + 64;
				t_left = j * 64;

				
				if (right < t_left || left > t_right || top > t_bottom || bottom < t_top) {

					collision_check = false;
					is_standing = false;
				}
				else if ((bottom == t_top || bottom == t_top + 1 || bottom == t_top + 2) && (right > t_left || left < t_right)) { //kai top collision yra true
					platform_height = t_top;
					platform_right = t_right;
					platform_left = t_left;
					collision_check = true;
					is_standing = true;
				}
				else {
					collision_check = false;
					is_standing = false;
				}
			}
		}
	}
}

void Player::load_collision_level() {
	collision_map();
}

void Player::movement(float delta_time) {

	update();
	get_collision_check();

	velocity.x = 0.f;

	cout << "stnd | " << is_standing << " col | " << collision_check << " jump | " << jump_check << " plat | " << platform_height << " bot | " << bottom << endl;

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		if (right < WINDOW_WIDTH + 2) {
			velocity.x += speed;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::A)) {
		if (left > 0) {
			velocity.x -= speed;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Space) && !jump_check) {
		jump_check = true;
		is_standing = false;
		velocity.y = -sqrtf(2.f * gravity_speed * jump_height);
	}
	
	
	if (!collision_check) {
		platform_height = MAP_HEIGHT - 64;
		platform_right = MAP_WIDTH;
		platform_left = 0;
	}

	update();

	

	//tikrinti ar YRA collision
	if ((bottom == platform_height || bottom == platform_height + 1 || bottom == platform_height + 2) && (right > platform_left && left < platform_right)) {
		jump_check = false;
		is_standing = true;
		velocity.y = 0.0f;
	}

	if (!jump_check && !collision_check && !is_standing) {
		velocity.y += gravity_speed * delta_time;
	}

	player.move(velocity * delta_time);
}