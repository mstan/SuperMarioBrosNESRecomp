param(
    [string]$Rom,
    [string]$BuildDir = 'build_release',
    [string]$EngineRoot,
    [string]$RecompUi,
    [ValidateSet('cycle','legacy')][string]$Backend = 'cycle',
    [switch]$LocalOnly
)
$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $PSScriptRoot
if (-not $EngineRoot) { $EngineRoot = Join-Path $root 'nesrecomp' }
if (-not $Rom) {
    foreach ($name in 'baserom.nes','Super Mario Bros. (USA).nes','Super Mario Bros. (World).nes') {
        $candidate = Join-Path $root $name
        if (Test-Path -LiteralPath $candidate -PathType Leaf) { $Rom = $candidate; break }
    }
}
if ($Backend -eq 'cycle' -and -not $Rom) { throw 'Supply -Rom with the original USA/World NTSC ROM path.' }
$net = if ($LocalOnly) { 'OFF' } else { 'ON' }
if ($Backend -ne 'cycle') { throw 'This build entry point uses host-native HLE.' }
$build = if ([IO.Path]::IsPathRooted($BuildDir)) { $BuildDir } else { Join-Path $root $BuildDir }
$flags=@('-DNESRECOMP_REQUIRE_FALCON_OWNER_HELPER=ON',"-DSMB_ENABLE_NETPLAY=$net")
& (Join-Path $EngineRoot 'tools/build_cycle_windows.ps1') -ProjectRoot $root -Rom $Rom -BuildDir $build -EngineRoot $EngineRoot -RecompUi $RecompUi -CMakeArgs $flags
