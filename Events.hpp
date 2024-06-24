#pragma once
#include <variant>
struct JumpEvent { 	int maxJumpHeigt;  };
struct ReachedJumpPeakEvent { };
struct LandedEvent {};

struct BeganMovingEvent {};
struct StoppedMovingEvent {};
struct BeganShootingEvent {};
struct StoppedShootingEvent {};
struct UpdateEvent { float l_dt; };  // special event that allows timed events to trigger themselves
struct CollidedEvent {};
struct OffStageEvent {};


using EventVar = std::variant<JumpEvent, ReachedJumpPeakEvent, LandedEvent, UpdateEvent, BeganShootingEvent, StoppedShootingEvent, CollidedEvent, OffStageEvent, BeganMovingEvent, StoppedMovingEvent>;