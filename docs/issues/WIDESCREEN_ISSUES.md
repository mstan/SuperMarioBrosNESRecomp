# Widescreen Issues Tracker

## RESOLVED: Ghost Mario in sprite runahead
**Commits:** `add1648`, `aace235`

The sprite runahead runs the full game engine with camera shifted +256px to
capture enemy sprites for the right widescreen margin.  The player also gets
rendered into this extended OAM, creating a "ghost Mario".

**Root cause:** Player rendering at $F176 uses pure 8-bit subtraction
(`SprObject_X - ScreenLeft_X`) with no page check.  During runahead, the
game's camera tracking code adjusts ScreenLeft_X, shifting the ghost's OAM X
to ~0 instead of the real frame's ~55.

**Fix:** Compute player's screen X from the RUNAHEAD state
(`g_ram[0x86] - g_ram[0x071C]`) and blank extended OAM sprites within
[-4, +20] of that X.  Uses uint8_t circular subtraction to avoid
signed-int wrapping bugs when player_sx is near 255/0.

---

## OPEN: Piranha plant half-renders / despawns in widescreen margin

**Location:** World 1-2 warp zone area (and likely all piranha plant pipes)

**Symptoms:**
1. From far away, piranha plant is fully visible in the 16:9 right margin
   via sprite runahead (see `piranha_15_far_visible.png`)
2. As Mario approaches, the piranha plant HALF disappears — partially
   rendered (see `piranha_16_half_rendered.png`)
3. Stepping back does NOT restore the full rendering — it stays half-rendered
4. Getting even closer, the first piranha plant disappears entirely, but a
   SECOND piranha plant further out is visible at the margin edge
   (see `piranha_18_closer_still_gone.png`)

**Analysis:**
There appears to be a de-rendering boundary between the 4:3 viewport edge
(X=256 from ScreenLeft) and the 16:9 right margin.  The game's own
off-screen enemy management code (likely `CheckRightBounds` at $C164 or
the 72px activation check at $D69A/$D6A1) deactivates/despawns enemies
when they cross certain screen X thresholds.

In 4:3 this is invisible — the enemy is already off-screen.  But in 16:9
widescreen, these entities are visible in the right margin.  Once the game
deactivates an enemy, it stays deactivated — the runahead also won't render
it because the runahead starts from the real frame's RAM (where the enemy
is already marked inactive).

**Key code locations to investigate:**
- `CheckRightBounds` at ~$C164: spawn threshold (ScreenRight + 48px)
  - Currently hooked in game_ram_read_hook but DISABLED (see comment in extras.c)
  - Was disabled because extending it causes 8-bit OAM X wrapping for enemies
    past X=255 from ScreenLeft
- $D69A/$D6A1: 72px activation/rendering check — used for enemy behavior,
  NOT just spawning.  Extending this caused reversed movement and X wrapping.
- Enemy state arrays: $001E-$0023 (Enemy_Flag), $0016-$001B (Enemy_ID)

**The fundamental problem:**
The game uses 8-bit sprite X coordinates (0-255).  Enemies beyond X=255
from ScreenLeft cannot be placed correctly in NES OAM.  The sprite runahead
works by shifting the camera +256px, which lets the NES engine render
enemies that would be at X=0-255 in that shifted view.  But the REAL
frame's game logic still deactivates enemies based on 4:3 bounds.

**Possible approaches:**
1. **Suppress enemy deactivation in the widescreen margin zone** — hook the
   off-screen check to extend the "active" zone by g_widescreen_right pixels.
   Risk: enemies might behave incorrectly if activated beyond 8-bit X range.
2. **Freeze enemy state for margin-zone entities** — prevent the real frame
   from deactivating enemies that are visible in the widescreen margin, while
   still letting the runahead render them.
3. **Use the runahead to also preserve enemy activation state** — after the
   runahead captures extended OAM, also note which enemies were active, and
   prevent the real frame from deactivating those specific slots.

---

## NOTED: 21:9 rolling wrap-around bug

21:9 ultrawide mode (560px, 152px margins) has a visual rolling/wrapping
artifact.  Not yet investigated.  Lower priority than 16:9 issues.

---

## NOTED: Flagpole flag not visible in 16:9 margin

The flagpole flag at the end of levels does not appear as an extended sprite
despite being within the 16:9 viewport.  May be related to the piranha plant
issue (sprite deactivation at 4:3 boundary) or could be a separate issue with
how the flagpole flag entity is managed.
