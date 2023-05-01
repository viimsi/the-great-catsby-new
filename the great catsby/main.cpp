#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Game.h"

int main()
{
    Game myGame;
    while(!Keyboard::isKeyPressed(Keyboard::Escape)) {
        myGame.run();
    }
}