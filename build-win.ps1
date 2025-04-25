# PowerShell version of build.sh for Windows users

Clear-Host

Write-Host ""
Write-Host "===================================================="
Write-Host "====                                            ===="
Write-Host "====                 Welcome to                 ===="
Write-Host "====            SUDOKU GAME BUILDER             ===="
Write-Host "====                                            ===="
Write-Host "====      Developed for fun by Neama Kazemi     ===="
Write-Host "====                Github/neamax               ===="
Write-Host "====                                            ===="
Write-Host "====      ---  LuckyGene Indie Studios  ---     ===="
Write-Host "====              www.luckygene.net             ===="
Write-Host "====                                            ===="
Write-Host "===================================================="
Write-Host ""
Write-Host "This script will compile the C++ source files"
Write-Host "and saves the output in the ./Build directory."
Write-Host "You can choose your own name for the executable file."
Write-Host ""

# Prompt for executable name
$defaultName = "SudokuGame.exe"
Write-Host -NoNewline "Enter executable name [default: $defaultName]: "
$execName = Read-Host
if ([string]::IsNullOrWhiteSpace($execName)) {
    $execName = $defaultName
}

# Ensure .exe extension
if (-not ($execName -like "*.exe")) {
    $execName += ".exe"
}

# Create Build directory if it doesn't exist
if (-not (Test-Path -Path "Build")) {
    New-Item -ItemType Directory -Path "Build" | Out-Null
}

# Check for existing file and append _#
$baseName = [System.IO.Path]::GetFileNameWithoutExtension($execName)
$ext = ".exe"
$counter = 1
while (Test-Path "Build/$execName") {
    $execName = "$baseName`_$counter$ext"
    $counter++
}

Write-Host ""
Write-Host "   Starting compilation..."
Start-Sleep -Seconds 2

# Simulated progress bar
Write-Host -NoNewline "   Compiling source files "
for ($i = 0; $i -lt 20; $i++) {
    Write-Host -NoNewline "="
    Start-Sleep -Milliseconds 100
}
Write-Host ""

# Compile the source
& g++ -I Source/Public Source/Private/*.cpp -o "Build/$execName"

# Check result
if ($LASTEXITCODE -eq 0) {
    Write-Host ""
    Write-Host " Build Success!"
    Write-Host " Your game has been successfully compiled."
    Write-Host " Output file: ./Build/$execName"
    Write-Host ""
} else {
    Write-Host " Build failed."
}