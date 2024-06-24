#include "Player.hpp"
#include "Sprite.hpp"


Player::Player()
    :  tex{}
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        {
            std::cout << "Rising" << std::endl;

        }
        playerFSM.velx = 0.f;

        if (currAnimation != PlayerAnim::InAirLeft && currAnimation != PlayerAnim::InAirRight)
        {
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::InAirRight;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 1;
                playerFSM.currAnimFrameIndex = 0;

                currFrame = animMap[PlayerAnim::InAirRight].at(0);
            }
            else
            {
                currAnimation = PlayerAnim::InAirLeft;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 1;
                playerFSM.currAnimFrameIndex = 0;
                currFrame = animMap[PlayerAnim::InAirLeft].at(0);
            }
        }

        
       
        // SHOOTBEGAN
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::InAirShootingRight;

                currFrame = animMap[PlayerAnim::InAirShootingRight].at(0);
                playerFSM.currAnimFrameCount = 1;
                animTimer.restart();
                animDelay = 0.3f;
                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;
                dispatch(playerFSM, BeganShootingEvent{});

            }
            else
            {
                currAnimation = PlayerAnim::InAirShootingLeft;

                currFrame = animMap[PlayerAnim::InAirShootingLeft].at(0);
                playerFSM.currAnimFrameCount = 1;
                animTimer.restart();
                animDelay = 0.3f;
                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;

                dispatch(playerFSM, BeganShootingEvent{});
                return;
            }
            // make a bullet
        }


        
        if (abs(playerFSM.vely) < 50.f)
        {
            std::cout << "Reached peak of jump" << std::endl;
            std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;
            std::cout << "PlayerFSM.vely at top of jump = " << playerFSM.vely << std::endl;

            //playerFSM.vely = 10.f;
            playerFSM.vely = 1.f;


            playerFSM.vely = 0.f;
           
            dispatch(playerFSM, ReachedJumpPeakEvent{});
            return;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerFSM.velx = -240.f;
            playerFSM.facingRight = false;
            currAnimation = PlayerAnim::InAirLeft;

            currFrame = animMap[PlayerAnim::InAirLeft].at(0);
            dispatch(playerFSM, BeganMovingEvent{});
            return;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            playerFSM.velx = 240.f;
            playerFSM.facingRight = true;
            currAnimation = PlayerAnim::InAirRight;

            currFrame = animMap[PlayerAnim::InAirRight].at(0);
            dispatch(playerFSM, BeganMovingEvent{});
            return;
        }
       

        playerFSM.vely += playerFSM.gravity * l_dt.asSeconds();
        playerFSM.posy += playerFSM.vely * l_dt.asSeconds();
        playerFSM.posx += playerFSM.velx * l_dt.asSeconds();
    }
    else if (playerFSM.isType(states_player::RisingAndMoving{}))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        {
            std::cout << "RisingAndMoving" << std::endl;

        }

        if (currAnimation != PlayerAnim::InAirLeft && currAnimation != PlayerAnim::InAirRight)
        {
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::InAirRight;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 4;
                playerFSM.currAnimFrameIndex = 0;

                currFrame = animMap[PlayerAnim::InAirRight].at(0);
            }
            else
            {
                currAnimation = PlayerAnim::InAirLeft;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 4;
                playerFSM.currAnimFrameIndex = 0;
                currFrame = animMap[PlayerAnim::InAirLeft].at(0);
            }
            currAnimIndex = 0;
            animTimer.restart();
            animDelay = 0.16f;
        }
        

        if (playerFSM.facingRight)
        {
            

        // if going right but not pressing right

            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 1;
                currAnimation = PlayerAnim::InAirRight;
                currFrame = animMap[PlayerAnim::InAirRight].at(0);
                dispatch(playerFSM, StoppedMovingEvent{});
            }



        }
        else
        {
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 1;
                currAnimation = PlayerAnim::InAirLeft;
                currFrame = animMap[PlayerAnim::InAirLeft].at(0);
                dispatch(playerFSM, StoppedMovingEvent{});
            }
        }

        if (playerFSM.facingRight)
        {


            // if going right but not pressing right

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;
                playerFSM.facingRight = false;
                playerFSM.currAnimFrameCount = 1;
                currAnimation = PlayerAnim::InAirLeft;
                currFrame = animMap[PlayerAnim::InAirLeft].at(0);
                dispatch(playerFSM, StoppedMovingEvent{}, BeganMovingEvent{});
            }



        }
        else
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;
                playerFSM.facingRight = true;

                playerFSM.currAnimFrameCount = 1;
                currAnimation = PlayerAnim::InAirRight;
                currFrame = animMap[PlayerAnim::InAirRight].at(0);
                dispatch(playerFSM, StoppedMovingEvent{}, BeganMovingEvent{});
            }
        }

        if (abs(playerFSM.vely) < 50.f)
        {
            std::cout << "Reached peak of jump" << std::endl;
            std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;
            std::cout << "PlayerFSM.vely at top of jump = " << playerFSM.vely << std::endl;

            //playerFSM.vely = 10.f;
            playerFSM.vely = 1.f;


            playerFSM.vely = 0.f;

            dispatch(playerFSM, ReachedJumpPeakEvent{});
        }

        playerFSM.vely += playerFSM.gravity * l_dt.asSeconds();
        playerFSM.posy += playerFSM.vely * l_dt.asSeconds();
        playerFSM.posx += playerFSM.velx * l_dt.asSeconds();
    }
    else if (playerFSM.isType(states_player::RisingAndShooting{}))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        {
            std::cout << "RisingAndShooting" << std::endl;

        }
        if (currAnimation != PlayerAnim::InAirShootingRight && currAnimation != PlayerAnim::InAirShootingLeft)
        {
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::InAirShootingRight;
                currAnimIndex = 0;

                playerFSM.currAnimFrameCount = 1;
                playerFSM.currAnimFrameIndex = 0;
                animTimer.restart();
                animDelay = 0.3f;
                playerFSM.velx = 0.f;

                currFrame = animMap[PlayerAnim::InAirShootingRight].at(0);
            }
            else
            {
                currAnimation = PlayerAnim::InAirShootingLeft;
                currAnimIndex = 0;

                playerFSM.currAnimFrameCount = 1;
                playerFSM.currAnimFrameIndex = 0;
                animTimer.restart();
                animDelay = 0.3f;
                playerFSM.velx = 0.f;

                currFrame = animMap[PlayerAnim::InAirShootingLeft].at(0);
            }
        }






        if (abs(playerFSM.vely) < 50.f)
        {
            std::cout << "Reached peak of jump" << std::endl;
            std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;
            std::cout << "PlayerFSM.vely at top of jump = " << playerFSM.vely << std::endl;

            //playerFSM.vely = 10.f;
            playerFSM.vely = 1.f;


            playerFSM.vely = 0.f;


            dispatch(playerFSM, ReachedJumpPeakEvent{});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerFSM.velx = -240.f;
            playerFSM.facingRight = false;
            currAnimation = PlayerAnim::InAirShootingLeft;

            currFrame = animMap[PlayerAnim::InAirShootingLeft].at(0);
            dispatch(playerFSM, BeganMovingEvent{});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            playerFSM.velx = 240.f;
            playerFSM.facingRight = true;
            currAnimation = PlayerAnim::InAirShootingRight;

            currFrame = animMap[PlayerAnim::InAirShootingRight].at(0);
            dispatch(playerFSM, BeganMovingEvent{});
        }
      

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || animTimer.getElapsedTime().asSeconds() > animDelay)
        {
            playerFSM.currAnimFrameCount = 1;
            playerFSM.currAnimFrameIndex = 0;
            animTimer.restart();
            animDelay = 0.14f;
            playerFSM.velx = 0.f;
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::InAirRight;
                currFrame = animMap[currAnimation].at(0);
            }
            else
            {
                currAnimation = PlayerAnim::InAirLeft;
                currFrame = animMap[currAnimation].at(0);

            }
                dispatch(playerFSM, StoppedShootingEvent{});
                return;
        }

        if (playerFSM.posy + playerFSM.height > playerFSM.maxY)
        {
            playerFSM.posy = playerFSM.maxY - playerFSM.height;
            std::cout << "Landed" << std::endl;

            std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;
            std::cout << "PlayerFSM.vely = " << playerFSM.vely << std::endl;
            // std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;


            playerFSM.velx = 0.f;
            playerFSM.vely = 0.f;
            playerFSM.jumpHeight = 0;
            playerFSM.currAnimFrameCount = 4;
            playerFSM.currAnimFrameIndex = 0;
            animTimer.restart();
            animDelay = 0.16f;

            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::RunningAndShootingRight;

                currFrame = animMap[PlayerAnim::RunningAndShootingRight].at(0);
            }
            else
            {
                currAnimation = PlayerAnim::RunningAndShootingLeft;

                currFrame = animMap[PlayerAnim::RunningAndShootingLeft].at(0);
            }
            //currAnim = PlayerAnim::IdleRight;
            dispatch(playerFSM, LandedEvent{});
            return;

        }

       

        playerFSM.vely += playerFSM.gravity * l_dt.asSeconds();
        playerFSM.posy += playerFSM.vely * l_dt.asSeconds();
       

    }
    else if (playerFSM.isType(states_player::RisingAndMovingAndShooting{}))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        {
            std::cout << "RisingAndMovingAndShooting" << std::endl;

        }


        if (playerFSM.facingRight)
        {


            // if going right but not pressing right

            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 1;
                currAnimation = PlayerAnim::InAirRight;
                currFrame = animMap[PlayerAnim::InAirRight].at(0);
                dispatch(playerFSM, StoppedMovingEvent{});
            }



        }
        else
        {
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 1;
                currAnimation = PlayerAnim::InAirLeft;
                currFrame = animMap[PlayerAnim::InAirLeft].at(0);
                dispatch(playerFSM, StoppedMovingEvent{});
            }
        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && animTimer.getElapsedTime().asSeconds() > animDelay)
        {
            playerFSM.currAnimFrameCount = 1;
            playerFSM.currAnimFrameIndex = 0;
            animTimer.restart();
            animDelay = 0.14f;
            playerFSM.velx = 0.f;



            currAnimIndex = 0;

            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                if (playerFSM.facingRight)
                {
                    currAnimation = PlayerAnim::InAirRight;

                    currFrame = animMap[PlayerAnim::InAirRight].at(0);
                }
                else
                {
                    currAnimation = PlayerAnim::InAirLeft;

                    currFrame = animMap[PlayerAnim::InAirLeft].at(0);
                }
                dispatch(playerFSM, StoppedShootingEvent{});
            }
        }


        if (abs(playerFSM.vely) < 50.f)
        {
            std::cout << "Reached peak of jump" << std::endl;
            std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;
            std::cout << "PlayerFSM.vely at top of jump = " << playerFSM.vely << std::endl;

            //playerFSM.vely = 10.f;
            playerFSM.vely = 1.f;


            playerFSM.vely = 0.f;


            dispatch(playerFSM, ReachedJumpPeakEvent{});
        }

        if (playerFSM.facingRight)
            currFrame = animMap[PlayerAnim::InAirShootingRight].at(0);
        else
            currFrame = animMap[PlayerAnim::InAirShootingLeft].at(0);


        playerFSM.vely += playerFSM.gravity * l_dt.asSeconds();
        playerFSM.posy += playerFSM.vely * l_dt.asSeconds();
        playerFSM.posx += playerFSM.velx * l_dt.asSeconds();
     }

    else if (playerFSM.isType(states_player::Falling{}))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        {
            std::cout << "Falling" << std::endl;

        }
        if (currAnimation != PlayerAnim::InAirLeft && currAnimation != PlayerAnim::InAirRight)
        {
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::InAirRight;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 1;
                playerFSM.currAnimFrameIndex = 0;

                currFrame = animMap[PlayerAnim::InAirRight].at(0);
            }
            else
            {
                currAnimation = PlayerAnim::InAirLeft;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 1;
                playerFSM.currAnimFrameIndex = 0;
                currFrame = animMap[PlayerAnim::InAirLeft].at(0);
            }
        }

        // SHOOTBEGAN
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::InAirShootingRight;

                currFrame = animMap[PlayerAnim::InAirShootingRight].at(0);
                playerFSM.currAnimFrameCount = 1;

                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;
                dispatch(playerFSM, BeganShootingEvent{});

            }
            else
            {
                currAnimation = PlayerAnim::InAirShootingLeft;

                currFrame = animMap[PlayerAnim::InAirShootingLeft].at(0);
                playerFSM.currAnimFrameCount = 1;

                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;

                dispatch(playerFSM, BeganShootingEvent{});
            }
            // make a bullet
        }


        if (playerFSM.posy + playerFSM.height > playerFSM.maxY)
        {
            playerFSM.posy = playerFSM.maxY - playerFSM.height;
            std::cout << "Landed" << std::endl;

            std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;
            std::cout << "PlayerFSM.vely = " << playerFSM.vely << std::endl;
           // std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;


            playerFSM.velx = 0.f;
            playerFSM.vely = 0.f;
            playerFSM.jumpHeight = 0;


            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::InAirRight;

                currFrame = animMap[PlayerAnim::InAirRight].at(0);
            }
            else
            {
                currAnimation = PlayerAnim::InAirLeft;

                currFrame = animMap[PlayerAnim::InAirLeft].at(0);
            }
            //currAnim = PlayerAnim::IdleRight;
            dispatch(playerFSM, LandedEvent{});


        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            playerFSM.velx = -240.f;
            playerFSM.facingRight = false;
            currAnimation = PlayerAnim::InAirLeft;

            currFrame = animMap[PlayerAnim::InAirLeft].at(0);
            dispatch(playerFSM, BeganMovingEvent{});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerFSM.velx = 240.f;
            playerFSM.facingRight = true;
            currAnimation = PlayerAnim::InAirRight;

            currFrame = animMap[PlayerAnim::InAirRight].at(0);
            dispatch(playerFSM, BeganMovingEvent{});
        }
       

         
        playerFSM.vely += playerFSM.gravity * l_dt.asSeconds();
        playerFSM.posy += playerFSM.vely * l_dt.asSeconds();
        playerFSM.posx += playerFSM.velx * l_dt.asSeconds();
    }
    else if (playerFSM.isType(states_player::FallingAndMoving{}))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        {
            std::cout << "FallingAndMoving" << std::endl;

        }
        if (currAnimation != PlayerAnim::InAirLeft && currAnimation != PlayerAnim::InAirRight)
        {
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::InAirRight;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 1;
                playerFSM.currAnimFrameIndex = 0;

                currFrame = animMap[PlayerAnim::InAirRight].at(0);
            }
            else
            {
                currAnimation = PlayerAnim::InAirLeft;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 1;
                playerFSM.currAnimFrameIndex = 0;
                currFrame = animMap[PlayerAnim::InAirLeft].at(0);
            }
        }
        if (playerFSM.facingRight)
        {


            // if going right but not pressing right

            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                playerFSM.velx = 0.f;
                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 1;
                currAnimation = PlayerAnim::InAirRight;
                currFrame = animMap[PlayerAnim::InAirRight].at(0);
                dispatch(playerFSM, StoppedMovingEvent{});
            }



        }
        else
        {
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                playerFSM.velx = 0.f;

                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 1;
                currAnimation = PlayerAnim::InAirLeft;
                currFrame = animMap[PlayerAnim::InAirLeft].at(0);
                dispatch(playerFSM, StoppedMovingEvent{});
            }
        }
        // SHOOTBEGAN
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::InAirShootingRight;

                currFrame = animMap[PlayerAnim::InAirShootingRight].at(0);
                playerFSM.currAnimFrameCount = 1;

                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;
                dispatch(playerFSM, BeganShootingEvent{});

            }
            else
            {
                currAnimation = PlayerAnim::InAirShootingLeft;

                currFrame = animMap[PlayerAnim::InAirShootingLeft].at(0);
                playerFSM.currAnimFrameCount = 1;

                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;

                dispatch(playerFSM, BeganShootingEvent{});
            }
            // make a bullet
        }

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
            {
                currAnimation = PlayerAnim::RunningRight;

                currFrame = animMap[PlayerAnim::RunningRight].at(0);
            }
            else
            {
                currAnimation = PlayerAnim::RunningLeft;

                currFrame = animMap[PlayerAnim::RunningLeft].at(0);
            }
            //currAnim = PlayerAnim::IdleRight;
            dispatch(playerFSM, LandedEvent{});
            return;

        }

        playerFSM.vely += playerFSM.gravity * l_dt.asSeconds();
        playerFSM.posy += playerFSM.vely * l_dt.asSeconds();
        playerFSM.posx += playerFSM.velx * l_dt.asSeconds();
    }
    else if (playerFSM.isType(states_player::FallingAndMovingAndShooting{}))
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        {
            std::cout << "FallingAndMovingAndShooting" << std::endl;

        }


        if (playerFSM.facingRight)
        {


            // if going right but not pressing right

            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 1;
                currAnimation = PlayerAnim::InAirRight;
                currFrame = animMap[PlayerAnim::InAirRight].at(0);
                dispatch(playerFSM, StoppedMovingEvent{});
            }



        }
        else
        {
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 1;
                currAnimation = PlayerAnim::InAirLeft;
                currFrame = animMap[PlayerAnim::InAirLeft].at(0);
                dispatch(playerFSM, StoppedMovingEvent{});
            }
        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && animTimer.getElapsedTime().asSeconds() > animDelay)
        {
            playerFSM.currAnimFrameCount = 1;
            playerFSM.currAnimFrameIndex = 0;
            animTimer.restart();
            animDelay = 0.14f;
            playerFSM.velx = 0.f;



            currAnimIndex = 0;

            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                if (playerFSM.facingRight)
                {
                    currAnimation = PlayerAnim::InAirRight;

                    currFrame = animMap[PlayerAnim::InAirRight].at(0);
                }
                else
                {
                    currAnimation = PlayerAnim::InAirLeft;

                    currFrame = animMap[PlayerAnim::InAirLeft].at(0);
                }
                dispatch(playerFSM, StoppedShootingEvent{});
            }
        }


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
            {
                currAnimation = PlayerAnim::RunningRight;

                currFrame = animMap[PlayerAnim::RunningRight].at(0);
            }
            else
            {
                currAnimation = PlayerAnim::RunningLeft;

                currFrame = animMap[PlayerAnim::RunningLeft].at(0);
            }
            //currAnim = PlayerAnim::IdleRight;
            dispatch(playerFSM, LandedEvent{});
            return;

        }


        if (playerFSM.facingRight)
            currFrame = animMap[PlayerAnim::InAirShootingRight].at(0);
        else
            currFrame = animMap[PlayerAnim::InAirShootingLeft].at(0);


        playerFSM.vely += playerFSM.gravity * l_dt.asSeconds();
        playerFSM.posy += playerFSM.vely * l_dt.asSeconds();
        playerFSM.posx += playerFSM.velx * l_dt.asSeconds();
    }
    else if (playerFSM.isType(states_player::FallingAndShooting{})) 
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
    {
        std::cout << "FallingAndShooting" << std::endl;

    }
    if (currAnimation != PlayerAnim::InAirShootingLeft && currAnimation != PlayerAnim::InAirShootingRight)
    {
        if (playerFSM.facingRight)
        {
            currAnimation = PlayerAnim::InAirShootingRight;
            currAnimIndex = 0;
            playerFSM.currAnimFrameCount = 1;
            playerFSM.currAnimFrameIndex = 0;

            currFrame = animMap[PlayerAnim::InAirShootingRight].at(0);
        }
        else
        {
            currAnimation = PlayerAnim::InAirShootingLeft;
            currAnimIndex = 0;
            playerFSM.currAnimFrameCount = 1;
            playerFSM.currAnimFrameIndex = 0;
            currFrame = animMap[PlayerAnim::InAirShootingLeft].at(0);
        }
    }

    if (playerFSM.posy + playerFSM.height > playerFSM.maxY)
    {
        playerFSM.posy = playerFSM.maxY - playerFSM.height;
        std::cout << "Landed" << std::endl;

        std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;
        std::cout << "PlayerFSM.vely = " << playerFSM.vely << std::endl;
        // std::cout << "PlayerFSM.posy = " << playerFSM.posy << std::endl;


        playerFSM.velx = 0.f;
        playerFSM.vely = 0.f;
        playerFSM.jumpHeight = 0;


        if (playerFSM.facingRight)
        {
            currAnimation = PlayerAnim::InAirRight;

            currFrame = animMap[PlayerAnim::InAirRight].at(0);
        }
        else
        {
            currAnimation = PlayerAnim::InAirLeft;

            currFrame = animMap[PlayerAnim::InAirLeft].at(0);
        }
        //currAnim = PlayerAnim::IdleRight;
        dispatch(playerFSM, LandedEvent{});
        return;

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        playerFSM.velx = -240.f;
        playerFSM.facingRight = false;
        currAnimation = PlayerAnim::InAirShootingLeft;

        currFrame = animMap[PlayerAnim::InAirShootingLeft].at(0);
        dispatch(playerFSM, BeganMovingEvent{});
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        playerFSM.velx = 240.f;
        playerFSM.facingRight = true;
        currAnimation = PlayerAnim::InAirShootingRight;

        currFrame = animMap[PlayerAnim::InAirShootingRight].at(0);
        dispatch(playerFSM, BeganMovingEvent{});
    }


    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && animTimer.getElapsedTime().asSeconds() > animDelay)
    {
        playerFSM.currAnimFrameCount = 1;
        playerFSM.currAnimFrameIndex = 0;
        animTimer.restart();
        animDelay = 0.14f;
        playerFSM.velx = 0.f;



        currAnimIndex = 0;

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::InAirRight;

                currFrame = animMap[PlayerAnim::InAirRight].at(0);
            }
            else
            {
                currAnimation = PlayerAnim::InAirLeft;

                currFrame = animMap[PlayerAnim::InAirLeft].at(0);
            }
            dispatch(playerFSM, StoppedShootingEvent{});
        }
    }

    playerFSM.vely += playerFSM.gravity * l_dt.asSeconds();
    playerFSM.posy += playerFSM.vely * l_dt.asSeconds();

}

    else if (playerFSM.isType(states_player::Idle{}))
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        {
            std::cout << "Idle" << std::endl;

        }
        if (playerFSM.facingRight)
        {
            currAnimation = PlayerAnim::IdleRight;

            currFrame = animMap[PlayerAnim::IdleRight].at(0);
        }
        else
        {
            currAnimation = PlayerAnim::IdleLeft;

            currFrame = animMap[PlayerAnim::IdleLeft].at(0);
        }

        // SHOOTBEGAN
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::ShootingRight;

                currFrame = animMap[PlayerAnim::ShootingRight].at(0);
                playerFSM.currAnimFrameCount = 1;

                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;
                dispatch(playerFSM, BeganShootingEvent{});

            }
            else
            {
                currAnimation = PlayerAnim::ShootingLeft;

                currFrame = animMap[PlayerAnim::ShootingLeft].at(0);
                playerFSM.currAnimFrameCount = 1;

                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;

                dispatch(playerFSM, BeganShootingEvent{});
            }
            // make a bullet
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            playerFSM.vely = -1000.f;
            playerFSM.jumpHeight = 0;
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::InAirRight;

                currFrame = animMap[PlayerAnim::InAirRight].at(0);
            }
            else
            {
                currAnimation = PlayerAnim::InAirLeft;

                currFrame = animMap[PlayerAnim::InAirLeft].at(0);
            }

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
            currAnimation = PlayerAnim::RunningLeft;

            currFrame = animMap[PlayerAnim::RunningLeft].at(0);
            dispatch(playerFSM, BeganMovingEvent{});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerFSM.velx = 240.f;
            playerFSM.facingRight = true;
            playerFSM.currAnimFrameCount = 4;
            playerFSM.currAnimFrameIndex = 0;
            animTimer.restart();
            animDelay = 0.14f;
            currAnimation = PlayerAnim::RunningRight;

            currFrame = animMap[PlayerAnim::RunningRight].at(0);
            dispatch(playerFSM, BeganMovingEvent{});
        }
        //playerFSM.vely += playerFSM.gravity * l_dt.asSeconds();
        //playerFSM.posy += playerFSM.vely * l_dt.asSeconds();
        //playerFSM.posx += playerFSM.velx * l_dt.asSeconds();
    }
    else if (playerFSM.isType(states_player::Moving{}))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        {
            std::cout << "Moving" << std::endl;

        }
        // start
        if (currAnimation != PlayerAnim::RunningLeft && currAnimation != PlayerAnim::RunningRight)
        {
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::RunningRight;
                currAnimIndex = playerFSM.currAnimFrameIndex;
                playerFSM.currAnimFrameCount = 4;
                
                animDelay = 0.16f;
                animTimer.restart();

                currFrame = animMap[PlayerAnim::RunningRight].at(0);
            }
            else
            {
                currAnimation = PlayerAnim::RunningLeft;
                currAnimIndex = playerFSM.currAnimFrameIndex;

                playerFSM.currAnimFrameCount = 4;
               
                animDelay = 0.16f;
                animTimer.restart();
                currFrame = animMap[PlayerAnim::RunningLeft].at(0);
            }
            currAnimIndex = 0;
            animTimer.restart();
            animDelay = 0.16f;
        }
        //animate
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

      

        
        // if going right but not pressing right
       
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && playerFSM.facingRight)
            {
                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 1;
                playerFSM.velx = 0.f;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    playerFSM.facingRight = false;
                    currAnimation = PlayerAnim::IdleLeft;
                    currFrame = animMap[PlayerAnim::IdleLeft].at(0);
                }
                else
                {
                    currAnimation = PlayerAnim::IdleRight;
                    currFrame = animMap[PlayerAnim::IdleRight].at(0);
                }
                dispatch(playerFSM, StoppedMovingEvent{});
                return;
            }
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !playerFSM.facingRight)
            {
                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 1;
                playerFSM.velx = 0.f;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    playerFSM.facingRight = true;
                    currAnimation = PlayerAnim::IdleRight;
                    currFrame = animMap[PlayerAnim::IdleRight].at(0);
                }
                else
                {
                    currAnimation = PlayerAnim::IdleLeft;
                    currFrame = animMap[PlayerAnim::IdleLeft].at(0);
                }
                dispatch(playerFSM, StoppedMovingEvent{});
                return;
            }

         
       
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            playerFSM.vely = -1000.f;
            playerFSM.jumpHeight = 0;
            playerFSM.currAnimFrameIndex = 0;
            currAnimIndex = 0;
            playerFSM.currAnimFrameCount = 1;
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::InAirRight;

                currFrame = animMap[PlayerAnim::InAirRight].at(0);
            }
            else
            {
                currAnimation = PlayerAnim::InAirLeft;

                currFrame = animMap[PlayerAnim::InAirLeft].at(0);
            }

            //currAnim = PlayerAnim::IdleRight;
            dispatch(playerFSM, JumpEvent{ 1000 });
            return;
        }


        // SHOOTBEGAN
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::RunningAndShootingRight;

                currFrame = animMap[PlayerAnim::RunningAndShootingRight].at(0);
                playerFSM.currAnimFrameCount = 4;
                currAnimIndex = playerFSM.currAnimFrameIndex;
                animTimer.restart();
                animDelay = 0.3f;
                dispatch(playerFSM, BeganShootingEvent{});
                return;
            }
            else
            {
                currAnimation = PlayerAnim::RunningAndShootingLeft;

                currFrame = animMap[PlayerAnim::RunningAndShootingLeft].at(0);
                playerFSM.currAnimFrameCount = 4;
          
                currAnimIndex = playerFSM.currAnimFrameIndex;

                animTimer.restart();
                animDelay = 0.3f;
                dispatch(playerFSM, BeganShootingEvent{});
                return;
            }
            // make a bullet
        }

        
        currFrame = animMap[(playerFSM.facingRight) ? PlayerAnim::RunningRight : PlayerAnim::RunningLeft].at(playerFSM.currAnimFrameIndex);
        playerFSM.posx += playerFSM.velx * l_dt.asSeconds();
    }
    else if (playerFSM.isType(states_player::Shooting{}))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        {
            std::cout << "Shooting" << std::endl;

        }





        if (playerFSM.facingRight)
        {
            if (this->currAnimation != PlayerAnim::ShootingRight)
            {
                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;
                playerFSM.currAnimFrameCount = 1;
                currAnimation = PlayerAnim::ShootingRight;
                currFrame = animMap[PlayerAnim::ShootingRight].at(0);
                animTimer.restart();
            }
        }
        else
        {
            if (this->currAnimation != PlayerAnim::ShootingLeft)
            {
                playerFSM.currAnimFrameIndex = 0;
                currAnimIndex = 0;

                playerFSM.currAnimFrameCount = 1;
                currAnimation = PlayerAnim::ShootingLeft;
                currFrame = animMap[PlayerAnim::ShootingLeft].at(0);
                animTimer.restart();
            }
        }
      


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            playerFSM.velx = -240.f;
            playerFSM.facingRight = false;
            playerFSM.currAnimFrameCount = 4;
            playerFSM.currAnimFrameIndex = 0;
            animTimer.restart();
            animDelay = 0.14f;
            currAnimation = PlayerAnim::RunningAndShootingLeft;

            currFrame = animMap[PlayerAnim::RunningAndShootingLeft].at(0);
            dispatch(playerFSM, BeganMovingEvent{});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerFSM.velx = 240.f;
            playerFSM.facingRight = true;
            playerFSM.currAnimFrameCount = 4;
            playerFSM.currAnimFrameIndex = 0;
            animTimer.restart();
            animDelay = 0.14f;
            currAnimation = PlayerAnim::RunningAndShootingRight;

            currFrame = animMap[PlayerAnim::RunningAndShootingRight].at(0);
            dispatch(playerFSM, BeganMovingEvent{});
        }

