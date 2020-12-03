
$env:Path += ";C:/msys64/mingw64/bin"

Clear-Host

#. "./test/clear.ps1"

#Start-Sleep -Milliseconds 800

Set-Location ./test

New-Item -ItemType Directory -Force -Path ./build

Set-Location ./build

if ($($args.count) -gt 0) {
    cmake.exe ../ -G "Ninja" -DCMAKE_BUILD_TYPE=debug
}
else {
    cmake.exe ../ -G "Ninja" -DCMAKE_BUILD_TYPE=release
}

ninja.exe

Copy-Item -Path ../libs/* -Destination ./bin -Recurse