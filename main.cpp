#include <SFML/Graphics.hpp>
#include "GameStateMgr.hpp"
#include "GameState.hpp"

static float constexpr SECS_PER_FRAME = { (float)(1.f / 60.f) };

GameStateMgr gameStateMgr{};

void input();
void update(const sf::Time& l_dt);
void output(sf::RenderWindow& l_wnd);

int main() {
    sf::RenderWindow wnd(sf::VideoMode(800, 600), "SFML Game");

    sf::Clock clock;
    sf::Time deltaTime;
    while (wnd.isOpen()) {
          
        // Handle events
        sf::Event event;
        while (wnd.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                wnd.close();
        }
        //handle input
        input();

        deltaTime += clock.restart();

        bool repaint = false;
        while (deltaTime >= sf::seconds(SECS_PER_FRAME))
        {
            repaint = true;
            update(sf::seconds(SECS_PER_FRAME));
            deltaTime -= (sf::seconds(SECS_PER_FRAME));
        }


        // Update game state
        // update(deltaTime);

        if (repaint) {
            // Render game
            wnd.clear();
            output(wnd);
            wnd.display();
        }
    }

    return 0;
}

void input()
{
    gameStateMgr.getCurrentState()->handleInput();
}

void update(const sf::Time& l_dt)
{
    gameStateMgr.getCurrentState()->update(l_dt);
}

void output(sf::RenderWindow& l_wnd)
{
    gameStateMgr.getCurrentState()->render(l_wnd);
}

static void intel()
{
    auto p = std::string("nope");
}