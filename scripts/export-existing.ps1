param(
    [Parameter(Mandatory=$true)][string]$GhidraHome,
    [Parameter(Mandatory=$true)][string]$JavaHome,
    [Parameter(Mandatory=$true)][string]$ProjectDirectory,
    [Parameter(Mandatory=$true)][string]$Program,
    [Parameter(Mandatory=$true)][string]$OutputDirectory,
    [Parameter(Mandatory=$true)][string[]]$Addresses
)
$ErrorActionPreference = 'Stop'
$projectAbsolute = (Resolve-Path -LiteralPath $ProjectDirectory).Path
$scriptAbsolute = (Resolve-Path -LiteralPath $PSScriptRoot).Path
$outputAbsolute = [IO.Path]::GetFullPath($OutputDirectory)
$env:JAVA_HOME = (Resolve-Path -LiteralPath $JavaHome).Path
& (Join-Path $GhidraHome 'support\analyzeHeadless.bat') $projectAbsolute offline -process $Program -noanalysis -scriptPath $scriptAbsolute -postScript ExportKeyEvidence.java $outputAbsolute @Addresses
if ($LASTEXITCODE -ne 0) { throw "Ghidra export failed: $LASTEXITCODE" }
