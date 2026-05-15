// semcomp/Level.cpp — Level facade. Phase 0 placeholder; see Level.h.
#include "semcomp/Level.h"

// Intentionally empty: every method is inline in the header for Phase 0.
// This translation unit exists so future phase-1 accessors can be added
// without changing CMakeLists.txt.

namespace smb::semcomp {

// Anchor symbol so the linker keeps this TU when the class has only
// inline methods. Removed when phase-1 adds real accessors.
extern "C" void smb_semcomp_level_link_anchor() {}

}  // namespace smb::semcomp
