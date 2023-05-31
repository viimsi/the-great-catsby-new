#include "Enemy.h"
#include "Definitions.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;

void Enemy::update(float delta_time) {
	position.y += 350.f * delta_time;
}
void Enemy::display(RenderWindow &game) {
	RectangleShape book(size);
	book.setPosition(position);

	bottom = book.getPosition().y + book.getSize().y;
	top = book.getPosition().y;
	right = book.getPosition().x + book.getSize().x;
	left = book.getPosition().x;

	book.setTexture(&texture);
	game.draw(book);
}
int Enemy::get_bottom() {
	return bottom;
}
int Enemy::get_top() {
	return top;
}
int Enemy::get_left() {
	return left;
}
int Enemy::get_right() {
	return right;
}