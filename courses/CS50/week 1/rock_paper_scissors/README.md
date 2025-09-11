# 🚀 Rock, Paper, Scissors (C)

> A C program that simulates the game rock, paper, scissors.

---

## 📚 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Built With](#built-with)
- [Contributing](#contributing)
- [License](#license)

---

## 🧠 Overview
This project simulates two players playing rock, paper, scissors. It’s a foundation for more advanced features later.

---

## ✨ Features

### Core Logic
- [x] Single play against computer with chosen number of rounds
- [x] Multiple levels of difficulty vs. computer
- [x] Results history
- [ ] Customizable player name for record keeping

### Core “GUI”
- [ ] Show hand gestures during play (ASCII art)
- [ ] Display score on screen while playing
- [ ] Buttons/keys for user’s choice
- [ ] Sound effects for wins, losses, and ties

### Above and Beyond
- [ ] Display a list of outcomes
- [ ] Improve computer strategy based on prior outcomes
- [ ] Basic statistics (win rate, most common choice, longest streak)

---

## 🚀 Getting Started

### ✅ Prerequisites
- C compiler: GCC or Clang
- Unix-like OS (Linux/macOS)  
  **Tested:** Fedora Linux 40+ (GCC)
- Install CS50 library: https://github.com/cs50/libcs50 

---

## 🛠 Usage

```bash
# clone the parent repo once
git clone https://github.com/earlybird3010/cs-self-study.git

# cd into this subproject (quote path due to space)
cd 'cs-self-study/courses/CS50/week 1/rock_paper_scissors'

# build and run
gcc -std=c11 -Wall -Wextra -Werror main.c -o main -lcs50

./main
```
---

## 🗂 Project Structure

```markdown
rock_paper_scissors/
├──.vscode/       # files for build & debug
├── main.c        # program source
├── README.md
└── doc.txt       # notes tracker
```

---

## ⚙️ Built With

Language: C (GCC/Clang)

Libraries: CS50 (vendored: `cs50.c`, `cs50.h`)

---

## 🤝 Contributing

Pull requests are welcome! Fork the repo and open a PR.

---

## 📄 License

MIT
 © Chau Nguyen