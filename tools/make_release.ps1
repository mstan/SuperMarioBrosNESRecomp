<#
Build the single Windows release ZIP with the source-controlled mod catalog.
Fresh profiles use Widescreen (Experimental), adaptive Fit to screen. The ZIP
contains no mods/state.toml, so updating preserves explicit player selections.
The stock view remains available by disabling Widescreen in Mods.
Usage: powershell -File tools/make_release.ps1 [-BuildDir DIR] [-SkipBuild]
Variant is retained as a deprecated compatibility argument; every value emits
the same single Windows archive. No ROM, save, owner cache or dev config ships.
#>
param(
  [ValidateSet('standard', 'widescreen', 'both')]
  [string]$Variant = 'standard',
  [string]$BuildDir = 'build_release',
  [switch]$SkipBuild
)
$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $PSScriptRoot
$buildRoot = if ([IO.Path]::IsPathRooted($BuildDir)) { [IO.Path]::GetFullPath($BuildDir) } else { Join-Path $root $BuildDir }
$bin  = $buildRoot
if (-not (Test-Path (Join-Path $bin 'SuperMarioBrosRecomp.exe')) -and
    (Test-Path (Join-Path $buildRoot 'Release\SuperMarioBrosRecomp.exe'))) {
  $bin = Join-Path $buildRoot 'Release'
}
$out  = Join-Path $root 'release'
New-Item -ItemType Directory -Force $out | Out-Null

if (-not $SkipBuild) {
  & (Join-Path $root 'tools/build.ps1') -BuildDir $BuildDir
}

$exe = Join-Path $bin 'SuperMarioBrosRecomp.exe'
if (-not (Test-Path $exe)) { throw "missing $exe -- run build_all.bat first" }
$cmakeCache = Join-Path $buildRoot 'CMakeCache.txt'
if (-not (Test-Path $cmakeCache)) { throw "missing $cmakeCache -- run build_all.bat first" }
$traceSetting = Select-String -LiteralPath $cmakeCache -Pattern '^NESRECOMP_ENABLE_TRACE:BOOL=OFF$'
if (-not $traceSetting) {
  throw 'refusing to package a Windows build with NESRECOMP_ENABLE_TRACE enabled or unset'
}
$cycleBuild = Select-String -LiteralPath $cmakeCache -Pattern '^NESRECOMP_BACKEND:STRING=cycle$'
if (-not $cycleBuild) { throw 'release packaging requires the default cycle backend' }
$mingwRuntimeFiles = @('libgcc_s_seh-1.dll', 'libstdc++-6.dll', 'libwinpthread-1.dll')
$cacheText = Get-Content -LiteralPath $cmakeCache -Raw
$shaderSetting = [regex]::Match($cacheText, '(?m)^NESRECOMP_SHADER_PRESET_DIR:PATH=([^\r\n]*)')
$shaderPresetSource = $shaderSetting.Groups[1].Value
$shaderAssets = @()
if ($shaderPresetSource) {
  $shaderAssets += 'README.md'
  foreach ($preset in 'crt-soft', 'lcd-grid', 'sharp', 'warm-composite') {
    $shaderAssets += "$preset.glslp"
    $shaderAssets += "_passes/$preset-pass.glsl"
  }
}
$compilerSetting = [regex]::Match($cacheText, '(?m)^CMAKE_CXX_COMPILER:[^=]+=(.*)\r?$')
$compilerRuntimeDir = if ($compilerSetting.Success) { Split-Path -Parent $compilerSetting.Groups[1].Value.TrimEnd("`r") } else { '' }
$hasMingwRuntimes = $compilerRuntimeDir -and (Test-Path -LiteralPath (Join-Path $compilerRuntimeDir 'libstdc++-6.dll') -PathType Leaf)
$engineSetting = [regex]::Match($cacheText, '(?m)^NESRECOMP_ROOT:[^=]+=(.*)\r?$')
$uiSetting = [regex]::Match($cacheText, '(?m)^NESRECOMP_RECOMP_UI:[^=]+=(.*)\r?$')
$engineRoot = if ($engineSetting.Success) { $engineSetting.Groups[1].Value.TrimEnd("`r") } else { Join-Path $root 'nesrecomp' }
$uiRoot = if ($uiSetting.Success) { $uiSetting.Groups[1].Value.TrimEnd("`r") } else { Join-Path $root 'recomp-ui' }
$readmeCommon = @'
Super Mario Bros. - Static Recompilation
=========================================

