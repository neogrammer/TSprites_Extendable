#pragma once
#include <variant>
namespace states_player {
	struct Idle {};


	struct Rising {};

	
	struct Falling {};
}

using PlayerStateVar = std::variant<states_player::Idle, states_player::Rising, states_player::Falling>;