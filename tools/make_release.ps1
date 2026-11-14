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
$buildRoot = Join-Path $root $BuildDir
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
$engineSetting = [regex]::Match($cacheText, '(?m)^NESRECOMP_ROOT:[^=]+=(.*)\r?$')
$uiSetting = [regex]::Match($cacheText, '(?m)^NESRECOMP_RECOMP_UI:[^=]+=(.*)\r?$')
$engineRoot = if ($engineSetting.Success) { $engineSetting.Groups[1].Value.TrimEnd("`r") } else { Join-Path $root 'nesrecomp' }
$uiRoot = if ($uiSetting.Success) { $uiSetting.Groups[1].Value.TrimEnd("`r") } else { Join-Path $root 'recomp-ui' }
$releaseLicenses = @{
  'Game-LICENSE.txt' = (Join-Path $root 'LICENSE')
  'Game-PERMISSIONS.md' = (Join-Path $root 'PERMISSIONS.md')
  'NESRecomp-LICENSE.txt' = (Join-Path $engineRoot 'LICENSE')
  'SDL2-COPYING.txt' = (Join-Path $engineRoot 'runner/external/SDL2/COPYING.txt')
  'ImGui-LICENSE.txt' = (Join-Path $uiRoot 'src/third_party/imgui/LICENSE.txt')
  'RecompUI-LICENSE.txt' = (Join-Path $uiRoot 'LICENSE')
  'RecompNet-LICENSE.txt' = (Join-Path $engineRoot 'lib/recomp-net/LICENSE')
  'RBEngine-LICENSE.txt' = (Join-Path $engineRoot 'lib/retcomm-rbengine/LICENSE')
  'LatoLatin-OFL.txt' = (Join-Path $root 'tools/release-licenses/LatoLatin-OFL.txt')
  'NotoSansSymbols2-OFL.txt' = (Join-Path $root 'tools/release-licenses/NotoSansSymbols2-OFL.txt')
  'OpenMoji-LICENSE.txt' = (Join-Path $root 'tools/release-licenses/OpenMoji-LICENSE.txt')
}
# Match the notices to the compiler runtime actually staged by a GNU build.
if (Test-Path -LiteralPath (Join-Path $bin 'libstdc++-6.dll')) {
  $compilerSetting = [regex]::Match($cacheText, '(?m)^CMAKE_CXX_COMPILER:[^=]+=(.*)\r?$')
  if (-not $compilerSetting.Success) { throw 'missing C++ compiler identity for runtime notices' }
  $compilerPrefix = Split-Path -Parent (Split-Path -Parent $compilerSetting.Groups[1].Value.TrimEnd("`r"))
  foreach ($name in 'COPYING.LIB', 'COPYING.RUNTIME', 'COPYING3', 'README') {
    $releaseLicenses["GCC-$name.txt"] = Join-Path $compilerPrefix "share/licenses/gcc-libs/$name"
  }
  $releaseLicenses['libwinpthread-COPYING.txt'] = Join-Path $compilerPrefix 'share/licenses/libwinpthread/COPYING'
  $releaseLicenses['SDL2-runtime-LICENSE.txt'] = Join-Path $compilerPrefix 'share/licenses/SDL2/LICENSE.txt'
}

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

