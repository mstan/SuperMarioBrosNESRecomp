# Repository agent notes

Owner instruction (2026-09-24): work solo in the SMB and NESRecomp co-op
worktrees. Use the pinned `smb-disassembly` as the source for original behavior.
The old framework "NO GHIDRA = NO ACTION" rule is obsolete. Use the configured
headless Ghidra MCP autonomously when useful; its availability must not block
work that can be verified from disassembly, ROM bytes, and runtime tests.
Never launch a Ghidra GUI or kill another Ghidra process.

Track this implementation in central Beads issue `beads-2dw.2.10`.

Owner instruction (2026-09-25): automated checks must not repeatedly open
Windows console windows or steal focus. Python subprocesses must use
`CREATE_NO_WINDOW` on Windows; scripted launcher checks use `LNG_TEST_HIDDEN=1`.
Only show the interactive launcher when returning a build for the owner to test.

## Silent Windows command execution (owner, 2026-09-25)

Run native tools through an explicit hidden process wrapper on Windows, with
UseShellExecute=false, CreateNoWindow=true, WindowStyle=Hidden, and redirected
stdout/stderr. This includes Git, build tools, Python, and Beads, not only test
executables. Invoke native executables directly instead of PowerShell/npm shims.
Do not open a terminal or steal focus. Interactive game windows are shown only
when the owner requests a launch.
