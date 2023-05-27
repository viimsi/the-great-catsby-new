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
	game.setFramerateLimit(60);

	//žaidimo eiga
	while (game.isOpen()) 
	{
		//set view
		player_view.setCenter(WINDOW_WIDTH / 2.f, player.getPosition().y);
		game.setView(player_view);

		//atnaujinama (update)
		game.clear(Color(123, 205, 233)); //prieš tai ėjęs frame ištrinamas
		game.draw(Methods::background);

		//load'inu map'ą
		Methods::render_map();


		Event ev;
		game.setKeyRepeatEnabled(false);
		while (game.pollEvent(ev)) {
			switch (ev.type) {
			case Event::Closed:
				game.close();
				break;
			case Event::KeyPressed:
				if (ev.key.code == Keyboard::Space) {
					cout << "space" << endl;
				}
			}
		}

		float delta_time = timer.restart().asSeconds();

		//judejimas
		movement(delta_time);

		game.draw(player);

		game.display();
	}
}

void Game::run() {
	Methods::create_window();
	Methods::visual_map();
	Player::load_collision_level();
	render();
}