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

# Collect library implementations on every build, including newly added files.
$librarySources = @(Get-ChildItem -LiteralPath $libraryDirectory -Filter '*.c' -File -Recurse |
    Sort-Object FullName | Select-Object -ExpandProperty FullName)
$outputFile = Join-Path $source.DirectoryName ($source.BaseName + '.exe')
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
