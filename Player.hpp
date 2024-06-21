#ifndef PLAYER_HPP__
#define PLAYER_HPP__


#include <iostream>
#include <SFML/Graphics.hpp>
#include "PlayerStates.hpp"
#include "Events.hpp"
#include "FSM.hpp"
#include <iostream>
#include <optional>

enum class PlayerAnim : int
{
    IdleRight = 0,
    ShootingRight = 1,
    RunningRight = 2,
    RunningAndShootingRight = 3,
    InAirRight = 4,
    InAirShootingRight = 5,
    IdleLeft = 6,
    ShootingLeft = 7,
    RunningLeft = 8,
    RunningAndShootingLeft = 9,
    InAirLeft = 10,
    InAirShootingLeft = 11

};



struct PlayerTransitions
{


    std::optional<PlayerStateVar> operator()(states_player::Idle&, const JumpEvent& e)
    {
        return states_player::Rising{ };
    }

    std::optional<PlayerStateVar> operator()(states_player::Rising&, const ReachedJumpPeakEvent& e)
    {
      
        return states_player::Falling{};
        ///  (--jumpHeightCurrent < Rising::JumpHeightMax)
    }
   
    


    std::optional<PlayerStateVar> operator()(states_player::Falling&, const LandedEvent& e)
    {
 
        return states_player::Idle{ };
    }

   

    // default
    template<typename State, typename Event>
    std::optional<PlayerStateVar> operator()(State&, const Event&) const
    { return std::nullopt; }

};



class Sprite;
using Player_FSM = FSM<PlayerStateVar, EventVar, PlayerTransitions>;

class Player {
public:
    sf::Texture tex;
    sf::IntRect currFrame;
    std::map<PlayerAnim, std::vector<sf::IntRect> > animMap = {
        {
            PlayerAnim::IdleRight, std::vector<sf::IntRect> {
            {{4 * 84,0},{84,84}}
           }
        },
        {
            PlayerAnim::ShootingRight,  std::vector<sf::IntRect> {
                {{5 * 84,0},{84,84}}
            }
        },
        {
            PlayerAnim::RunningRight, std::vector<sf::IntRect> {
                 {{0,0},{84,84}},
                 {{1 * 84,0},{84,84}},
                 {{2 * 84,0},{84,84}},
                 {{3 * 84,0},{84,84}},

            }
        },
        {
            PlayerAnim::RunningAndShootingRight, std::vector<sf::IntRect> {
                 {{0,84},{84,84}},
                 {{1 * 84,84},{84,84}},
                 {{2 * 84,84},{84,84}},
                 {{3 * 84,84},{84,84}},

            }
        },
        {
            PlayerAnim::InAirRight, std::vector<sf::IntRect> {
            {{5 * 84,84},{84,84}}
           }
        },
        {
            PlayerAnim::InAirShootingRight,  std::vector<sf::IntRect> {
                {{4 * 84,84},{84,84}}
            }
        },
        {
            PlayerAnim::IdleLeft, std::vector<sf::IntRect> {
            {{4 * 84,168},{84,84}}
           }
        },
        {
            PlayerAnim::ShootingLeft,  std::vector<sf::IntRect> {
                {{5 * 84,168},{84,84}}
            }
        },
        {
            PlayerAnim::RunningLeft, std::vector<sf::IntRect> {
                 {{0,168},{84,84}},
                 {{1 * 84,168},{84,84}},
                 {{2 * 84,168},{84,84}},
                 {{3 * 84,168},{84,84}},

            }
        },
        {
            PlayerAnim::RunningAndShootingLeft, std::vector<sf::IntRect> {
                 {{0,252},{84,84}},
                 {{1 * 84,252},{84,84}},
                 {{2 * 84,252},{84,84}},
                 {{3 * 84,252},{84,84}},

            }
        },
        {
            PlayerAnim::InAirLeft, std::vector<sf::IntRect> {
            {{5 * 84,252},{84,84}}
           }
        },
        {
            PlayerAnim::InAirShootingLeft,  std::vector<sf::IntRect> {
                {{4 * 84,252},{84,84}}
            }
        }
    };
    
public:
    Player();

    Player_FSM playerFSM;


    void update(const sf::Time& l_dt);
        // players logic, handled in the fsm, state stored in this class, updates via the fsm and transitions when they occur
        // dispatch(fsm, eventBuffer[0], 1, 2, 3 ..);  <- this updates the sprite data via the transitions passed in when creating the fsm
        // spr.setPosition(this->getPosition())
        // 
        //  ONLY SETTING THE POSITION FOR COLLISION DETECTION TO BE ABLE TO TEST ITS CURRENT POSITION, animation not neccesary .. YET...


        // after this is called on all sprites, collision detection checks and may put an event into this sprites input buffer to be handled
        //   , a few maybe, as the collision detection system knows a couple events itsef which goes right into this buffer
    

    // this gets called right before rendering to update any sprites that need to be re-evaluated after collision detection
    // update position again,  animation IS neccessary this time
    // void finalize(){ 
    // dispatch(fsm, eventBuffer[0], [1], [2]..);
    // spr.setPosition(this->getPosition();
    // currStateName = fsm.getCurrentStateName();        
    // changeAnimationIfNeeded(currStateName);
    // spr.setTextureRect(currAnimFrame);
    

    void render(sf::RenderWindow& l_wnd); 
    void finalize();

};

void update(Player& player, const sf::Time& deltaTime);

void render(Player& player, sf::RenderWindow& window);


#endif
