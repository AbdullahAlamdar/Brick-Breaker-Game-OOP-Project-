# Brick Breaker Game

A classic **Brick Breaker** game implemented in C++ using the **OpenGL Utility Toolkit (GLUT)**. Destroy bricks by bouncing the ball with a paddle, and aim for the highest score!

---

## Table of Contents
1. [Features](#features)
2. [Gameplay](#gameplay)
3. [Setup and Installation](#setup-and-installation)
4. [How to Play](#how-to-play)
5. [Project Structure](#project-structure)
6. [Code Explanation](#code-explanation)
7. [Contributing](#contributing)
8. [License](#license)

---

## Features
- **Interactive Gameplay**: Control a paddle to bounce the ball and break bricks.
- **Real-Time Graphics**: Smooth rendering powered by OpenGL.
- **Dynamic Levels**: Difficulty increases as the game progresses.
- **Score Tracking**: Track your performance as you play.
- **Customizable Gameplay**: Modify paddle, bricks, and ball parameters in the code.
- **Cross-Platform**: Runs on Linux, macOS, and Windows (with appropriate setup).

---

## Gameplay
The objective is to destroy all the bricks on the screen using a ball that bounces off a paddle. If the ball falls below the paddle, you lose a life. Clear all the bricks to win the level.

### Controls
- **Move Paddle**: Use the arrow keys (`←` and `→`) to move the paddle.
- **Pause Game**: Press `P` to pause or resume.
- **Exit Game**: Press `ESC` to quit.

### Winning
- Successfully destroy all bricks on the screen.

### Losing
- The game ends when all lives are lost.

---

## Setup and Installation
### Prerequisites
- A **C++ Compiler** (e.g., `g++` or `clang`).
- **OpenGL and GLUT Libraries**:
  - Install these libraries based on your operating system:
    - On Ubuntu/Debian:
      ```bash
      sudo apt-get install freeglut3-dev
      ```
    - On Fedora:
      ```bash
      sudo dnf install freeglut-devel
      ```
    - On macOS (using Homebrew):
      ```bash
      brew install freeglut
      ```
    - On Windows: Download GLUT binaries from the official OpenGL website and configure them with your compiler.

### Installation Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/brick-breaker.git
2.Navigate to the project directory 
   ``` bash
   cd brick-breaker
   ```
3.Compile the code:
   ```bash
   g++ -o BrickBreaker Brick\ Breaker.cpp -lGL -lGLU -lglut
   ```
---
### Project Structure
- **Brick Breaker.cpp**: Main source file containing the game's logic, initialization, and rendering.
- **Brick Breaker.cpp**: Header file with utility functions for OpenGL shapes and basic drawing tools.

---

### Extras 
> **Developer's Note**: This project is extra special because it symbolizes a comeback story. Fun fact: I failed my OOP course in the regular semester, but I crushed it during the summer! Turns out, a little extra time and determination can turn a "failure" into a "feature upgrade." So if you’re struggling, just remember: persistence can break more bricks than this game ever will!













