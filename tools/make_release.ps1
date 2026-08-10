<#
make_release.ps1 -- build the dual-zip release assets.

Every release ships TWO windows zips (never a bare exe -- the exe needs
SDL2.dll):

  standard    SuperMarioBrosRecomp-windows-x64.zip
              No widescreen.ini -- boots the authentic 4:3 game.

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
      --title "vX.Y.Z -- <headline>" --notes-file <notes.md>

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
if (-not (Test-Path $exe)) { throw "missing $exe -- run build_all.bat first" }
$cmakeCache = Join-Path $bin 'CMakeCache.txt'
if (-not (Test-Path $cmakeCache)) { throw "missing $cmakeCache -- run build_all.bat first" }
$traceSetting = Select-String -LiteralPath $cmakeCache -Pattern '^NESRECOMP_ENABLE_TRACE:BOOL=OFF$'
if (-not $traceSetting) {
  throw 'refusing to package a Windows build with NESRECOMP_ENABLE_TRACE enabled or unset'
}

$readmeCommon = @'
Super Mario Bros. - Static Recompilation
=========================================

A native PC build of Super Mario Bros., produced by statically
recompiling the NES ROM's 6502 code to C with the NESRecomp framework
(github.com/mstan/nesrecomp).

No ROM is included. On first launch, select your legally-obtained
Super Mario Bros. (World) ROM (CRC32 3337EC46). The path is remembered
for future launches.

The Captain Falcon player-replacement mod is included but remains disabled
until you select a legally-owned Super Smash Bros. (USA), NTSC-U v1.0 ROM
in the Mods screen. That ROM is verified locally and is never included in
this package. The first Falcon launch derives its model, animations, effects,
and audio into your local user cache; those generated files are not shipped.

Controls: arrow keys = D-Pad, Z = A, X = B, Enter = Start,
Right Shift = Select. F5 turbo, F6 save state, F7 load state,
F11 / Alt+Enter fullscreen. Gamepads are supported; bindings are
configurable in keybinds.ini.
'@

function Get-StageRelativePath([string]$stage, [string]$path) {
  return $path.Substring($stage.Length).TrimStart('\', '/').Replace('\', '/')
}

function Assert-ReleaseStage([string]$stage, [string]$kind, [string]$sourceMods) {
  $files = @(Get-ChildItem $stage -Recurse -File)
  $relativeFiles = @($files | ForEach-Object { Get-StageRelativePath $stage $_.FullName })

  $required = @(
    'SuperMarioBrosRecomp.exe',
    'falcon_owner_assets.exe',
    'SDL2.dll',
    'keybinds.ini',
    'README.txt'
  )
  if ($kind -eq 'widescreen') { $required += 'widescreen.ini' }
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
    if ($_ -match '^mods/packages/[^/]+/[^/]+/manifest\.toml$') { return $false }
    return $true
  })
  if ($unexpected.Count -ne 0) {
    throw "release staging contains forbidden owner/dev payload: $($unexpected -join ', ')"
  }

  # The staged catalog must be a byte-for-byte mirror of source-controlled
  # mods/preloaded. This rejects state.toml, generated fighter blobs/audio,
  # local saves, and any other runtime residue under mods/.
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
    if ($text -match '(?im)(?:[a-z]:[\\/]|/(?:home|users|tmp)/)') {
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
  foreach ($extra in 'SDL2.dll', 'keybinds.ini', 'falcon_owner_assets.exe') {
    $p = Join-Path $bin $extra
    if (-not (Test-Path $p -PathType Leaf)) { throw "missing required runtime file at $p" }
    Copy-Item $p $stage
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

  Assert-ReleaseStage $stage $kind $preloadedMods

  if (Test-Path $zip) { Remove-Item $zip }
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
  Remove-Item -Recurse -Force $stage
  Write-Host "staged $zip"
}

if ($Variant -eq 'standard' -or $Variant -eq 'both') { New-ReleaseZip 'standard' }
if ($Variant -eq 'widescreen' -or $Variant -eq 'both') { New-ReleaseZip 'widescreen' }
