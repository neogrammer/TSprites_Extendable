#pragma once
#include <variant>
struct JumpEvent { 	int maxJumpHeigt;  };
struct ReachedJumpPeakEvent { };
struct LandedEvent {};

struct UpdateEvent { float l_dt; };  // special event that allows timed events to trigger themselves


using EventVar = std::variant<JumpEvent, ReachedJumpPeakEvent, LandedEvent, UpdateEvent>;