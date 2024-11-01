# Setup Code
What code should be created first?

## 1. Character/Pawn
Pawn is a must when it comes to Unreal Engine. Of course, without it what else our game can do?

If the game gonna have humanoid-like then Character class is more suitable than regular Pawn.
Whether the game is gonna be Third Person or First Person, Character class is a must!

- Inherited Pawn: Such as Enemy and Player. Usually, player should be implemented first.
- Character Blueprint Setup: Create the Blueprint from the C++ Class.
- Animation Blueprint: Animation handler for the characters!
- Player Controller: To handle the player

## 2. Input
We gonna use Enhanced Input. Define the Input Action on the separated Content's folder.

It should be placed on one level with `Content/Blueprints` and `Content/Assets`

- Include the "EnhancedInput" module on the `Build.cs`
- Setup Enhanced Input mapping context onto subsystem at the PlayerController
- For setup input action, there are some consideration:
  - If its general (pause game with ESC), place at Player Controller
  - If its specified (WASD when on humanoid character), place on that specified class

Code for setup input mapping context onto subsystem at PlayerController:
![img.png](subsystem.png)

## 3. Game Mode
After all of that, set the game mode and its properties properly.