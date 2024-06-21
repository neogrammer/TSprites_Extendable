#pragma once
#include <string>

template <typename StateVariant, typename EventVariant, typename Transitions>
class FSM {
	StateVariant state_;

public:
	float posx{ 40.f }, posy{ 100.f }, velx{ 0.f }, vely{ 0.f };
	float width{ 84.f }, height{ 84.f }, jumpHeight{ 0.f }, jumpHeightMax{ 300.f };
	float maxY{ 500.f }, gravity{ 0.0f }, maxGravity{ 980.f };
	float runSpd{ 2.6f }, maxRunSpd{ 200.f };
	float dt{ 0.f };

public:
	
	void dispatch(const EventVariant& evt)
	{
		std::optional<StateVariant> newState = std::visit(Transitions{}, state_, evt);
		if (newState)
		{
			state_ = *std::move(newState);
		}
	}
	
	template<typename X>
	bool isType(X tmp)
	{
		if (std::holds_alternative<X>(state_)) {
			return true;
		}
		else
		{
			return false;
		}

	}
};


template<typename Fsm, typename... Events>
void dispatch(Fsm& fsm, Events&&... evts)
{
	// need to dispatch all events in the list via the fsm.dispatch function
	(fsm.dispatch(std::forward<Events>(evts)), ...);
}

