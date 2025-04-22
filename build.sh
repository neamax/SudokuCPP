#!/usr/bin/env bash

# Colours
RED="\033[0;31m"
ORANGE="\033[3;96m"
LINK="\033[0;91m"
YELLOW="\033[1;33m"
CYAN="\033[0;36m"
MAGENTA="\033[0;35m"
RESET="\033[0m"

# Fancy intro
clear
echo
echo -e "${CYAN}===================================================="
echo -e "====                                            ===="
echo -e "====                 ${MAGENTA}Welcome to                 ${RESET}${CYAN}===="
echo -e "====            ${ORANGE}SUDOKU GAME BUILDER             ${RESET}${CYAN}===="
echo -e "====                                            ===="
echo -e "====      ${MAGENTA}Developed for fun by Neama Kazemi     ${RESET}${CYAN}===="
echo -e "====               ${MAGENTA}Github/${RESET}${LINK}neamax${RESET}                ${CYAN}===="
echo -e "====                                            ===="
echo -e "====  ➖➖➖  ${MAGENTA}LuckyGene Indie Studios  ➖➖➖   ${RESET}${CYAN}===="
echo -e "====             ${MAGENTA}www.luckygene.net              ${RESET}${CYAN}===="
echo -e "====                                            ===="
echo -e "${CYAN}====================================================${RESET}"
echo
echo -e "This script will compile the C++ source files"
echo -e "and saves the output in the ./Build directory."
echo -e "You can choose your own name for the executable file."
echo
echo

# Prompt for file name with default value
# Print the coloured prompt manually
echo -ne "${YELLOW}Enter executable name [default: SudokuGame.exe]: ${RESET}"
read EXEC_NAME
EXEC_NAME=${EXEC_NAME:-SudokuGame.exe}

# Ensure .exe extension
[[ "$EXEC_NAME" != *.exe ]] && EXEC_NAME="${EXEC_NAME}.exe"

# Create Build directory if it doesn't exist
mkdir -p Build

# Append _# if file exists
BASENAME="${EXEC_NAME%.exe}"
EXT=".exe"
COUNTER=1
while [[ -f "Build/$EXEC_NAME" ]]; do
    EXEC_NAME="${BASENAME}_$COUNTER$EXT"
    ((COUNTER++))
done

echo
echo -e "${CYAN}   Starting compilation...${RESET}"

# Actual compilation
g++ -I Source/Public Source/Private/*.cpp -o Build/$EXEC_NAME

sleep 2
# Simulated progress bar
echo -ne "${CYAN}   Compiling source files "
for i in {1..30}; do
    echo -ne "${GREEN}█${RESET}"
    sleep 0.1
done
echo

# Result
if [ $? -eq 0 ]; then
    echo -e "${CYAN}✔️ ${GREEN}Build complete! Your game has been successfully compiled.${RESET}"
else
    echo -e "${RED}❌ Build failed.${RESET}"
fi

sleep 1
echo -e "   ${CYAN}Your executable is ready at ./Build/$EXEC_NAME${RESET}"
