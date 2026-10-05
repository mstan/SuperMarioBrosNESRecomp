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
$cmake = Join-Path $env:ProgramFiles 'CMake/bin/cmake.exe'
if (-not (Test-Path -LiteralPath $cmake)) { throw "CMake was not found at $cmake" }
function Invoke-BuildTool([string]$program, [string[]]$arguments) {
    $quoted = foreach ($argument in $arguments) {
        '"' + [regex]::Replace([regex]::Replace($argument, '(\\*)"', '$1$1\"'), '(\\+)$', '$1$1') + '"'
    }
    $info = New-Object Diagnostics.ProcessStartInfo
    $info.FileName = $program
    $info.Arguments = $quoted -join ' '
    $info.WorkingDirectory = $root
    $info.UseShellExecute = $false
    $info.CreateNoWindow = $true
    $info.WindowStyle = [Diagnostics.ProcessWindowStyle]::Hidden
    $info.RedirectStandardOutput = $true
    $info.RedirectStandardError = $true
    $process = New-Object Diagnostics.Process
    $process.StartInfo = $info
    $null = $process.Start()
    $stdout = $process.StandardOutput.ReadToEndAsync()
    $stderr = $process.StandardError.ReadToEndAsync()
    $process.WaitForExit()
    Write-Output $stdout.GetAwaiter().GetResult()
    Write-Output $stderr.GetAwaiter().GetResult()
    $code = $process.ExitCode
    $process.Dispose()
    if ($code) { throw "$program failed ($code)" }
}
$build = Join-Path $root $BuildDir
$net = if ($LocalOnly) { 'OFF' } else { 'ON' }
$configure = @('-S',$root,'-B',$build,'-G','Visual Studio 17 2022','-A','x64',
    "-DNESRECOMP_ROOT=$EngineRoot","-DNESRECOMP_BACKEND=$Backend",
    '-DNESRECOMP_ENABLE_TRACE=OFF','-DNESRECOMP_REQUIRE_FALCON_OWNER_HELPER=ON',"-DSMB_ENABLE_NETPLAY=$net")
if ($Rom) { $configure += "-DNESRECOMP_ROM=$Rom" }
if ($RecompUi) { $configure += "-DNESRECOMP_RECOMP_UI=$RecompUi" }
Invoke-BuildTool $cmake $configure
Invoke-BuildTool $cmake @('--build',$build,'--config','Release','--parallel','4')
Write-Output "Built $Backend release in $build"
