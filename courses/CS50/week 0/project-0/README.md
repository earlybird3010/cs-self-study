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
- [x] **Boggart:** a creature who transforms into your worst fear
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
    - I rescaled and repositioned the skrewt as discussed above.
    - After Harry escaped the dungeon, I used a hand-calculated position to render him on screen.

### 3. Infinite looping
    - To avoid the dungeon backdrop from looping indefinitey, I chose an escape place that was as close as possible so that Harry couldn't touch the skrewt.
    - In the first place, I chose a place where Harry touched the wall. By design, the program moved him to his previous recorded position, which was his position when he entered the dungeon. As a result, I chose another position where he didn't touch anything.

## Design Notes - Boggart
It was simple to implement the Boggart, as its behavior closely mirrors the skrewt. I modified its movement pattern as well as its interaction when battling against Harry Potter. Nonetheless, I decided to challenge myself further by implementing background music tied to scene transitions, and that led to one important design decision.

### **Maze -> A Different Backdrop -> Another Backdrop Transitions**
    - When transitioning between backdrops, I wanted to stop the old soundtrack and start a new one smoothly. Also, I wanted each soundtrack to loop indefinitely in its associated scene, except for some special cases (Boggart's sound when it encounters Harry).
    - First idea: used `broadcast` and `stop all sounds` to stop the current music before starting a new one. This only worked for non-looping sounds, and it didn't apply to me because I had to loop my short soundtrack to make the background music. If a `forever` block was looping `play sounds() until done`, then a `stop all sounds` block would only stop the current iteration. Unfortunately, the `when I receive()` block cannot be stacked under the forever block and above the play sounds() until done block to stop the forever script from executing.   
    - Final idea: I needed to keep track of certain events, so I switched to using **global variables** to track music state.  One simple example is the win? variable, whose value is determined by Harry touching the Triwizard cup. When we start the game, it is set to false. Upon touching the cup, the Harry sprite broadcasts a message to all other sprites. Upon receiving this message, the result sprite sets win? to true. In any sprite other than the result sprite responsible for music, we set win? = true to be a condition for the music to stop.
    - One tiny detail: `play sounds() until done` block plays the full soundtrack unless stopped. To prevent overlaps, I added a `stop all sounds` block **right before** each new scene plays its theme.

# 🚀 Live Demo

🔗 [Play the game on Scratch](https://scratch.mit.edu/projects/1203579370/)