function Get-StageRelativePath([string]$stage, [string]$path) {
  return $path.Substring($stage.Length).TrimStart('\', '/').Replace('\', '/')
}

function Assert-ReleaseStage([string]$stage, [string]$sourceMods) {
  $files = @(Get-ChildItem $stage -Recurse -File)
  $relativeFiles = @($files | ForEach-Object { Get-StageRelativePath $stage $_.FullName })

  $required = @(
    'SuperMarioBrosRecomp.exe',
    'falcon_owner_assets.exe',
    'smb_hdpack_importer.exe',
    'SDL2.dll',
    'README.txt',
    'licenses/Game-LICENSE.txt',
    'licenses/NESRecomp-LICENSE.txt',
    'licenses/SDL2-COPYING.txt',
    'licenses/ImGui-LICENSE.txt',
    'THIRD-PARTY-LICENSES/README.md',
    'third_party/ymfm/LICENSE'
  )
  $required += @($releaseLicenses.Keys | ForEach-Object { "licenses/$_" })
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

function Assert-ReleaseArchive([string]$zip, [string]$stage) {
  Add-Type -AssemblyName System.IO.Compression.FileSystem
  $expected = @{}
  foreach ($file in Get-ChildItem $stage -Recurse -File) {
    $relative = Get-StageRelativePath $stage $file.FullName
    $expected[$relative] = $file.FullName
  }

  $archive = [System.IO.Compression.ZipFile]::OpenRead($zip)
  try {
    $seen = @{}
    foreach ($entry in $archive.Entries) {
      if ($entry.FullName.Contains('\')) {
        throw "release archive contains a non-portable Windows path: $($entry.FullName)"
      }
      $relative = $entry.FullName
      if ([string]::IsNullOrEmpty($entry.Name)) { continue }
      if ($relative.StartsWith('/') -or $relative -match '(^|/)\.\.(/|$)') {
        throw "release archive contains unsafe path: $relative"
      }
      if ($seen.ContainsKey($relative)) {
        throw "release archive contains duplicate path: $relative"
      }
      $seen[$relative] = $true
      if (-not $expected.ContainsKey($relative)) {
        throw "release archive contains unstaged payload: $relative"
      }

      $sha = [System.Security.Cryptography.SHA256]::Create()
      $stream = $entry.Open()
      try {
        $archiveHash = [BitConverter]::ToString($sha.ComputeHash($stream)).Replace('-', '')
      } finally {
        $stream.Dispose()
        $sha.Dispose()
      }
      $stageHash = (Get-FileHash -Algorithm SHA256 -LiteralPath $expected[$relative]).Hash
      if ($archiveHash -ne $stageHash) {
        throw "release archive content differs from staging: $relative"
      }
    }
    $missing = @($expected.Keys | Where-Object { -not $seen.ContainsKey($_) })
    if ($missing.Count -ne 0) {
      throw "release archive is missing staged payload: $($missing -join ', ')"
    }
  } finally {
    $archive.Dispose()
  }
}

function Remove-ReleaseStage([string]$stage) {
  $full = [IO.Path]::GetFullPath($stage)
  $allowed = @('stage_standard', 'stage_widescreen') | ForEach-Object {
    [IO.Path]::GetFullPath((Join-Path $out $_))
  }
  if ($full -notin $allowed) { throw "refusing to remove an unexpected release stage: $full" }
  foreach ($ancestor in @($root, $out)) {
    if ([IO.File]::GetAttributes($ancestor) -band [IO.FileAttributes]::ReparsePoint) {
      throw "refusing release cleanup through a reparse point: $ancestor"
    }
  }
  try { $attributes = [IO.File]::GetAttributes($full) }
  catch [IO.FileNotFoundException] { return }
  catch [IO.DirectoryNotFoundException] { return }
  if (($attributes -band [IO.FileAttributes]::ReparsePoint) -or
      -not ($attributes -band [IO.FileAttributes]::Directory)) {
    throw "refusing release cleanup of a reparse point or non-directory: $full"
  }
  $pending = New-Object 'System.Collections.Generic.Stack[string]'
  $pending.Push($full)
  while ($pending.Count) {
    $directory = $pending.Pop()
    if ([IO.File]::Exists((Join-Path $directory 'HEAD')) -and
        [IO.Directory]::Exists((Join-Path $directory 'objects'))) {
      throw "refusing release cleanup of a nested repository: $directory"
    }
    foreach ($entry in [IO.Directory]::EnumerateFileSystemEntries($directory)) {
      if ([IO.Path]::GetFileName($entry) -ieq '.git') {
        throw "refusing release cleanup of a nested repository: $entry"
      }
      $attributes = [IO.File]::GetAttributes($entry)
      if ($attributes -band [IO.FileAttributes]::ReparsePoint) {
        throw "refusing release cleanup of a reparse point: $entry"
      }
      if ($attributes -band [IO.FileAttributes]::Directory) { $pending.Push($entry) }
    }
  }
  Remove-Item -LiteralPath $full -Recurse -ErrorAction Stop
  if (Test-Path -LiteralPath $full) { throw "release stage was not removed: $full" }
}

function New-ReleaseZip {
  $stage = Join-Path $out "stage_standard"
  Remove-ReleaseStage $stage
  New-Item -ItemType Directory -Force $stage | Out-Null

  Copy-Item $exe $stage
  foreach ($extra in 'SDL2.dll', 'falcon_owner_assets.exe', 'smb_hdpack_importer.exe') {
    $p = Join-Path $bin $extra
    if (-not (Test-Path $p -PathType Leaf)) {
      $p = Join-Path $buildRoot $extra
    }
    if ($extra -eq 'keybinds.ini' -and -not (Test-Path $p -PathType Leaf)) {
      $p = Join-Path $root 'recomp-ui\keybinds.ini'
    }
    if (-not (Test-Path $p -PathType Leaf)) { throw "missing required runtime file at $p" }
    Copy-Item $p $stage
  }
  foreach ($runtime in $mingwRuntimeFiles) {
    $runtimePath = Join-Path $bin $runtime
    if (-not (Test-Path -LiteralPath $runtimePath -PathType Leaf)) {
      $runtimePath = Join-Path $buildRoot $runtime
    }
    if (Test-Path -LiteralPath $runtimePath -PathType Leaf) {
      Copy-Item -LiteralPath $runtimePath -Destination $stage
    }
  }

  # The launcher resolves its fonts/images beside the executable. Copy the
  # build-staged, console-filtered asset tree; never reach into a user cache.
  $launcherAssets = Join-Path $bin 'assets'
  if (-not (Test-Path $launcherAssets)) {
    throw "missing launcher assets at $launcherAssets"
  }
  Copy-Item $launcherAssets (Join-Path $stage 'assets') -Recurse

  # Built-in packages are source-controlled catalog data. Stage that pristine
  # tree rather than build_release/mods, which may contain state.toml with an
  # owner ROM path or other machine-local selections after a smoke test.
  $preloadedMods = Join-Path $root 'mods\preloaded'
  if (-not (Test-Path $preloadedMods)) {
    throw "missing preloaded mod catalog at $preloadedMods"
  }
  Copy-Item $preloadedMods (Join-Path $stage 'mods') -Recurse

  $readmeCommon | Out-File -Encoding ascii (Join-Path $stage 'README.txt')
  $zip = Join-Path $out 'SuperMarioBrosRecomp-windows-x64.zip'

  New-Item -ItemType Directory -Path (Join-Path $stage 'licenses') | Out-Null
  foreach ($name in $releaseLicenses.Keys) {
    if (-not (Test-Path -LiteralPath $releaseLicenses[$name] -PathType Leaf)) {
      throw "missing required license: $($releaseLicenses[$name])"
    }
    Copy-Item -LiteralPath $releaseLicenses[$name] -Destination (Join-Path $stage "licenses/$name")
  }
  # Preserve attribution and the license for the bundled Sonic audio library.
  New-Item -ItemType Directory -Force (Join-Path $stage 'THIRD-PARTY-LICENSES') | Out-Null
  New-Item -ItemType Directory -Force (Join-Path $stage 'third_party/ymfm') | Out-Null
  Copy-Item -LiteralPath (Join-Path $root 'THIRD-PARTY-LICENSES/README.md') -Destination (Join-Path $stage 'THIRD-PARTY-LICENSES/README.md')
  Copy-Item -LiteralPath (Join-Path $root 'third_party/ymfm/LICENSE') -Destination (Join-Path $stage 'third_party/ymfm/LICENSE')
  Assert-ReleaseStage $stage $preloadedMods

  if (Test-Path -LiteralPath $zip) { Remove-Item -LiteralPath $zip }
  Add-Type -AssemblyName System.IO.Compression
  Add-Type -AssemblyName System.IO.Compression.FileSystem
  $stageFull = [IO.Path]::GetFullPath($stage).TrimEnd('\') + '\'
  $archive = [IO.Compression.ZipFile]::Open(
    [IO.Path]::GetFullPath($zip), [IO.Compression.ZipArchiveMode]::Create)
  try {
    foreach ($file in Get-ChildItem -LiteralPath $stage -Recurse -File | Sort-Object FullName) {
      $fileFull = [IO.Path]::GetFullPath($file.FullName)
      if (-not $fileFull.StartsWith($stageFull, [StringComparison]::OrdinalIgnoreCase)) {
        throw "refusing to archive a file outside the release stage: $fileFull"
      }
      $entryName = $fileFull.Substring($stageFull.Length).Replace('\', '/')
      if ($entryName.StartsWith('/') -or $entryName -match '(^|/)\.\.(/|$)') {
        throw "unsafe ZIP entry name: $entryName"
      }
      [IO.Compression.ZipFileExtensions]::CreateEntryFromFile(
        $archive, $fileFull, $entryName,
        [IO.Compression.CompressionLevel]::Optimal) | Out-Null
    }
  } finally {
    $archive.Dispose()
  }
  Assert-ReleaseArchive $zip $stage
  Remove-ReleaseStage $stage
  Write-Host "staged $zip"
}

if ($Variant -ne 'standard') {
  Write-Warning 'Variant is deprecated; emitting the single Windows ZIP with catalog defaults.'
}
New-ReleaseZip
