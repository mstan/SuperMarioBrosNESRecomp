// semcomp/semcomp.h — Semantic-recompilation layer umbrella include.
//
// See docs/SEMCOMP.md for design and phased migration plan.
//
// Phase 0: compile-only facade. Every accessor delegates to the nesrecomp
// runtime state (g_ram, g_cpu). No writes, no behavior changes.
#pragma once

#define SMB_SEMCOMP_VERSION_MAJOR 0
#define SMB_SEMCOMP_VERSION_MINOR 1
#define SMB_SEMCOMP_PHASE         0  // 0 = scaffold

#include "semcomp/GameState.h"
#include "semcomp/Mario.h"
#include "semcomp/Level.h"
#include "semcomp/Camera.h"
#include "semcomp/ModApi.h"
#include "semcomp/SemcompGame.h"

namespace smb::semcomp {

// Exercises every accessor once. Returns true iff every read returned a
// value of its declared width without crashing. Not called by the runner in
// Phase 0; existence is a compile/link check that the facade is well-formed.
bool selftest();

}  // namespace smb::semcomp
