#pragma once
#include "Player.h"
#include "Methods.h"

#include "Definitions.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Game: public Player, public Methods {
private:
	Clock timer;
	bool jump_check;
	RenderWindow game;
public:
	Game() : jump_check(false), Player(timer, jump_check), Methods(game) {}
	~Game() {}

	void render();
	void run();
};