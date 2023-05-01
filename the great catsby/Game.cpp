#include "Game.h"
#include "Definitions.h"

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

void Game::visual_map() {
	//ruošiama nuskaityti tilemap'ą
	ifstream fd("Resources/level1.txt");
	vector<Vector2i> tempLevel;
	visual_level.clear();

	//tilemap'o nuskaitymas
	if (fd.is_open()) {
		//nuskaitomas tilemap su tekstūromis
		string tilePav;
		fd >> tilePav; //nuskaitoma 1-oji level1.txt failo eilutė
		tile_texture.loadFromFile(tilePav); //nuskaitoma tekstūra iš .png failo
		tiles.setTexture(tile_texture); //tiles pritaikoma tekstūra

		while (!fd.eof()) {
			string koor;
			fd >> koor; //nuskaitoma koordinate
			char x = koor[0], y = koor[2]; //is nuskaitytos koordinates bus gaunamos atskiros x ir y reikšmės

			if (!isdigit(x) || !isdigit(y)) {
				tempLevel.push_back(Vector2i(-1, -1)); //kadangi tilemap neturi neigiamų reikšmių, tai šiai koordinatei nebus priskiriama tekstūra
			}
			else {
				tempLevel.push_back(Vector2i(x - '0', y - '0')); //taip bus gaunama atitinkama tekstūra
			}

			if (fd.peek() == '\n') { //tikrinama ar tai eilutės pabaiga
				visual_level.push_back(tempLevel);
				tempLevel.clear();
			}
		}

		visual_level.push_back(tempLevel);
	}

	fd.close();
}
void Game::collision_map() {
	ifstream fd("Resources/col1.txt");
	vector<Vector2i> tempLevel;
	collision_level.clear();

	while (!fd.eof()) {
		string koor;
		fd >> koor; //nuskaitoma koordinate
		char x = koor[0], y = koor[2]; //is nuskaitytos koordinates bus gaunamos atskiros x ir y reikšmės

		if (!isdigit(x) || !isdigit(y)) {
			tempLevel.push_back(Vector2i(-1, -1)); //-1,-1 koordinate reiškia kad tai NĖRA objektas
		}
		else if (x == '1' && y == '1') {
			tempLevel.push_back(Vector2i(1, 1)); //1,1 koordinatė reiškia kad tai yra COLLISION objektas
		}
		else if (x == '0' && y == '0') {
			tempLevel.push_back(Vector2i(0, 0)); //1,1 koordinatė reiškia kad tai yra COIN, bet ne collision objektas
			MAX_score++;
		}

		if (fd.peek() == '\n') { //tikrinama ar tai eilutės pabaiga
			collision_level.push_back(tempLevel);
			tempLevel.clear();
		}
	}

	collision_level.push_back(tempLevel);
}
void Game::load_map() {
	visual_map();
	collision_map();
}
void Game::render_map() {
	for (int i = 0; i < visual_level.size(); i++) {
		for (int j = 0; j < visual_level[i].size(); j++) {
			if (visual_level[i][j].x != -1 && visual_level[i][j].y != -1) {
				tiles.setPosition(j * 64, i * 64);
				tiles.setTextureRect(IntRect(visual_level[i][j].x * 64, visual_level[i][j].y * 64, 64, 64));
				game.draw(tiles);
			}
		}
	}
}
void Game::render_window() {
	game.setFramerateLimit(60);

	//žaidimo eiga
	while (game.isOpen()) {
		//atnaujinama (update)
		game.clear(Color(123, 205, 233)); //prieš tai ėjęs frame ištrinamas

		game.draw(background);

		//load'inu map'ą
		render_map();

		Event ev;
		game.setKeyRepeatEnabled(false);
		while (game.pollEvent(ev)) {
			switch (ev.type) {
			case Event::Closed:
				game.close();
				break;
			case Event::KeyPressed:
				if (ev.key.code == Keyboard::Space) {
					cout << "Up";
				}
				break;
			}

			game.display();
		}
	}
}

void Game::run() {
	load_map();
	render_window();
}