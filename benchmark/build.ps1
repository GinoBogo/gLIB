
$env:Path += ";C:/msys64/mingw64/bin"

Clear-Host

. "./benchmark/clear.ps1"

Start-Sleep -Milliseconds 800

Set-Location ./benchmark

New-Item -ItemType Directory -Force -Path ./build

Set-Location ./build

cmake.exe ../ -G "Ninja" -DCMAKE_BUILD_TYPE=release

ninja.exe

Copy-Item -Path ../libs/* -Destination ./bin -Recurse