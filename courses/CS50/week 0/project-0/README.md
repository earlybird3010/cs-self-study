# Triwizard Maze
Triwizard Maze is a maze escape game based on the third task in the Triwizard Tournament in the book Harry Potter and the Goblet of Fire.

# Why?
I want to create a substantial Scratch project to improve my critical thingking and debugging skills.

# Phase 1: Basic setup
- [x] **Basic Setup:** Create a maze sprite, a Harry Potter Sprite, and a Triwizard Cup sprite at the center of the maze.
- [x] **Player Movement:** Implement function to represent Harry Potter's natural movement. It means the player cannot pass through walls.
- [x] **Goal Object:** The game ends when Harry Potter touches the Triwizard cup.

## Additional details
- Changed the maze from a backdrop to a sprite to utilize the `touching` sensing block. This ensure the player cannot pass through walls.
- Added an additional backdrop and sprite that appear when the player reaches the Triwizard Cup, serving as a win screen.

# Phase 2: Add enemies
- [x] **Blast-Ended Skrewt:** a giant scorpion who moves around and attacks people
- [ ] **Boggart:** a creature who transforms into your worst fear
- [ ] **Golden Mist:** a mist which disorients the player
- [ ] **Sphinx:** a creature that poses difficult questions to whom it encounters
- [ ] **Acromantula:** a giant spider
- [ ] **Devil's Snare:** a type of magical plant that entangles people

## Design Notes - Blasted-Ended Skrewt
I thought it was simple to build this enemy, but it was challenging. Here are three major design decisions and lessons.

### 1.**Maze -> Dungeon -> Maze Transitions**
    - When the skrewt touches Harry, the maze transitions to a **dungeon backdrop** where Harry must choose from three options to defeat it.
    - If Harry loses, the game ends. If he wins, he returns to the maze.
    - Inspired by Ivy's Hardest Game, I used 2 additional variables to store the skrewt's position before entering the dungeon. They are used to restore the skrewt to its original position when it escaped the dungeon.

### 2. Rescaling and repositioning sprites
    - I rescale and reposition the skrewt as discussed above.
    - After Harry escaped the dungeon, I used a hand-calculated position to render him on screen.

### 3. Infinite looping
    - To avoid the dungeon backdrop from looping indefinitey, I chose an escape place that was as close as possible so that Harry couldn't touch the skrewt.
    - In the first place, I chose a place where Harry touched the wall. By design, the program moved him to his previous recorded position, which was his position when he entered the dungeon. As a result, I chose another position where he didn't touch anything.

# 🚀 Live Demo

🔗 [Play the game on Scratch](https://scratch.mit.edu/projects/1203579370/)