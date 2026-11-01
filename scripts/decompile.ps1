param(
    [Parameter(Mandatory=$true)][string]$GhidraHome,
    [Parameter(Mandatory=$true)][string]$JavaHome,
    [string]$BinaryDirectory = 'C:\Program Files (x86)\Toyota Diagnostics\Techstream\bin'
)
$ErrorActionPreference = 'Stop'
$repo = Split-Path -Parent $PSScriptRoot
$env:JAVA_HOME = (Resolve-Path -LiteralPath $JavaHome).Path
$headless = Join-Path (Resolve-Path -LiteralPath $GhidraHome).Path 'support\analyzeHeadless.bat'
$targets = @{
    'MainMenu.exe' = @('00420d80','004218b0','0041d500','004a9e40','00425100','00423330','004b6110')
    'tiswebapi.dll' = @('10001160','10010480','10003860','10003890','10003990','10003a50')
    'IT3Versatile.dll' = @('10001740','10001790')
}
foreach ($name in $targets.Keys) {
    $source = Join-Path $BinaryDirectory $name
    $samples = Join-Path $repo 'local\samples'
    $out = Join-Path $repo ('local\reproduced\' + $name)
    $project = Join-Path $out 'project'
    New-Item -ItemType Directory -Path $samples,$project -Force | Out-Null
    $sample = Join-Path $samples $name
    Copy-Item -LiteralPath $source -Destination $sample
    $addresses = $targets[$name]
    & $headless $project offline -import $sample -overwrite -analysisTimeoutPerFile 240 -max-cpu 2 -scriptPath $PSScriptRoot -postScript ExportKeyEvidence.java $out @addresses
    if ($LASTEXITCODE -ne 0) { throw "Decompilation failed for $name" }
}
