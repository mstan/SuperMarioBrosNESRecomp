<#
make_release.ps1 — build the dual-zip release assets.

Every release ships TWO windows zips (never a bare exe — the exe needs
SDL2.dll):

  standard    SuperMarioBrosRecomp-windows-x64.zip
              No widescreen.ini — boots the authentic 4:3 game.

  widescreen  SuperMarioBrosRecomp-widescreen-windows-x64.zip
              Same exe plus widescreen.ini (enabled, 16:9). Widescreen
              is runtime-gated config: with the ini absent or disabled
              the binary is exactly the standard game (the --verify
              oracle gate runs byte-identical with widescreen off), so
              both zips share one build.

The script builds build_release\ via build_all.bat (plain regen, oracle
OFF, reverse-debug OFF), then stages and zips. Zips land in release\
(gitignored). Neither zip ever contains debug.ini or a ROM.

Publish AFTER smoke-testing both zips from a scratch directory:

  gh release create vX.Y.Z release\SuperMarioBrosRecomp-windows-x64.zip `
      release\SuperMarioBrosRecomp-widescreen-windows-x64.zip `
      --title "vX.Y.Z — <headline>" --notes-file <notes.md>

Usage: powershell -File tools\make_release.ps1 [-Variant standard|widescreen|both] [-SkipBuild]
#>
param(
  [ValidateSet('standard', 'widescreen', 'both')]
  [string]$Variant = 'both',
  [switch]$SkipBuild
)
$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $PSScriptRoot
$bin  = Join-Path $root 'build_release'
$out  = Join-Path $root 'release'
New-Item -ItemType Directory -Force $out | Out-Null

if (-not $SkipBuild) {
  & cmd /c (Join-Path $root 'build_all.bat')
  if ($LASTEXITCODE -ne 0) { throw "build_all.bat failed ($LASTEXITCODE)" }
}

$exe = Join-Path $bin 'SuperMarioBrosRecomp.exe'
if (-not (Test-Path $exe)) { throw "missing $exe — run build_all.bat first" }

$readmeCommon = @'
Super Mario Bros. - Static Recompilation
=========================================

A native PC build of Super Mario Bros., produced by statically
recompiling the NES ROM's 6502 code to C with the NESRecomp framework
(github.com/mstan/nesrecomp).

No ROM is included. On first launch, select your legally-obtained
Super Mario Bros. (World) ROM (CRC32 3337EC46). The path is remembered
for future launches.

Controls: arrow keys = D-Pad, Z = A, X = B, Enter = Start,
Right Shift = Select. F5 turbo, F6 save state, F7 load state,
F11 / Alt+Enter fullscreen. Gamepads are supported; bindings are
configurable in keybinds.ini.
'@

$readmeWidescreen = @'

WIDESCREEN (EXPERIMENTAL)
-------------------------
This variant ships with 16:9 widescreen enabled via widescreen.ini.
Widescreen is EXPERIMENTAL AND BUGGY: enemy spawn timing differs
slightly from the vanilla timeline, and sprite glitches in the widened
margins are still being found. See WIDESCREEN.md in the source repo
for details.

Delete widescreen.ini (or set enabled = 0) to get the standard 4:3
game; you can also pass --widescreen 16:9, --widescreen <L>x<R>, or
--widescreen off on the command line.
'@

function New-ReleaseZip([string]$kind) {
  $stage = Join-Path $out "stage_$kind"
  if (Test-Path $stage) { Remove-Item -Recurse -Force $stage }
  New-Item -ItemType Directory -Force $stage | Out-Null

  Copy-Item $exe $stage
  foreach ($extra in 'SDL2.dll', 'keybinds.ini') {
    $p = Join-Path $bin $extra
    if (Test-Path $p) { Copy-Item $p $stage }
  }

  if ($kind -eq 'widescreen') {
    "enabled = 1`r`naspect = 16:9`r`n" |
      Out-File -Encoding ascii (Join-Path $stage 'widescreen.ini') -NoNewline
    ($readmeCommon + $readmeWidescreen) |
      Out-File -Encoding ascii (Join-Path $stage 'README.txt')
    $zip = Join-Path $out 'SuperMarioBrosRecomp-widescreen-windows-x64.zip'
  } else {
    $readmeCommon | Out-File -Encoding ascii (Join-Path $stage 'README.txt')
    $zip = Join-Path $out 'SuperMarioBrosRecomp-windows-x64.zip'
  }

  # Belt-and-braces: never ship debug/dev artifacts.
  foreach ($banned in 'debug.ini', 'baserom.nes') {
    $p = Join-Path $stage $banned
    if (Test-Path $p) { Remove-Item $p }
  }

  if (Test-Path $zip) { Remove-Item $zip }
  Compress-Archive -Path (Join-Path $stage '*') -DestinationPath $zip
  Remove-Item -Recurse -Force $stage
  Write-Host "staged $zip"
}

if ($Variant -eq 'standard' -or $Variant -eq 'both') { New-ReleaseZip 'standard' }
if ($Variant -eq 'widescreen' -or $Variant -eq 'both') { New-ReleaseZip 'widescreen' }
