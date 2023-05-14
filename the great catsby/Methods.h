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
	RenderWindow game;
	vector<vector<Vector2i>> visual_level, collision_level;
	int MAX_score;
	Clock timer;
	bool jump_check, collision_check;

public:
	Methods() : map(Vector2f(MAP_HEIGHT, MAP_WIDTH)) {
		MAX_score = 0;
		game.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 64), "The Great Catsby", Style::Titlebar | Style::Close);
		cout << "done";
	}
	~Methods() {}

	void visual_map();
	void collision_map();
	void load_map();
	void render_map();
};