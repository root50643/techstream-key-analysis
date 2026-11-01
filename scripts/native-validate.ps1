param(
    [string]$BinaryDirectory = 'C:\Program Files (x86)\Toyota Diagnostics\Techstream\bin',
    [string]$Python = 'python'
)
$ErrorActionPreference = 'Stop'
$repo = Split-Path -Parent $PSScriptRoot
$local = Join-Path $repo 'local'
New-Item -ItemType Directory -Path $local -Force | Out-Null
$compiler = Join-Path $env:WINDIR 'Microsoft.NET\Framework\v4.0.30319\csc.exe'
if (!(Test-Path -LiteralPath $compiler)) { throw '32-bit .NET Framework compiler not found.' }
$probe = Join-Path $local 'NativeProbe.exe'
& $compiler /nologo /platform:x86 "/out:$probe" (Join-Path $PSScriptRoot 'NativeProbe.cs')
if ($LASTEXITCODE -ne 0) { throw 'Native probe compilation failed.' }
$previous = $env:PYTHONPATH
try {
    $env:PYTHONPATH = Join-Path $repo 'src'
    & $Python (Join-Path $PSScriptRoot 'native_validate.py') --probe $probe --bin-directory $BinaryDirectory
    if ($LASTEXITCODE -ne 0) { throw 'Native validation failed.' }
} finally { $env:PYTHONPATH = $previous }
