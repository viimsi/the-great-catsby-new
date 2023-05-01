#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Game {
private:
    // Add all your variables you need, your "globals".
    sf::RenderWindow window;
    sf::Texture texture;
    sf::Sprite sprite;
    unsigned int lives;
    // ...
public:
    // This is the constructor, called whenever a 'Game' object is created.
    // Use this to setup stuff you have to set once.
    // This should only be used for things that can't fail, to always have a defined state.
    Game() {
        lives = 0;
    }

    // This is the destructor, called whenever a 'Game' object is destroyed.
    ~Game() {
    }

    // Load and run the game
    int run() {
        // Prepare everything
        window.create(sf::VideoMode(640, 480), "My SFML Game" /* ... */);

        // This should do some error checking as well and 'return' just in case.
        texture.loadFromFile("myImage.png");
        sprite.setTexture(texture);

        while (window.isOpen()) {
            // Your standard game loop here...
            // Polling events...
            sf::Event event;
            while (window.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closing:
                    window.close();
                    break;
                }
            }

            // Updating things...

            // Drawing everything...
            window.clear();
            window.draw(sprite);
            window.display();
        }
        return 0;
    }
};

int main() {
    // Create a Game object and run it
    Game myGame;
    return myGame.run();
}