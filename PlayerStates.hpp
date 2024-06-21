#pragma once
#include <variant>
namespace states_player {
	struct Idle {};


	struct Rising {
		int jumpForce{ 0 };
		Rising()
			: jumpForce{ 0 }
		{}

		Rising(int l_jumpForce)
			: jumpForce{ l_jumpForce }
		{}

		int& getJumpForce()
		{
			return jumpForce;
		}
	};

	struct Falling {

		int gravity{ 0 };
		Falling()
			: gravity{ 0 }
		{}

		Falling(int l_gravity)
			: gravity{ l_gravity }
		{}

		int& getJumpForce()
		{
			return gravity;
		}
	};
}

using PlayerStateVar = std::variant<states_player::Idle, states_player::Rising, states_player::Falling>;