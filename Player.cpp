#include "Player.hpp"
#include "Sprite.hpp"


Player::Player()
    : tex{}
    , playerFSM{}
    //, currAnim{PlayerAnim::IdleRight}
    , currFrame{}
{
    if (!tex.loadFromFile("assets/textures/player_atlas84x84.png"))
    {
        std::cout << "Unable to load texture" << std::endl;
    }

    playerFSM.gravity = 2.f;
    dispatch(playerFSM, JumpEvent{ 1000 });

    playerFSM.posy = 200.f;
    std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;

    currFrame = animMap[PlayerAnim::InAirRight].at(0);
    //this->currAnim = PlayerAnim::InAirRight;

}



void Player::update(const sf::Time& l_dt) {

    playerFSM.dt = l_dt.asSeconds();

    //playerFSM.velx = 0.f;
   // playerFSM.vely = 0.f;
   



    if (playerFSM.isType(states_player::Rising{}))
    {
        playerFSM.jumpHeight += playerFSM.gravity;
        playerFSM.vely -= playerFSM.jumpHeight;
        playerFSM.posy += (playerFSM.vely * ( 1 - (playerFSM.jumpHeight / playerFSM.jumpHeightMax))) * l_dt.asSeconds();
        playerFSM.posx += playerFSM.velx * l_dt.asSeconds();

        std::cout << playerFSM.jumpHeight << ", " << std::endl;
        if (playerFSM.jumpHeight > playerFSM.jumpHeightMax)
        {
            std::cout << "Reached peak of jump" << std::endl;
            std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;
            playerFSM.vely = 10.f;

            dispatch(playerFSM, ReachedJumpPeakEvent{});

        }
    }
    else if (playerFSM.isType(states_player::Falling{}))
    {
        if (playerFSM.vely == 0.f)
            playerFSM.vely = 10.f;
        playerFSM.vely *= playerFSM.vely;
        playerFSM.posy += playerFSM.vely * l_dt.asSeconds();

        if (playerFSM.posy + playerFSM.height > playerFSM.maxY)
        {
            playerFSM.posy = playerFSM.maxY - playerFSM.height;
            std::cout << "Landed" << std::endl;

            std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;
            std::cout << "PlayerFSM.vely = " << playerFSM.vely << std::endl;
           // std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;



            playerFSM.vely = 0.f;
            playerFSM.jumpHeight = 0;
            currFrame = animMap[PlayerAnim::IdleRight].at(0);
            //currAnim = PlayerAnim::IdleRight;
            dispatch(playerFSM, LandedEvent{});


        }

    }
    else if (playerFSM.isType(states_player::Idle{}))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            playerFSM.jumpHeight = 0;
            currFrame = animMap[PlayerAnim::InAirRight].at(0);
            //currAnim = PlayerAnim::IdleRight;
                dispatch(playerFSM, JumpEvent{1000});
        }
    }
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
    tmpSpr.setPosition(playerFSM.posx, playerFSM.posy);
    tmpSpr.setTextureRect(currFrame);



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
