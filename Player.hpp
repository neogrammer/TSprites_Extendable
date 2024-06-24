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



  

    std::optional<PlayerStateVar> operator()(states_player::Idle&, const BeganMovingEvent& e)
    {
        //return states_player::Moving{};
        return states_player::Moving{ };
    }

    std::optional<PlayerStateVar> operator()(states_player::Moving&, const StoppedMovingEvent& e)
    {

        return states_player::Idle{ };
    }

    std::optional<PlayerStateVar> operator()(states_player::Moving&, const BeganShootingEvent& e)
    {

        return states_player::MovingAndShooting{ };
    }
    std::optional<PlayerStateVar> operator()(states_player::Moving&, const JumpEvent& e)
    {

        return states_player::RisingAndMoving{ };
    }
    std::optional<PlayerStateVar> operator()(states_player::Rising&, const BeganMovingEvent& e)
    {

        return states_player::RisingAndMoving{ };
    }

    std::optional<PlayerStateVar> operator()(states_player::RisingAndMoving&, const StoppedMovingEvent& e)
    {

        return states_player::Rising{ };
    }



    std::optional<PlayerStateVar> operator()(states_player::FallingAndMoving&, const StoppedMovingEvent& e)
    {

        return states_player::Falling{ };
    }

    std::optional<PlayerStateVar> operator()(states_player::FallingAndMoving&, const LandedEvent& e)
    {

        return states_player::Moving{ };
    }

    std::optional<PlayerStateVar> operator()(states_player::RisingAndMoving&, const BeganShootingEvent& e)
    {

        return states_player::RisingAndMovingAndShooting{ };
    }

    std::optional<PlayerStateVar> operator()(states_player::Falling&, const BeganMovingEvent& e)
    {

        return states_player::FallingAndMoving{ };
    }




    std::optional<PlayerStateVar> operator()(states_player::RisingAndMoving&, const ReachedJumpPeakEvent& e)
    {

        return states_player::FallingAndMoving{};
        ///  (--jumpHeightCurrent < Rising::JumpHeightMax)
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


    std::optional<PlayerStateVar> operator()(states_player::Idle&, const BeganShootingEvent& e)
    {
        
        return states_player::Shooting{ };
    }


    std::optional<PlayerStateVar> operator()(states_player::Rising&, const BeganShootingEvent& e)
    {

        return states_player::RisingAndShooting{};
    }

    
    std::optional<PlayerStateVar> operator()(states_player::Shooting&, const StoppedShootingEvent& e)
    {

        return states_player::Idle{ };
    }

    std::optional<PlayerStateVar> operator()(states_player::Shooting&, const BeganMovingEvent& e)
    {

        return states_player::MovingAndShooting{};
    }


    std::optional<PlayerStateVar> operator()(states_player::RisingAndMovingAndShooting&, const StoppedShootingEvent& e)
    {

        return states_player::RisingAndMoving{ };

    }
    std::optional<PlayerStateVar> operator()(states_player::RisingAndMovingAndShooting&, const StoppedMovingEvent& e)
    {

        return states_player::RisingAndShooting{ };

    }
    std::optional<PlayerStateVar> operator()(states_player::RisingAndMovingAndShooting&, const ReachedJumpPeakEvent& e)
    {

        return states_player::FallingAndMovingAndShooting{ };

    }


    std::optional<PlayerStateVar> operator()(states_player::FallingAndMovingAndShooting&, const StoppedShootingEvent& e)
    {

        return states_player::FallingAndMoving{ };

    }
    std::optional<PlayerStateVar> operator()(states_player::FallingAndMovingAndShooting&, const StoppedMovingEvent& e)
    {

        return states_player::FallingAndShooting{ };

    }
    std::optional<PlayerStateVar> operator()(states_player::FallingAndMovingAndShooting&, const LandedEvent& e)
    {

        return states_player::MovingAndShooting{ };

    }



    std::optional<PlayerStateVar> operator()(states_player::FallingAndMoving&, const BeganShootingEvent& e)
    {

        return states_player::FallingAndMovingAndShooting{ };
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name=""></param>
    /// <param name="e"></param>
    /// <returns></returns>
    std::optional<PlayerStateVar> operator()(states_player::FallingAndShooting&, const StoppedShootingEvent& e)
    {

        return states_player::Falling{ };
    }


  

    std::optional<PlayerStateVar> operator()(states_player::RisingAndShooting&, const StoppedShootingEvent& e)
    {

        return states_player::Rising{ };
    }

 


    std::optional<PlayerStateVar> operator()(states_player::RisingAndShooting&, const ReachedJumpPeakEvent& e)
    {

        return states_player::FallingAndShooting{ };
    }


    std::optional<PlayerStateVar> operator()(states_player::MovingAndShooting&, const StoppedShootingEvent& e)
    {

        return states_player::Moving{ };
    }

    std::optional<PlayerStateVar> operator()(states_player::MovingAndShooting&, const StoppedMovingEvent& e)
    {

        return states_player::Shooting{ };
    }
    std::optional<PlayerStateVar> operator()(states_player::MovingAndShooting&, const JumpEvent& e)
    {

        return states_player::RisingAndMovingAndShooting{ };
    }

    ///




  


    // default
    template<typename State, typename Event>
    std::optional<PlayerStateVar> operator()(State&, const Event&) const
    { return std::nullopt; }

};



class Sprite;
using Player_FSM = FSM<PlayerStateVar, EventVar, PlayerTransitions>;

class Player {
public:
    bool startOfShot{ false };
    float shotTimer{ 0.f };
    sf::Clock animTimer{};
    float animDelay{ 0.f };
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
    bool alive{ true };

    // logic for how the player interacts with the system defined in this function
    // as you are aware the correct state the user is in, and can code for that specific state logic, while being able to
    // change the state correctly by dispathing events to the playerFSM
    void update(const sf::Time& l_dt);
    bool isAlive();
    void render(sf::RenderWindow& l_wnd); 
    void finalize();

};

void update(Player& player, const sf::Time& deltaTime);
bool isAlive(Player& player);
void render(Player& player, sf::RenderWindow& window);


#endif
