# 🧱 Cub3D - My First RayCaster with MLX42

[![1337 Badge](https://img.shields.io/badge/1337-Project-blue)](https://www.42network.org/)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![Grade](https://img.shields.io/badge/Grade-125%2F100-success)

## 📜 Project Overview

Cub3D is a 42 Network project that involves creating a 3D graphical representation of a maze using ray-casting techniques, inspired by the classic game Wolfenstein 3D. This project provides hands-on experience with computer graphics, mathematics, and the miniLibX library.

## 🎮 Features

### ✅ Mandatory Part

- **Raycasting Engine**: Implementation of raycasting algorithm for pseudo-3D perspective
- **Dynamic Window Management**: Smooth window handling (minimize, focus change, etc.)
- **Texture Mapping**: Different wall textures for each cardinal direction (North, South, East, West)
- **Color Configuration**: Customizable floor and ceiling colors
- **Player Controls**:
  - **WASD Keys**: Move through the maze
  - **Arrow Keys**: Rotate camera view
  - **ESC Key**: Close window and exit program
  - **Window Red Cross**: Close window gracefully
- **Map Parsing**: Support for `.cub` configuration files with specific format
- **Error Handling**: Proper validation and error messages for misconfigured files

### ➕ Bonus Part

- **Wall Collisions**: Prevent player from moving through walls
- **Minimap System**: 2D overhead view of the maze
- **Interactive Doors**: Doors that can open and close
- **Animated Sprites**: Moving elements within the game world
- **Mouse Control**: Rotate viewpoint using mouse movement

## 🎮 Bonus Video

![Game Screenshot](assets/video.gif)  

## 🗺️ Map File Format (`.cub`)

The scene description file must contain:

### Texture Paths
```
NO ./path_to_north_texture
SO ./path_to_south_texture  
WE ./path_to_west_texture
EA ./path_to_east_texture
DO ./path_to_door_texture (bonus feature)
```

### Colors
```
F 220,100,0    # Floor color (R,G,B in range 0-255)
C 225,30,0     # Ceiling color (R,G,B in range 0-255)
```

### Map Layout
- `0`: Empty space
- `1`: Wall
- `N/S/E/W`: Player start position and orientation
- `D`: Door (bonus feature)

### Example Valid Map
```
111111
1001D1
101001
1100N1
111111
```

## 📂 Project Structure

```plaintext
📦 42-cub3D_1337
├── 📂 assets/                    # Game assets (textures, sprites)
├── 📂 bonus/                     # Bonus version source code
│   ├── 📂 include/               # Header files for bonus
│   ├── 📂 src/                   # Source files for bonus
│   │   ├── 📂 parsing/           # Map and config parsing
│   │   ├── 📂 rendering/         # Graphics and raycasting
│   │   └── 📂 utils/             # Utility functions
│   └── cub3D_bonus.c             # Main file for bonus version
├── 📂 mandatory/                 # Mandatory version source code
│   ├── 📂 include/               # Header files for mandatory
│   ├── 📂 src/                   # Source files for mandatory
│   │   ├── 📂 parsing/           # Map and config parsing
│   │   ├── 📂 rendering/         # Graphics and raycasting
│   │   └── 📂 utils/             # Utility functions
│   └── cub3D.c                   # Main file for mandatory version
├── 📂 subject/                   # Project subject and documentation
│   └── en.subject.pdf            # Official project requirements
├── Makefile                      # Build configuration
└── README.md                     # Project documentation
```

## 🛠️ Installation & Compilation

### 📌 Prerequisites
- **CMake** (required for MLX42 compilation)
- **GLFW** (required for MLX42 window management)
- **GCC** compiler
- **Make** build system

### 📌 Automatic MLX42 Setup
The Makefile automatically clones and compiles MLX42 if not present in the project directory:

```bash
# MLX42 will be automatically cloned and built during compilation
make
```

### 📌 Manual Dependencies Installation (if needed)

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install build-essential cmake libglfw3-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
```

**macOS:**
```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install cmake glfw
```

### 📌 Compilation

```bash
# Mandatory part
make

# Bonus part
make bonus

# Cleanup
make clean      # Remove object files
make fclean     # Remove all binaries and objects including MLX42
make re         # Full rebuild
```

## 🎯 Usage

**mandatory:**
```bash
./cub3D assets/scenes/valid_scenes/1.scene.cub
```

**bonus:**
```bash
./cub3D assets/scenes/valid_scenes/1.scene_bonus.cub
```

## 🎮 Controls

- **W**: Move forward
- **S**: Move backward  
- **A**: Strafe left
- **D**: Strafe right
- **← →**: Rotate camera
- **ESC**: Exit game
- **Mouse**: Look around (bonus)
- **Space/E**: Open/close doors (bonus)

## 🔧 Technical Implementation

### Core Algorithms
- **Raycasting**: Calculate ray directions and distances for 3D projection
- **DDA Algorithm**: Digital Differential Analysis for efficient ray traversal
- **Texture Mapping**: Perspective-correct texture rendering
- **Collision Detection**: Prevent movement through walls and handle door interactions

### Key Components
- **Map Validation**: Ensure maps are closed/surrounded by walls
- **Texture Loading**: Support for XPM texture files
- **Event Handling**: Keyboard and mouse input processing
- **Memory Management**: Proper allocation and cleanup
- **Door System**: Interactive doors that can be opened/closed (bonus)

## 📏 Project Rules

- **Language**: Written in C following 42 Norm
- **Memory**: No memory leaks allowed
- **Libraries**: Limited to miniLibX, math library, and standard C libraries
- **Error Handling**: Must handle all error cases gracefully
- **Makefile**: Required with standard rules (all, clean, fclean, re, bonus)

## 🎓 Learning Outcomes

- **Computer Graphics**: Understanding of raycasting and 3D projection
- **Mathematics**: Practical application of vectors, trigonometry, and linear algebra
- **Game Development**: Core concepts of game loops and real-time rendering
- **Performance Optimization**: Efficient algorithms for real-time graphics
- **External Libraries**: Integration with MLX42, CMake, and GLFW

---

*"This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. It will enable you to explore ray-casting and create a dynamic view inside a maze."*

For complete project details and requirements, refer to the subject file:
📄 [`en.subject.pdf`](https://github.com/Redadaghouj/42-cub3D_1337/blob/main/subject/en.subject.pdf)
