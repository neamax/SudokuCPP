# Sudoku Console Game
A simple Sudoku puzzle generator and solver written in C++. Built as a clean, beginner-friendly project to demonstrate basic C++ skills, logic building, and object-oriented design.


## 🎯 Features
- Well-commented clean code
- Auto-generated a valid Sudoku board
- Interactive terminal gameplay
- Input validation
- Simple object-oriented structure


## 🧑🏽‍💻 Run
- Download and run executable files available on the [Release](https://github.com/neamax/SudokuCPP/releases) page or /Build folder


## 🔧 Build
You can edit and compile your own version of this game easily using the following scripts.

- Clone or download this repository
```bash
git clone https://github.com/neamax/SudokuCPP.git
```

### Windows
- Install g++ (MinGW) from [MSYS2](https://www.msys2.org/)

- Using Git Bash
```bash
cd /project/root/path
chmod +x build.sh
./build-win.sh
```

- Using Windows PowerShell
```bash
cd /project/root/path
./build.ps1
```


### MacOS or Linux
- Install g++ on Terminal
```bash
sudo apt update
sudo apt install g++ -y
```

- Using g++ compiler
```bash
cd /project/root/path
g++ Source/Private/main.cpp Source/Private/SudokuGame.cpp -I Source/Public -o Build/SudokuGame
./SudokuGame
```

-- Compiled executable file will be saved in /Build folder.


## 📁 File Structure
```
.
├── Source/
│   ├── Public/             # Header files (.h)
│   └── Private/            # Source files (.cpp)
│
├── Build/                  # Compiled executable goes here
│   └── [LatestVersion]
│
├── build-win.sh                # Shell script to build the project for Windows
├── build-win.ps1               # Windows PowerShell script to build the project for Windows
├── README.md                   # You're reading it!
├── LICENCE
└── .gitignore
```


## 🪖 Behind the Code
This project was written during my free time in military service. In the quiet hours, surrounded by duty and discipline, I turned to code as both escape and challenge. Sudoku was the perfect metaphor — a grid of chaos slowly tamed by logic and patience.

I hope this little game brings you the same sense of focus and calm it gave me.

– Neama 🎮