A native PC build of Super Mario Bros., produced by statically
recompiling the NES ROM's 6502 code to C with the NESRecomp framework
(github.com/mstan/nesrecomp).

No ROM is included. On first launch, select your legally-obtained
Super Mario Bros. (World) ROM (PRG+CHR CRC32 D445F698). The path is remembered
for future launches.

The Super Smash Bros. 64 player-replacement mod includes Captain Falcon and
Pikachu, but remains disabled until you select a legally-owned Super Smash Bros.
(USA), NTSC-U v1.0 ROM in the Mods screen. That ROM is verified locally and is
never included in this package. The first launch derives each selected fighter's
model, animations, effects, and audio into your local user cache; those
generated files are not shipped.

Simultaneous Co-op is available in Mods > Gameplay and is disabled by default.
Choose 2, 3, or 4 players: Mario, Luigi, Wario, and Waluigi. Assign each player's
keyboard or gamepad in Controls. Co-op uses a shared 4:3 camera, shared resources,
and team lives. Dead players return at the next level or team retry.
Co-op is mutually exclusive with Free Backtracking, widescreen, Voxel 3D, and all character
replacement mods. Enabling co-op replaces those conflicting selections.

Experimental character replacement mods are default-off and mutually exclusive.
Samus requires a verified Metroid ROM, Link requires a verified Zelda II ROM,
and Sonic requires a verified Sonic 3 & Knuckles Genesis ROM. The launcher Mods
screen handles these owner-ROM pickers and verification gates; no owner ROM data
or derived owner-ROM graphics are shipped in this package.

Controls: arrow keys = D-Pad, Z = A, X = B, Enter = Start,
Backslash = Select. Escape opens the menu. F8 saves the current state;
F9 loads it. Alt+Enter toggles fullscreen. Configure every player's
keyboard or gamepad in the launcher or menu; settings live in config.ini.
The cycle CPU is the default, with NTSC timing for this USA/World title.

Online play: host or join a room from the launcher. Two to four seats use
the host's co-op selection. The menu does not pause an online match;
load states and changing mods are unavailable during a match.

Modern HD: convert your locally supplied LyonHrt pack with
smb_hdpack_importer.exe --pack PACK_DIRECTORY --rom SMB_ROM --out HD.nesmod
Then install HD.nesmod in the launcher's Mods screen. No textures or ROM
are included. This HD mod is for local play.

Widescreen (Experimental) is available in Mods: adaptive Fit, 16:9, 21:9,
and 32:9, with original enemy activation or movement on load. Fresh profiles
enable adaptive Fit to screen. Disable it in Mods for the original view; updates
preserve explicit saved selections. The camera anchors at area edges and centers small
fixed rooms; Mods also offers the previous centered camera. Special objects and linked balance platforms
still have native limits; this has not been validated through every world.
Experimental mod savestates are not compatible across all builds.

Free Backtracking is enabled for fresh profiles. In single-player Mario or Luigi
play, the camera follows travel left and right within the current area. Coins,
changed blocks, earned checkpoints and defeated ordinary enemies retain progress;
distant ordinary enemies sleep and resume when revisited. Disable it separately
in Mods for the original one-way scrolling. It also works with the original 4:3
view. Fixed pipe rooms and scripted transitions keep their original bounds.
Updates preserve an explicit saved Off choice. Whole-world coverage is incomplete.
'@

