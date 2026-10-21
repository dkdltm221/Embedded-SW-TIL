param([Parameter(Mandatory = $true)][string]$SourceFile)

$ErrorActionPreference = 'Stop'
$workspaceRoot = Split-Path $PSScriptRoot -Parent
$source = Get-Item -LiteralPath $SourceFile
if ($source.Extension -notin '.c', '.cpp', '.cc', '.cxx') {
    throw 'Open a C or C++ source file before building.'
}
$relativeDirectory = $source.DirectoryName.Substring($workspaceRoot.Length).TrimStart('\')
$outputDirectory = Join-Path (Join-Path (Join-Path $workspaceRoot 'build') $relativeDirectory) $source.BaseName
New-Item -ItemType Directory -Force -Path $outputDirectory | Out-Null
$vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
$installation = & $vswhere -latest -products '*' -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (-not $installation) { throw 'MSVC C/C++ build tools were not found.' }
$developerShell = Join-Path $installation 'Common7\Tools\Launch-VsDevShell.ps1'
& $developerShell -Arch amd64 -HostArch amd64 -SkipAutomaticLocation | Out-Null
Push-Location $outputDirectory
try {
    $compilerOptions = @('/nologo', '/W4', '/Zi', '/utf-8')
    if ($source.Extension -ne '.c') { $compilerOptions += '/EHsc' }
    & cl.exe @compilerOptions $source.FullName "/Fe$($source.BaseName).exe" /link /INCREMENTAL:NO
    $buildExitCode = $LASTEXITCODE
} finally {
    Pop-Location
}
exit $buildExitCode