/// UP

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            playerFSM.vely = -1000.f;
            playerFSM.jumpHeight = 0;
            playerFSM.currAnimFrameIndex = 0;
            currAnimIndex = 0;
            playerFSM.currAnimFrameCount = 1;
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::InAirShootingRight;

                currFrame = animMap[PlayerAnim::InAirShootingRight].at(0);
            }
            else
            {
                currAnimation = PlayerAnim::InAirShootingLeft;

                currFrame = animMap[PlayerAnim::InAirShootingLeft].at(0);
            }

            //currAnim = PlayerAnim::IdleRight;
            dispatch(playerFSM, JumpEvent{ 1000 });
        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || animTimer.getElapsedTime().asSeconds() > animDelay)
        {
            playerFSM.currAnimFrameCount = 1;
            playerFSM.currAnimFrameIndex = 0;
            animTimer.restart();
            animDelay = 0.14f;
            playerFSM.velx = 240.f;



            currAnimIndex = 0;
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::IdleRight;

                currFrame = animMap[PlayerAnim::IdleRight].at(0);
            }
            else
            {
                currAnimation = PlayerAnim::IdleLeft;

                currFrame = animMap[PlayerAnim::IdleLeft].at(0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                dispatch(playerFSM, StoppedShootingEvent{}, BeganShootingEvent{});
            else
                dispatch(playerFSM, StoppedShootingEvent{});
        }


        if (playerFSM.facingRight)
            currFrame = animMap[PlayerAnim::ShootingRight].at(0);
        else
            currFrame = animMap[PlayerAnim::ShootingLeft].at(0);
}
    else if (playerFSM.isType(states_player::MovingAndShooting{}))
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        {
            std::cout << "MovingAndShooting" << std::endl;

        }
        
            if (this->currAnimation != PlayerAnim::RunningAndShootingRight && this->currAnimation != PlayerAnim::RunningAndShootingLeft)
            {

                if (playerFSM.facingRight)
                {
                    currAnimation = PlayerAnim::RunningAndShootingRight;
                    currAnimIndex = playerFSM.currAnimFrameIndex;
                    playerFSM.currAnimFrameCount = 4;

                    animDelay = 0.3f;
                    animTimer.restart();

                    currFrame = animMap[PlayerAnim::RunningAndShootingRight].at(0);
                }
                else
                {
                    currAnimation = PlayerAnim::RunningAndShootingLeft;
                    currAnimIndex = playerFSM.currAnimFrameIndex;

                    playerFSM.currAnimFrameCount = 4;

                    animDelay = 0.3f;
                    animTimer.restart();
                    currFrame = animMap[PlayerAnim::RunningAndShootingLeft].at(0);
                }
              

              
            }
       
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
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerFSM.velx = 0.f;

            playerFSM.currAnimFrameCount = 1;



            currAnimIndex = 0;
            animTimer.restart();
            animDelay = 0.3f;
            playerFSM.currAnimFrameIndex = 0;

            currAnimation = PlayerAnim::ShootingRight;

            currFrame = animMap[PlayerAnim::ShootingRight].at(0);
            dispatch(playerFSM, StoppedMovingEvent{});
            return;


        }
        if (playerFSM.facingRight)
        {
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                playerFSM.velx = 0.f;

                playerFSM.currAnimFrameCount = 1;



                currAnimIndex = 0;
                animTimer.restart();
                animDelay = 0.3f;
                playerFSM.currAnimFrameIndex = 0;
                currAnimation = PlayerAnim::ShootingRight;

                currFrame = animMap[PlayerAnim::ShootingRight].at(0);
                dispatch(playerFSM, StoppedMovingEvent{});
                return;


            }
        }
        else
        {
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                playerFSM.velx = 0.f;

                playerFSM.currAnimFrameCount = 1;



                currAnimIndex = 0;
                animTimer.restart();
                animDelay = 0.3f;
                playerFSM.currAnimFrameIndex = 0;
                currAnimation = PlayerAnim::ShootingLeft;

                currFrame = animMap[PlayerAnim::ShootingLeft].at(0);
                dispatch(playerFSM, StoppedMovingEvent{});
                return;

            }

        }



        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::RunningRight;

                currFrame = animMap[PlayerAnim::RunningRight].at(0);
                playerFSM.currAnimFrameCount = 4;
                animDelay = 0.16f;
                animTimer.restart();
                
                currAnimIndex = 0;
                dispatch(playerFSM, StoppedShootingEvent{});
                
            }
            else
            {
                currAnimation = PlayerAnim::RunningLeft;

                currFrame = animMap[PlayerAnim::RunningLeft].at(0);
                playerFSM.currAnimFrameCount = 4;
                animDelay = 0.16f;
                animTimer.restart();
                
                currAnimIndex = 0;

                dispatch(playerFSM, StoppedShootingEvent{});
            }
            return;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            playerFSM.vely = -1000.f;
            playerFSM.jumpHeight = 0;
            currAnimIndex = 0;
            if (!playerFSM.facingRight)
            {
                currAnimation = PlayerAnim::InAirShootingLeft;

                currFrame = animMap[PlayerAnim::InAirShootingLeft].at(0);
            }
            else
            {
                currAnimation = PlayerAnim::InAirShootingRight;

                currFrame = animMap[PlayerAnim::InAirShootingRight].at(0);
            }
            playerFSM.currAnimFrameCount = 1;

            playerFSM.currAnimFrameIndex = 0;
            //currAnim = PlayerAnim::IdleRight;
            


            dispatch(playerFSM, JumpEvent{ 1000 });
            return;
        }





        currFrame = animMap[(playerFSM.facingRight) ? PlayerAnim::RunningAndShootingRight : PlayerAnim::RunningAndShootingLeft].at(playerFSM.currAnimFrameIndex);
        playerFSM.posx += playerFSM.velx * l_dt.asSeconds();
    }


   }

    

   
 
   
   


bool Player::isAlive()
{
    return alive;
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

bool isAlive(Player& player)
{
    return player.isAlive();
}

void render(Player& player, sf::RenderWindow& window) {
    player.render(window);
}