function Assert-ReleaseStage([string]$stage, [string]$sourceMods, [string[]]$DependencyNotices) {
  $files = @(Get-ChildItem $stage -Recurse -File)
  $relativeFiles = @($files | ForEach-Object { Get-StageRelativePath $stage $_.FullName })

  $required = @(
    'SuperMarioBrosRecomp.exe',
    'falcon_owner_assets.exe',
    'smb_hdpack_importer.exe',
    'SDL2.dll',
    'README.txt',
    'licenses/Game-LICENSE.txt',
    'licenses/Game-PERMISSIONS.md',
    'licenses/NESRecomp-LICENSE.txt',
    'licenses/SDL2-COPYING.txt',
    'licenses/ImGui-LICENSE.txt',
    'THIRD-PARTY-LICENSES/README.md',
    'third_party/ymfm/LICENSE'
  )
  $required += @($DependencyNotices | ForEach-Object { "licenses/$_" })
  $missing = @($required | Where-Object { $_ -notin $relativeFiles })
  if ($missing.Count -ne 0) {
    throw "release staging is missing required payload: $($missing -join ', ')"
  }

  $requiredAssets = @(
    'assets/fonts/LatoLatin-Bold.ttf',
    'assets/fonts/LatoLatin-Regular.ttf',
    'assets/fonts/NotoSansSymbols2-Regular.ttf',
    'assets/fonts/OpenMoji-black-glyf.ttf',
    'assets/img/boxart.tga',
    'assets/img/brand_mark.tga',
    'assets/img/brand_nes.tga',
    'assets/img/flags.png',
    'assets/img/pad_nes.tga',
    'assets/img/verdict_bad.tga',
    'assets/img/verdict_none.tga',
    'assets/img/verdict_ok.tga',
    'assets/img/verdict_warn.tga'
  )
  foreach ($shader in $shaderAssets) {
    $relative = "assets/shaders/$shader"
    $requiredAssets += $relative
    $sourceShader = Join-Path $shaderPresetSource $shader
    $stagedShader = Join-Path $stage $relative
    if (-not (Test-Path -LiteralPath $sourceShader -PathType Leaf) -or
        -not (Test-Path -LiteralPath $stagedShader -PathType Leaf)) {
      throw "release staging is missing bundled shader: $relative"
    }
    if ((Get-FileHash -LiteralPath $sourceShader -Algorithm SHA256).Hash -ne
        (Get-FileHash -LiteralPath $stagedShader -Algorithm SHA256).Hash) {
      throw "release staging changed bundled shader: $relative"
    }
  }
  $stagedAssets = @($relativeFiles | Where-Object { $_ -like 'assets/*' })
  $assetDifference = @(Compare-Object $requiredAssets $stagedAssets)
  if ($assetDifference.Count -ne 0) {
    throw 'release staging launcher asset inventory differs from the approved NES launcher assets'
  }

  # This is deliberately an allowlist. It prevents a new build artifact from
  # becoming publishable merely because its name or extension was not yet
  # added to a denylist.
  $unexpected = @($relativeFiles | Where-Object {
    if ($_ -in $required) { return $false }
    if ($_ -in $requiredAssets) { return $false }
    if ($_ -in $mingwRuntimeFiles) { return $false }
    if ($_ -in @('msvcp140.dll','vcruntime140.dll','vcruntime140_1.dll','msvcp140_1.dll','msvcp140_2.dll','concrt140.dll','vccorlib140.dll','msvcp140_atomic_wait.dll','msvcp140_codecvt_ids.dll')) { return $false }
    if ($_ -match '^mods/packages/[^/]+/[^/]+/manifest\.toml$') { return $false }
    return $true
  })
  if ($unexpected.Count -ne 0) {
    throw "release staging contains forbidden owner/dev payload: $($unexpected -join ', ')"
  }

  # The staged catalog must be a byte-for-byte mirror of source-controlled
  # mods/preloaded. Player selections are never authored into an archive.
  $sourceManifestRoot = (Resolve-Path $sourceMods).Path
  $sourceManifests = @(Get-ChildItem $sourceManifestRoot -Recurse -File)
  if ($sourceManifests.Count -eq 0) { throw 'source preloaded mod catalog is empty' }
  $expectedModPaths = @()
  foreach ($source in $sourceManifests) {
    $relative = Get-StageRelativePath $sourceManifestRoot $source.FullName
    if ($relative -notmatch '^packages/[^/]+/[^/]+/manifest\.toml$') {
      throw "source preloaded catalog contains non-manifest payload: $relative"
    }
    $stagedRelative = "mods/$relative"
    $expectedModPaths += $stagedRelative
    $stagedPath = Join-Path $stage $stagedRelative.Replace('/', '\')
    if (-not (Test-Path -LiteralPath $stagedPath -PathType Leaf)) {
      throw "release staging is missing preloaded manifest: $stagedRelative"
    }
    if ((Get-FileHash -Algorithm SHA256 -LiteralPath $source.FullName).Hash -ne
        (Get-FileHash -Algorithm SHA256 -LiteralPath $stagedPath).Hash) {
      throw "release staging modified preloaded manifest: $stagedRelative"
    }
  }
  foreach ($packageId in 'nesrecomp.developer.replay', 'nesrecomp.twitch-chat') {
    $relative = "mods/packages/$packageId/1.0.0/manifest.toml"
    $generated = Join-Path $bin $relative
    $packaged = Join-Path $stage $relative
    if (-not (Test-Path -LiteralPath $generated -PathType Leaf) -or
        -not (Test-Path -LiteralPath $packaged -PathType Leaf) -or
        (Get-FileHash -LiteralPath $generated).Hash -ne (Get-FileHash -LiteralPath $packaged).Hash) {
      throw "Missing or changed generated framework manifest: $packageId"
    }
    $expectedModPaths += $relative
  }
  $stagedModPaths = @($relativeFiles | Where-Object { $_ -like 'mods/*' })
  $modDifference = @(Compare-Object $expectedModPaths $stagedModPaths)
  if ($modDifference.Count -ne 0) {
    throw "release staging mod inventory differs from pristine mods/preloaded"
  }

  # Reject machine-local absolute paths in every text payload, even when the
  # file itself has an otherwise permitted release name.
  foreach ($file in $files | Where-Object { $_.Extension -in '.txt', '.ini', '.toml' }) {
    $text = Get-Content -Raw -LiteralPath $file.FullName
    if ($text -match '(?im)(?:(?<![a-z0-9_])[a-z]:[\\/]|/(?:home|users|tmp)/)') {
      throw "release text contains a machine-local absolute path: $(Get-StageRelativePath $stage $file.FullName)"
    }
  }
}


$extra = @{
    'falcon_owner_assets.exe' = (Join-Path $bin 'falcon_owner_assets.exe')
    'smb_hdpack_importer.exe' = (Join-Path $bin 'smb_hdpack_importer.exe')
    'THIRD-PARTY-LICENSES/README.md' = (Join-Path $root 'THIRD-PARTY-LICENSES/README.md')
    'third_party/ymfm/LICENSE' = (Join-Path $root 'third_party/ymfm/LICENSE')
    'licenses/Game-PERMISSIONS.md' = (Join-Path $root 'PERMISSIONS.md')
}
$check = { param($stage,$notices) Assert-ReleaseStage $stage (Join-Path $root 'mods/preloaded') $notices }
& (Join-Path $engineRoot 'tools/package_cycle_windows.ps1') -ProjectRoot $root -Target SuperMarioBrosRecomp -Title 'Super Mario Bros.' -BuildDir $buildRoot -SkipBuild -ArchiveName 'SuperMarioBrosRecomp-windows-x64.zip' -ReadmeText $readmeCommon -AdditionalFiles $extra -ValidateStage $check
