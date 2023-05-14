#include "Methods.h"
#include "Definitions.h"
#include "Player.h"
#include "Game.h"

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

void Game::render() {
	Methods::game.setFramerateLimit(60);

	//žaidimo eiga
	while (Methods::game.isOpen()) 
	{
		//set view
		player_view.setCenter(WINDOW_WIDTH / 2.f, Player::player.getPosition().y);
		Methods::game.setView(player_view);

		//atnaujinama (update)
		Methods::game.clear(Color(123, 205, 233)); //prieš tai ėjęs frame ištrinamas
		Methods::game.draw(Methods::background);

		//load'inu map'ą
		Methods::render_map();

		//judejimas
		Player::movement();

		Event ev;
		Methods::game.setKeyRepeatEnabled(false);
		while (Methods::game.pollEvent(ev)) {
			switch (ev.type) {
			case Event::Closed:
				Methods::game.close();
				break;
			case Event::KeyPressed:
				if (ev.key.code == Keyboard::Space) {
					if (Methods::collision_check) {
						Methods::timer.restart();
					}
				}
				break;
			case Event::KeyReleased:
				if (ev.key.code == Keyboard::Space) {
					Methods::jump_check = false;
				}
			}
			break;
			}

		Methods::game.draw(Player::player);

		Methods::game.display();
	}
}

void Game::run() {
	Methods::load_map();
	render();
}