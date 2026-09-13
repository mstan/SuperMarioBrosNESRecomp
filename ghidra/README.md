# Ghidra analysis

Ghidra is optional for building and playing the game. Keep `.gpr` projects,
`.rep` databases, and project locks local; Git ignores them. Removing these
files from Git tracking does not delete an existing local analysis database.

Share human-authored analysis as `annotations/*.annotations.json`, together
with the ROM revision and import/rebuild instructions. Do not commit the
database or ROM. The source-controlled [`symbols.sym`](../symbols.sym) is also
available for named ROM/RAM addresses.

On the maintainer's configured headless Ghidra MCP server, use `registry_list`
to discover the NES program, then `registry_open` to open it read-only. Do not
launch another Ghidra instance to bypass a project lock.

Before deleting a local database, preserve its human annotations and verify
that the source binary still exists. RAM captures may be irreplaceable.
