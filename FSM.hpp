#pragma once
#include <string>

template <typename StateVariant, typename EventVariant, typename Transitions>
class FSM {
	StateVariant state_;
public:
	
	void dispatch(const EventVariant& evt)
	{
		std::optional<StateVariant> newstate = std::visit(Transitions{}, state_, evt);
		if (newstate)
		{
			state_ = *std::move(newstate);
		}
	}
	

};


template<typename Fsm, typename... Events>
void dispatch(Fsm& fsm, Events&&... evts)
{
	// need to dispatch all events in the list via the fsm.dispatch function
	
	(fsm.dispatch(std::forward<Events>(evts)...));
}

