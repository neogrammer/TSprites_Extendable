#pragma once
#include <variant>
struct JumpEvent { 	int jump = 0;  };
struct ReachedJumpPeakEvent { int gravity = 0; };
struct LandedEvent {};

struct FillerEvent {};

using EventVar = std::variant<JumpEvent, ReachedJumpPeakEvent, LandedEvent>;