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

    playerFSM.gravity = 1200.f;
    playerFSM.vely = -1000.f;
    dispatch(playerFSM, JumpEvent{ 1000 });

    playerFSM.posy = 500.f;
    std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;
    if (playerFSM.facingRight)
    {
        currFrame = animMap[PlayerAnim::InAirRight].at(0);

    }
    else
    {
        currFrame = animMap[PlayerAnim::InAirLeft].at(0);

    }
    //this->currAnim = PlayerAnim::InAirRight;

}




//  All the logic for what happens to the players state based on what state they are in goes here and the data for the player 
//  is in playerFSM. structure, and the sprite when generated on the fly will use that information and the currFrame as the textureRect

void Player::update(const sf::Time& l_dt) {

    playerFSM.dt = l_dt.asSeconds();

    //playerFSM.velx = 0.f;
   // playerFSM.vely = 0.f;
    int currAnimIndex = 0;


    
    std::unique_ptr<PlayerAnim> wasAnimChange = nullptr;

    if (playerFSM.isType(states_player::Rising{}))
    {
        

        
       
        playerFSM.vely += playerFSM.gravity * l_dt.asSeconds();
        playerFSM.posy += playerFSM.vely * l_dt.asSeconds();
        playerFSM.posx += playerFSM.velx * l_dt.asSeconds();

        std::cout << playerFSM.vely << ", " << std::endl;
        if (abs(playerFSM.vely) < 50.f)
        {
            std::cout << "Reached peak of jump" << std::endl;
            std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;
            std::cout << "PlayerFSM.vely at top of jump = " << playerFSM.vely << std::endl;

            //playerFSM.vely = 10.f;
            playerFSM.vely = 1.f;

            dispatch(playerFSM, ReachedJumpPeakEvent{});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            playerFSM.velx = -240.f;
            playerFSM.facingRight = false;
            currFrame = animMap[PlayerAnim::InAirLeft].at(0);
            dispatch(playerFSM, BeganMovingLeftEvent{});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerFSM.velx = 240.f;
            playerFSM.facingRight = true;
            currFrame = animMap[PlayerAnim::InAirRight].at(0);
            dispatch(playerFSM, BeganMovingRightEvent{});
        }
        else
        {
            if (playerFSM.facingRight)
                currFrame = animMap[PlayerAnim::InAirRight].at(0);
            else
                currFrame = animMap[PlayerAnim::InAirLeft].at(0);
            playerFSM.velx = 0.f;
        }
    }
    else if (playerFSM.isType(states_player::Falling{}))
    {
        playerFSM.vely += playerFSM.gravity * l_dt.asSeconds();
        playerFSM.posy += playerFSM.vely * l_dt.asSeconds();
        playerFSM.posx += playerFSM.velx * l_dt.asSeconds();

        if (playerFSM.posy + playerFSM.height > playerFSM.maxY)
        {
            playerFSM.posy = playerFSM.maxY - playerFSM.height;
            std::cout << "Landed" << std::endl;

            std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;
            std::cout << "PlayerFSM.vely = " << playerFSM.vely << std::endl;
           // std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;



            playerFSM.vely = 0.f;
            playerFSM.jumpHeight = 0;

            if (playerFSM.facingRight)
                currFrame = animMap[PlayerAnim::IdleRight].at(0);
            else
                currFrame = animMap[PlayerAnim::IdleLeft].at(0);

            //currAnim = PlayerAnim::IdleRight;
            dispatch(playerFSM, LandedEvent{});


        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            playerFSM.velx = -240.f;
            playerFSM.facingRight = false;
            currFrame = animMap[PlayerAnim::InAirLeft].at(0);
            dispatch(playerFSM, BeganMovingLeftEvent{});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerFSM.velx = 240.f;
            playerFSM.facingRight = true;
            currFrame = animMap[PlayerAnim::InAirRight].at(0);
            dispatch(playerFSM, BeganMovingRightEvent{});
        }
        else
        {

            if (playerFSM.facingRight)
                currFrame = animMap[PlayerAnim::InAirRight].at(0);
            else
                currFrame = animMap[PlayerAnim::InAirLeft].at(0);

            playerFSM.velx = 0.f;
        }

    }
    else if (playerFSM.isType(states_player::Idle{}))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            playerFSM.vely = -1000.f;
            playerFSM.jumpHeight = 0;
            if (playerFSM.facingRight)
                currFrame = animMap[PlayerAnim::InAirRight].at(0);
            else
                currFrame = animMap[PlayerAnim::InAirLeft].at(0);

            //currAnim = PlayerAnim::IdleRight;
                dispatch(playerFSM, JumpEvent{1000});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            playerFSM.velx = -240.f;
            playerFSM.facingRight = false;
            playerFSM.currAnimFrameCount = 4;
            playerFSM.currAnimFrameIndex = 0;
            animTimer.restart();
            animDelay = 0.14f;
            currFrame = animMap[PlayerAnim::RunningLeft].at(0);
            dispatch(playerFSM, BeganMovingLeftEvent{});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerFSM.velx = 240.f;
            playerFSM.facingRight = true;
            playerFSM.currAnimFrameCount = 4;
            playerFSM.currAnimFrameIndex = 0;
            animTimer.restart();
            animDelay = 0.14f;
            currFrame = animMap[PlayerAnim::RunningRight].at(0);
            dispatch(playerFSM, BeganMovingRightEvent{});
        }
        else
        {
            if (playerFSM.facingRight)
                currFrame = animMap[PlayerAnim::IdleRight].at(0);
            else
                currFrame = animMap[PlayerAnim::IdleLeft].at(0);

            playerFSM.velx = 0.f;
        }
    }
    else if (playerFSM.isType(states_player::MovingLeft{}))
    {
        playerFSM.posx += playerFSM.velx * l_dt.asSeconds();

        PlayerAnim* currAnim;
        if (playerFSM.facingRight)
            currAnim = new PlayerAnim(PlayerAnim::RunningRight);
        else
            currAnim = new PlayerAnim(PlayerAnim::RunningLeft);

        wasAnimChange = std::make_unique<PlayerAnim>(*(PlayerAnim*)std::move(currAnim));
        // animate the player
        if (animTimer.getElapsedTime().asSeconds() > animDelay)
        {
            animTimer.restart();
            if (++playerFSM.currAnimFrameIndex >= playerFSM.currAnimFrameCount)
            {
                playerFSM.currAnimFrameIndex = 0;
            }


            currAnimIndex = playerFSM.currAnimFrameIndex;
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            playerFSM.velx = 0.f;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                playerFSM.facingRight = true;
                currAnimIndex = 0;
                currFrame = animMap[PlayerAnim::IdleRight].at(0);

            }
            else
            {
                currAnimIndex = 0;
                currFrame = animMap[PlayerAnim::IdleLeft].at(0);
            }
            dispatch(playerFSM, StoppedMovingLeftEvent{});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            playerFSM.vely = -1000.f;
            playerFSM.jumpHeight = 0;
            if (playerFSM.facingRight)
                currFrame = animMap[PlayerAnim::InAirRight].at(0);
            else
                currFrame = animMap[PlayerAnim::InAirLeft].at(0);

            //currAnim = PlayerAnim::IdleRight;
            currAnimIndex = 0;
            dispatch(playerFSM, JumpEvent{ 1000 });
        }

        
       
    }
    else if (playerFSM.isType(states_player::MovingRight{}))
    {
        playerFSM.posx += playerFSM.velx * l_dt.asSeconds();

        PlayerAnim* currAnim;
        if (playerFSM.facingRight)
            currAnim = new PlayerAnim(PlayerAnim::RunningRight);
        else
            currAnim = new PlayerAnim(PlayerAnim::RunningLeft);

        wasAnimChange = std::make_unique<PlayerAnim>(*(PlayerAnim*)std::move(currAnim));
        // animate the player
        if (animTimer.getElapsedTime().asSeconds() > animDelay)
        {
            animTimer.restart();
            if (++playerFSM.currAnimFrameIndex >= playerFSM.currAnimFrameCount)
            {
                playerFSM.currAnimFrameIndex = 0;
            }


            currAnimIndex = playerFSM.currAnimFrameIndex;
        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerFSM.velx = 0.f;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                playerFSM.facingRight = false;
                currAnimIndex = 0;
                currFrame = animMap[PlayerAnim::IdleLeft].at(0);

            }
            else
            {
                currAnimIndex = 0;
                currFrame = animMap[PlayerAnim::IdleRight].at(0);
            }
            dispatch(playerFSM, StoppedMovingRightEvent{});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            playerFSM.vely = -1000.f;
            playerFSM.jumpHeight = 0;
            if (playerFSM.facingRight)
                currFrame = animMap[PlayerAnim::InAirRight].at(0);
            else
                currFrame = animMap[PlayerAnim::InAirLeft].at(0);

            //currAnim = PlayerAnim::IdleRight;
            currAnimIndex = 0;
            dispatch(playerFSM, JumpEvent{ 1000 });
        }
    }
    else if (playerFSM.isType(states_player::RisingAndMovingLeft{})) 
    {
        // Implement this next
        playerFSM.vely += playerFSM.gravity * l_dt.asSeconds();
        playerFSM.posy += playerFSM.vely * l_dt.asSeconds();
        playerFSM.posx += playerFSM.velx * l_dt.asSeconds();

        std::cout << playerFSM.vely << ", " << std::endl;
        if (abs(playerFSM.vely) < 50.f)
        {
            std::cout << "Reached peak of jump" << std::endl;
            std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;
            std::cout << "PlayerFSM.vely at top of jump = " << playerFSM.vely << std::endl;

            //playerFSM.vely = 10.f;
            playerFSM.vely = 1.f;

            dispatch(playerFSM, ReachedJumpPeakEvent{});
        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerFSM.velx = 0.f;
            currFrame = animMap[PlayerAnim::InAirLeft].at(0);
            dispatch(playerFSM, StoppedMovingLeftEvent{});
            
        }
        else
        {
            currFrame = animMap[PlayerAnim::InAirLeft].at(0);
        }

    }
    else if (playerFSM.isType(states_player::RisingAndMovingRight{}))
    {
        // Implement this next
        playerFSM.vely += playerFSM.gravity * l_dt.asSeconds();
        playerFSM.posy += playerFSM.vely * l_dt.asSeconds();
        playerFSM.posx += playerFSM.velx * l_dt.asSeconds();

        std::cout << playerFSM.vely << ", " << std::endl;
        if (abs(playerFSM.vely) < 50.f)
        {
            std::cout << "Reached peak of jump" << std::endl;
            std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;
            std::cout << "PlayerFSM.vely at top of jump = " << playerFSM.vely << std::endl;

            //playerFSM.vely = 10.f;
            playerFSM.vely = 1.f;

            dispatch(playerFSM, ReachedJumpPeakEvent{});
        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            playerFSM.velx = 0.f;
            currFrame = animMap[PlayerAnim::InAirRight].at(0);
            dispatch(playerFSM, StoppedMovingRightEvent{});

        }
        else
        {
            currFrame = animMap[PlayerAnim::InAirRight].at(0);
        }
    }
    else if (playerFSM.isType(states_player::FallingAndMovingLeft{})) 
    {

        // Implement this next
        playerFSM.vely += playerFSM.gravity * l_dt.asSeconds();
        playerFSM.posy += playerFSM.vely * l_dt.asSeconds();
        playerFSM.posx += playerFSM.velx * l_dt.asSeconds();

        if (playerFSM.posy + playerFSM.height > playerFSM.maxY)
        {
            playerFSM.posy = playerFSM.maxY - playerFSM.height;
            std::cout << "Landed" << std::endl;

            std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;
            std::cout << "PlayerFSM.vely = " << playerFSM.vely << std::endl;
            // std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;



            playerFSM.vely = 0.f;
            playerFSM.jumpHeight = 0;
            playerFSM.currAnimFrameCount = 4;
            playerFSM.currAnimFrameIndex = 0;
            animTimer.restart();
            animDelay = 0.14f;
            currFrame = animMap[PlayerAnim::RunningLeft].at(0);

            //currAnim = PlayerAnim::IdleRight;
            dispatch(playerFSM, LandedEvent{});

        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerFSM.velx = 0.f;
            currFrame = animMap[PlayerAnim::InAirLeft].at(0);
            dispatch(playerFSM, StoppedMovingLeftEvent{});
        }
        else
        {
            currFrame = animMap[PlayerAnim::InAirLeft].at(0);
        }
    }
   
    else if (playerFSM.isType(states_player::FallingAndMovingRight{}))
    {
    // Implement
      // Implement this next
      playerFSM.vely += playerFSM.gravity * l_dt.asSeconds();
      playerFSM.posy += playerFSM.vely * l_dt.asSeconds();
      playerFSM.posx += playerFSM.velx * l_dt.asSeconds();

      if (playerFSM.posy + playerFSM.height > playerFSM.maxY)
      {
          playerFSM.posy = playerFSM.maxY - playerFSM.height;
          std::cout << "Landed" << std::endl;

          std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;
          std::cout << "PlayerFSM.vely = " << playerFSM.vely << std::endl;
          // std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;



          playerFSM.vely = 0.f;
          playerFSM.jumpHeight = 0;
          playerFSM.currAnimFrameCount = 4;
          playerFSM.currAnimFrameIndex = 0;
          animTimer.restart();
          animDelay = 0.14f;
          currFrame = animMap[PlayerAnim::RunningRight].at(0);

          //currAnim = PlayerAnim::IdleRight;
          dispatch(playerFSM, LandedEvent{});


      }

      if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      {
          playerFSM.velx = 0.f;
          currFrame = animMap[PlayerAnim::InAirRight].at(0);
          dispatch(playerFSM, StoppedMovingRightEvent{});
      }
      else
      {
          currFrame = animMap[PlayerAnim::InAirRight].at(0);
      }

    }

    else if (playerFSM.isType(states_player::Shooting{})){}
    else if (playerFSM.isType(states_player::MovingLeftAndShooting{})){ }
    else if (playerFSM.isType(states_player::MovingRightAndShooting{})) { }    
    else if (playerFSM.isType(states_player::RisingAndShooting{})) { }
    else if (playerFSM.isType(states_player::FallingAndShooting{})) {  }
    else if (playerFSM.isType(states_player::RisingAndMovingLeftAndShooting{})){}
    else if (playerFSM.isType(states_player::FallingAndMovingLeftAndShooting{})) {}
    else if (playerFSM.isType(states_player::RisingAndMovingRightAndShooting{})) { }
    else if (playerFSM.isType(states_player::FallingAndMovingRightAndShooting{})) { }
   
    if (wasAnimChange)
    {
        currFrame = animMap[*wasAnimChange].at(playerFSM.currAnimFrameIndex);
    }
      
}

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
