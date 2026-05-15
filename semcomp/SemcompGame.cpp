// semcomp/SemcompGame.cpp — anchor TU for the SemcompGame facade.
#include "semcomp/SemcompGame.h"

namespace smb::semcomp {

// Anchor symbol so the linker keeps this TU when SemcompGame is header-only
// in Phase 0. Removed once SemcompGame gains out-of-line methods in Phase 2.
extern "C" void smb_semcomp_game_link_anchor() {}

}  // namespace smb::semcomp
