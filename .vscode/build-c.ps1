param(
    [Parameter(Mandatory = $true)][string]$SourceFile,
    [switch]$Run
)

$ErrorActionPreference = 'Stop'
$workspaceRoot = Split-Path $PSScriptRoot -Parent
$libraryDirectory = Join-Path $workspaceRoot 'C/src/lib'
$source = Get-Item -LiteralPath $SourceFile

if ($source.Extension -ne '.c') {
    throw 'Open a C practice source file before building.'
}

$libraryPrefix = [IO.Path]::GetFullPath($libraryDirectory).TrimEnd('\') + '\'
if ($source.FullName.StartsWith($libraryPrefix, [StringComparison]::OrdinalIgnoreCase)) {
    throw 'Run the practice file containing main, not a library source file.'
}

# C/src exercises use the shared libraries; algorithm solutions build independently.
$practicePrefix = [IO.Path]::GetFullPath((Join-Path $workspaceRoot 'C/src')).TrimEnd('\') + '\'
$librarySources = @()
if ($source.FullName.StartsWith($practicePrefix, [StringComparison]::OrdinalIgnoreCase)) {
    $librarySources = @(Get-ChildItem -LiteralPath $libraryDirectory -Filter '*.c' -File -Recurse |
        Sort-Object FullName | Select-Object -ExpandProperty FullName)
}
$outputFile = Join-Path $source.DirectoryName ($source.BaseName + '.exe')

# MinGW ld may reject non-ASCII output paths. Keep the source name and use an ASCII build path.
if ($outputFile -match '[^\x00-\x7F]') {
    $pathHasher = [Security.Cryptography.SHA256]::Create()
    try {
        $pathBytes = [Text.Encoding]::UTF8.GetBytes($source.FullName.ToLowerInvariant())
        $pathHash = [BitConverter]::ToString($pathHasher.ComputeHash($pathBytes)).Replace('-', '').Substring(0, 12)
    } finally {
        $pathHasher.Dispose()
    }
    $outputDirectory = Join-Path $workspaceRoot "build/gcc/$pathHash"
    New-Item -ItemType Directory -Force -Path $outputDirectory | Out-Null
    $outputFile = Join-Path $outputDirectory 'program.exe'
}
$compilerArguments = @('-g', '-I', $libraryDirectory, $source.FullName) +
    $librarySources + @('-o', $outputFile)

& gcc @compilerArguments
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

if ($Run) {
    Push-Location $source.DirectoryName
    try {
        & $outputFile
        $runExitCode = $LASTEXITCODE
    } finally {
        Pop-Location
    }
    exit $runExitCode
}
