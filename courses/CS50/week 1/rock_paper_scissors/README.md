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
- [ ] Single play against computer with chosen number of rounds
- [ ] Multiple levels of difficulty vs. computer
- [ ] Results history
- [ ] Customizable player name for record keeping

### Core “GUI” (console)
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

> Note: `cs50.c`/`cs50.h` are included in this folder; no system C S50 install required.

---

## 🛠 Usage

```bash
# clone the parent repo once
git clone https://github.com/earlybird3010/cs-self-study.git

# cd into this subproject (quote path due to space)
cd 'cs-self-study/courses/CS50/week 1/rock_paper_scissors'

# build and run
gcc -std=c11 -Wall -Wextra -Werror main.c cs50.c -o main
./main

🗂 Project Structure
rock_paper_scissors/
├── cs50.c        # vendored CS50 library source
├── cs50.h        # vendored CS50 header
├── main.c        # program source
├── README.md
└── doc.txt       # notes / tracker
# (build artifacts like bin/rps are not committed)

⚙️ Built With

Language: C (GCC/Clang)

Libraries: cs50.c, cs50.h

🤝 Contributing

Pull requests are welcome! Fork the repo and open a PR.

📄 License

MIT
 © Chau Nguyen