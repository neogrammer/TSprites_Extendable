#pragma once
#include <variant>
namespace states_player {
	struct Idle {};


	struct Rising {};


	struct Falling {};


	struct Moving {};


	struct Shooting {};

	struct MovingAndShooting {};


	struct RisingAndMoving {};
	struct FallingAndMoving {};

	struct RisingAndShooting {};
	struct FallingAndShooting {};

	struct RisingAndMovingAndShooting {};
	struct FallingAndMovingAndShooting {};
}

using PlayerStateVar = std::variant<states_player::Idle, states_player::Rising, states_player::Falling, states_player::Moving, states_player::MovingAndShooting, states_player::RisingAndMoving, states_player::FallingAndMoving, states_player::FallingAndShooting, states_player::RisingAndMovingAndShooting, states_player::FallingAndMovingAndShooting, states_player::Shooting, states_player::RisingAndShooting>;