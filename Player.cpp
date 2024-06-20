#include "Player.hpp"
#include "Sprite.hpp"

Player::Player()
    : tex{}
{
    if (!tex.loadFromFile("assets/textures/player_atlas84x84.png"))
    {
        std::cout << "Unable to load texture" << std::endl;
    }
}



void Player::update(const sf::Time& l_dt) {
    // players logic, handled in the fsm, state stored in this class, updates via the fsm and transitions when they occur
    // dispatch(fsm, eventBuffer[0], 1, 2, 3 ..);  <- this updates the sprite data via the transitions passed in when creating the fsm
    // spr.setPosition(this->getPosition())
    // 
    //  ONLY SETTING THE POSITION FOR COLLISION DETECTION TO BE ABLE TO TEST ITS CURRENT POSITION, animation not neccesary .. YET...


    // after this is called on all sprites, collision detection checks and may put an event into this sprites input buffer to be handled
    //   , a few maybe, as the collision detection system knows a couple events itsef which goes right into this buffer
}

// this gets called right before rendering to update any sprites that need to be re-evaluated after collision detection
// update position again,  animation IS neccessary this time
// void finalize(){ 
// dispatch(fsm, eventBuffer[0], [1], [2]..);
// spr.setPosition(this->getPosition();
// currStateName = fsm.getCurrentStateName();        
// changeAnimationIfNeeded(currStateName);
// spr.setTextureRect(currAnimFrame);


void Player::render(sf::RenderWindow& l_wnd) {


    // finalize();
    sf::Sprite tmpSpr;
    tmpSpr.setTexture(tex);
    tmpSpr.setPosition({ 400.f, 400.f });
    tmpSpr.setTextureRect({ {0,0},{84,84} });



    l_wnd.draw(tmpSpr);
}

void Player::finalize()
{
}

void update(Player& player, const sf::Time& deltaTime) {
    player.update(deltaTime);
}

void render(Player& player, sf::RenderWindow& window) {
    player.render(window);
}