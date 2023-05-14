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
public:
	Game() {}
	~Game() {}

	void render();
	void run();
};