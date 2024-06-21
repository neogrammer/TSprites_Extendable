#pragma once
#include <variant>
struct JumpEvent { 	int maxJumpHeigt;  };
struct ReachedJumpPeakEvent { };
struct LandedEvent {};
struct BeganMovingLeftEvent {};
struct StoppedMovingLeftEvent {};
struct BeganMovingRightEvent {};
struct StoppedMovingRightEvent {};
struct BeganShootingEvent {};
struct StoppedShootingEvent {};
struct UpdateEvent { float l_dt; };  // special event that allows timed events to trigger themselves


using EventVar = std::variant<JumpEvent, ReachedJumpPeakEvent, LandedEvent, UpdateEvent, BeganMovingLeftEvent, StoppedMovingLeftEvent
, BeganMovingRightEvent, StoppedMovingRightEvent, BeganShootingEvent, StoppedShootingEvent>;