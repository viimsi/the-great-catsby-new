#pragma once

#include "Definitions.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Methods {
protected:
	Texture background_texture,
		tile_texture,
		foreground_texture;
	Sprite background,
		tiles,
		foreground;
	RectangleShape map;
	vector<vector<Vector2i>> visual_level, collision_level;
	int MAX_score;
	Clock timer;
	RenderWindow& game;
public:
	Methods(RenderWindow& window) : game(window), map(Vector2f(MAP_HEIGHT, MAP_WIDTH)) {
		MAX_score = 0;
	}
	~Methods() {}

	void create_window();
	void visual_map();
	void collision_map();
	void render_map();
};