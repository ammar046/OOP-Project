# OOP-Project

## Overview

`OOP-Project` is a C++ 2D platformer inspired by Sonic the Hedgehog. The project is built using SFML and demonstrates object-oriented design patterns such as inheritance, polymorphism, and the factory pattern.

Players can choose from multiple characters, collect rings and power-ups, fight enemies, and progress through scrollable levels including a boss fight.

## Key Features

- 4 playable levels with side-scrolling camera movement
- Playable characters: Sonic, Knuckles, and Tails
- Character switching in-game using `Z`
- Collectibles: rings, extra lives, and special boosts
- Multiple enemy types: CrabMeat, BeeBot, BatBrain, MotoBug, and EggStinger boss
- In-game HUD with health, ring count, and timer
- Main menu with `Continue`, `Play Game`, `Settings`, `Leader Board`, and `Level Select`
- Settings menu supports toggling music and sound effects plus adjusting volume
- Dynamic level creation using grid-based maps and a factory-based level builder

## Gameplay Controls

- `Left Arrow` - move selected character left
- `Right Arrow` - move selected character right
- `Space` - jump
- `Z` - switch active character during play
- `Escape` - back out of menus or return to main menu during gameplay
- `Up Arrow` / `Down Arrow` - navigate menu items
- `Left Arrow` / `Right Arrow` - adjust volume in settings
- `Enter` - select menu option

## Architecture

This project is organized with a strong focus on OOP principles:

- `Game.h` / `Source.cpp` - main game loop, event processing, state management
- `Menu.h` - menu rendering, input handling, settings, and level selection
- `Levels.h` / `LevelFactory.h` - level creation, object spawning, camera scrolling, and collision handling
- `PlayableCharacters.h`, `Sonic.h`, `Knuckles.h`, `Tails.h` - playable character classes with shared behavior and individual animations
- `Characters.h` - base character interface
- `Enemyfactory.h`, `Enemies.h`, plus enemy headers - enemy creation and polymorphic behavior
- `CollectibleFactory.h`, `Collectibles.h`, `Ring.h`, `ExtraLife.h`, `SpecialBoost.h` - collectible item creation and display
- `Physics.h`, `Collision.h` - physics calculations, gravity, jump handling, and collision responses

## Project Structure

- `OOP Project/` - source code and Visual Studio project files
- `OOP Project/Data/` - audio and sprite assets used by the game
- `OOP Project/fonts/` - font asset(s)
- `OOP Project/Sprites/` - background and menu graphics

## Dependencies

- SFML 2.x (`sfml-graphics`, `sfml-window`, `sfml-audio`, `sfml-system`)
- C++17 compatible compiler
- Visual Studio is recommended because the project contains a `.vcxproj` file

## Build & Run

### Windows / Visual Studio

1. Open `OOP Project/OOP Project.vcxproj` in Visual Studio.
2. Configure the SFML include and library paths in project settings if needed.
3. Build the solution.
4. Run the generated executable from the `Debug` or `Release` output folder.

### Alternative Build (Manual)

If you want to build manually, ensure SFML is installed and available. A typical command might look like:

```bash
g++ -std=c++17 "OOP Project/Source.cpp" -I"/path/to/SFML/include" -L"/path/to/SFML/lib" \
  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o "OOPProject"
```

> Note: The project was created as a Visual Studio solution, so manual builds may require additional source files and linker options.

## Notes

- The `Continue` menu entry resumes a previously started game only when the player is still alive.
- The `Level Select` menu allows starting directly from any unlocked level.
- The boss fight is implemented in the final stage and uses the `EggStinger` enemy.

## Contribution

If you want to extend this game, good next steps include:

- Adding a proper level editor or loading levels from external files
- Implementing save/load progress
- Adding controller support
- Improving enemy AI and player animations
- Refactoring input handling for cleaner separation of concerns
