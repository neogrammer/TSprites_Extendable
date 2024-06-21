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


    std::optional<PlayerStateVar> operator()(states_player::Idle&, const BeganMovingLeftEvent& e)
    {

        return states_player::MovingLeft{ };
    }

    std::optional<PlayerStateVar> operator()(states_player::Idle&, const BeganMovingRightEvent& e)
    {

        return states_player::MovingRight{ };
    }

    std::optional<PlayerStateVar> operator()(states_player::MovingRight&, const StoppedMovingRightEvent& e)
    {

        return states_player::Idle{ };
    }

    std::optional<PlayerStateVar> operator()(states_player::MovingLeft&, const StoppedMovingLeftEvent& e)
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
    PlayerAnim currAnimation{ PlayerAnim::InAirRight };
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

    // logic for how the player interacts with the system defined in this function
    // as you are aware the correct state the user is in, and can code for that specific state logic, while being able to
    // change the state correctly by dispathing events to the playerFSM
    void update(const sf::Time& l_dt);
    void render(sf::RenderWindow& l_wnd); 
    void finalize();

};

void update(Player& player, const sf::Time& deltaTime);

void render(Player& player, sf::RenderWindow& window);


#endif
