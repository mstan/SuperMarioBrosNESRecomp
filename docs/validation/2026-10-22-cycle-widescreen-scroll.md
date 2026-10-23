# Cycle widescreen scroll-page correction

Central Beads: `beads-2dw.2.15`. Owner reported repeated pipes, cut hills and
cloud seams in the World 1-1 Fit playtest. The reference captures also contain
the defect; reference/candidate equality had preserved a pre-existing bug.

`runtime_get_visible_frame_start` returned captured PPUCTRL bit 0 beside the
low eight bits of the rendered scroll. SMB can select a different nametable
through its address/scroll writes, so PPUCTRL is not the rendered page. At the
reproduction point the game camera is 483 but the compositor calculated 227,
placing the extended world 256 pixels away from the native picture.

The cycle bridge now derives the page from the complete captured 9-bit X
scroll. Other control bits, the Y result and all simulation code are unchanged.
On the qualified pilot revision (`88424dd`), this adapter is consumed only by
the widescreen renderer.

Targeted qualification, not a renewed performance/campaign matrix:

- A 200-frame replay through the crossing has identical full guest/hardware
  trace, native framebuffer, PCM and complete serialized guest/mod state
  before/after the fix. The extended presentation changes as intended.
- At frame 1200, camera 483 now renders at 483. The existing seam diagnostic
  falls from 1,145 background-coverage mismatches to zero out of 6,656 samples.
  Before/after images were inspected: terrain and clouds join continuously.
- Hidden/muted actual SDL/game-UI reproduction at the owner's 1659x720 window
  (554-pixel Fit canvas), current-build save/load/save and repeated rendering
  pass. Resize to 1280x720 (426 pixels) retains zero seam errors; returning to
  1659x720 reproduces the exact original corrected image.

Private evidence is under
`G:/Temp/Codex/nesrecomp/accuracy-perf-20261022/smb1-widescreen/`, including the
owner screenshot, `phase1200/before.*`, `phase1200/after.*`, and `fixed/`.
The preserved reference and candidate builds reproduce the same early phase.
The existing captured reference at frame 1200 shows the faulty seam.

SMB3 passed owner QA. The owner then accepted the corrected SMB1 presentation
and explicitly approved integration on 2026-10-23.

Current master already contains `072cd2d`, which reads the complete captured
scroll directly in the renderer. That active fix is preserved; the approved
bridge correction keeps the adapter consistent as well. Existing renderer
defaults and the recomp-ui pin are unchanged. The framework pin includes the
approved performance bundle; no new performance claim is made for the current
Windows HLE default.
