// semcomp/semcomp.h — Semantic-recompilation layer umbrella include.
//
// See docs/SEMCOMP.md for design and phased migration plan.
#pragma once

#define SMB_SEMCOMP_VERSION_MAJOR 0
#define SMB_SEMCOMP_VERSION_MINOR 2
#define SMB_SEMCOMP_PHASE         1  // 1 = Mario-as-object reads

#include "semcomp/Camera.h"
#include "semcomp/GameState.h"
#include "semcomp/Level.h"
#include "semcomp/Mario.h"
#include "semcomp/ModApi.h"
#include "semcomp/PlayerSession.h"
#include "semcomp/SemcompGame.h"

namespace smb::semcomp {

// Exercises every accessor once. Returns true iff every read returned a
// value of its declared width without crashing. Not called by the runner;
// existence is a compile/link check that the facade is well-formed.
bool selftest();

}  // namespace smb::semcomp
