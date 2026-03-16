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

## RESOLVED: Piranha plant half-renders / despawns in widescreen margin

**Location:** World 1-2 warp zone area (and likely all piranha plant pipes)

**Symptoms (before fix):**
1. From far away, piranha plant is fully visible in the 16:9 right margin
   via sprite runahead (see `piranha_15_far_visible.png`)
2. As Mario approaches, the piranha plant HALF disappears — partially
   rendered (see `piranha_16_half_rendered.png`)
3. Stepping back does NOT restore the full rendering — it stays half-rendered
4. Getting even closer, the first piranha plant disappears entirely, but a
   SECOND piranha plant further out is visible at the margin edge
   (see `piranha_18_closer_still_gone.png`)

**Root cause:**
The sprite runahead shifts the camera +256px (one page) by incrementing
ScreenLeft_PageLoc ($071A) and ScreenRight_PageLoc ($071B).  The enemy
bounds check at $D67A-$D6D5 computes a keep-alive zone from
ScreenLeft-72px to ScreenRight+72px.  During runahead, the shifted left
boundary is 256px further right than the real frame's — so enemies in
the real frame's 4:3 viewport fall outside the shifted left boundary and
get deactivated via JSR $C998 (zeros 8 enemy fields: $0F+X, $16+X,
$1E+X, $0110+X, $0796+X, $0125+X, $03C5+X, $078A+X).

The deactivated enemies have no OAM sprites, so the extended OAM capture
captures nothing for them.  Although RAM is restored after the runahead,
the damage is done — the extended OAM already missed the sprites.

**Fix:** PC-gated `ram_read_hook` at $D693 (LDA $071A in bounds check
left boundary computation).  During `g_runahead_mode`, returns
`(val > 0) ? val - 1 : val`, restoring the real frame's left boundary.

**Files changed:**
- `game.cfg`: added `ram_read_hook 071A` (plus 071B/071C/071D for future)
- `extras.c`: `game_ram_read_hook()` with PC=$D693 check during runahead
- `nesrecomp` submodule: merged ram_read_hook feature from origin/master

**Verified:** World 1-2 piranha plants remain visible in the widescreen
right margin as Mario approaches.  The hook fires correctly (confirmed
via debug logging: "page 1 -> 0" during runahead frames).

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
