#include "Methods.h"
#include "Definitions.h"
#include "Player.h"

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

void Methods::create_window() {
	game.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 64), "The Great Catsby", Style::Titlebar | Style::Close);
}
void Methods::visual_map() {
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
void Methods::collision_map() {
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
			tempLevel.push_back(Vector2i(0, 0)); //0, 0 koordinatė reiškia kad tai yra COIN, bet ne collision objektas
			MAX_score++;
		}

		if (fd.peek() == '\n') { //tikrinama ar tai eilutės pabaiga
			collision_level.push_back(tempLevel);
			tempLevel.clear();
		}
	}

	collision_level.push_back(tempLevel);
}
void Methods::render_map() {
	background_texture.loadFromFile("Resources/background.png");
	background.setTexture(background_texture);
	background.setScale(Vector2f(2, 2));

	for (int i = 0; i < visual_level.size(); i++) {
		for (int j = 0; j < visual_level[i].size(); j++) {
			if (visual_level[i][j].x != -1 && visual_level[i][j].y != -1) {
				tiles.setPosition(j * 64, i * 64);
				tiles.setTextureRect(IntRect(visual_level[i][j].x * 32, visual_level[i][j].y * 32, 32, 32));
				tiles.setScale(Vector2f(2, 2));
				game.draw(tiles);
			}
		}
	}
}