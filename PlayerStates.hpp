#pragma once
#include <variant>
namespace states_player {
	struct Idle {};


	struct Rising {};

	
	struct Falling {};

	struct MovingLeft {};
	struct RisingAndMovingLeft {};
	struct FallingAndMovingLeft {};
	struct MovingRight {};
	struct RisingAndMovingRight {};
	struct FallingAndMovingRight {};
	struct Shooting {};
	struct MovingLeftAndShooting {};
	struct MovingRightAndShooting {};
	struct RisingAndShooting {};
	struct FallingAndShooting {};
	struct RisingAndMovingLeftAndShooting {};
	struct FallingAndMovingLeftAndShooting {};
	struct RisingAndMovingRightAndShooting {};
	struct FallingAndMovingRightAndShooting {};
}

using PlayerStateVar = std::variant<states_player::Idle, states_player::Rising, states_player::Falling, states_player::MovingLeft, states_player::RisingAndMovingLeft
 , states_player::FallingAndMovingLeft, states_player::MovingRight, states_player::RisingAndMovingRight, states_player::FallingAndMovingRight, states_player::Shooting
	, states_player::MovingLeftAndShooting, states_player::MovingRightAndShooting, states_player::RisingAndShooting, states_player::FallingAndShooting
	, states_player::RisingAndMovingLeftAndShooting, states_player::FallingAndMovingLeftAndShooting, states_player::RisingAndMovingRightAndShooting
	, states_player::FallingAndMovingRightAndShooting>;