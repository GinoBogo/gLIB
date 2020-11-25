
Clear-Host

function DeleteItem {
    param ($name)

    if ((Test-Path $name) -eq $true ) { Remove-Item $name -Recurse }
}

DeleteItem("./benchmark/build")