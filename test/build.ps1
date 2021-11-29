
$env:Path += ";C:/msys64/mingw64/bin"

Clear-Host

#. "./test/clear.ps1"

#Start-Sleep -Milliseconds 800

Set-Location ./test

New-Item -ItemType Directory -Force -Path ./build

Set-Location ./build

if ($($args.count) -gt 0) {
    $valid = "false"
    if ($args -eq "debug") {
        cmake.exe ../ -G "Ninja" -DCMAKE_BUILD_TYPE=debug
        $valid = "true"
    }
    if ($args -eq "release") {
        cmake.exe ../ -G "Ninja" -DCMAKE_BUILD_TYPE=release
        $valid = "true"
    }
    if ($valid -eq "false") {
        Write-Output "[ERROR] Wrong script argument: ""$args"""
    }
}
else {
    cmake.exe ../ -G "Ninja" -DCMAKE_BUILD_TYPE=release
}

ninja.exe

Copy-Item -Path ../../libs/* -Destination ./bin -Recurse