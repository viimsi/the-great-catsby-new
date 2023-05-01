#pragma once

#include "Definitions.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Game {
private:
	Texture background_texture,
		tile_texture,
		foreground_texture;
	Sprite background,
		tiles,
		foreground;
	RectangleShape map;
	RenderWindow game;
	vector<vector<Vector2i>> visual_level, collision_level;
	int MAX_score;

public:
	Game() {
		map.setSize(Vector2f(MAP_HEIGHT, MAP_WIDTH));
		MAX_score = 0;
		game.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "The Great Catsby", Style::Titlebar | Style::Close);
	}
	~Game() {}

	void render_window();
	void visual_map();
	void collision_map();
	void load_map();
	void render_map();

	void run();
};