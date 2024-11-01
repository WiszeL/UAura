# 1. Project Setup
- Set the JetBrains Rider as default IDE of UE
- Disable Live Coding, auto Hot Reload
- Write out the Copyright Notice `Copyright, <COMPARY>, <YEAR>`
- Set `Asset Editor Open Location` to "Main Window"

# 2. Version Control
## 2.1 GIT IGNORE
A special file to prevent files/folder to be uploaded to Git. Recommended to put the Content's Asset on separated
service like Google Drive to avoid Git LFS. Blueprint SHOULD be always on version control.

Existed .gitignore:
```gitignore
# Ignore all files by default, but scan all directories.
*
!*/

# Do not ignore git files in the root of the repo.
!/.git*

# Do not ignore current project's `.uproject`.
!/*.uproject

# Do not ignore source, config and plugins dirs.
!/Source/**
!/Config/**
!/Plugins/**
!/Summary/**
!/Data/**

# Ignore everything in the Content except those
# As it gonna take the Git LFS (kinda expensive for me)
!/Content/Blueprints/**
!/Content/Inputs/**
!/Content/Data/**

# Allow any files from /RawContent dir.
# Any file in /RawContent dir will be managed by git lfs.
!/RawContent/**/*

# OS/platform generated files.

# Windows
ehthumbs.db
Thumbs.db

# Mac OS X
.DS_Store
.DS_Store?
.AppleDouble
.LSOverride
._*

# Linux
*~
.directory

# vim
[._]*.s[a-w][a-z]
[._]s[a-w][a-z]
*.un~
Session.vim
.netrwhist

# Visual Studio
.vs
.idea
```

## 2.2 GIT ATTRIBUTES
Used to mark a file as LFS. As I said before, LFS is not recommended for indie dev (or at least me)
but if we still need it, we can use .gitattributes:

```gitignore
# UE file types
*.uasset filter=lfs diff=lfs merge=lfs -text
*.umap filter=lfs diff=lfs merge=lfs -text

# Raw Content types
*.fbx filter=lfs diff=lfs merge=lfs -text
*.3ds filter=lfs diff=lfs merge=lfs -text
*.psd filter=lfs diff=lfs merge=lfs -text
*.png filter=lfs diff=lfs merge=lfs -text
*.mp3 filter=lfs diff=lfs merge=lfs -text
*.wav filter=lfs diff=lfs merge=lfs -text
*.xcf filter=lfs diff=lfs merge=lfs -text
*.jpg filter=lfs diff=lfs merge=lfs -text
```

## 2.3 INIT REPOSITORY
Make sure to create the repository first in the GitHub (or any Git service).
After we create the repository, there will be command to initialize our project to be version controlled.

Run these commands on the **ROOT** project.

```bash
git init
git add .
git commit -m "Project Initialization"
git branch -M main
git remote add origin https://github.com/<gituser>/<gitrepo>.git
git push -u origin main
```

## 2.4 COMMITING CHANGES
To commit a change, before commiting it make sure to back up the project first just in case if we're going to lose the progress.
Right after that, we can use command `git pull` to update our local project with the newer version from the online one.
Lastly we can commit normally.

```bash
# Make sure to backup the project before pull
git pull

# After that, we can commit our changes
git commit -m "Changes"
git push -u origin main
```

# 3. Setup Code
What code should be created first?

## 3.1 Character/Pawn
Pawn is a must when it comes to Unreal Engine. Of course, without it what else our game can do?

If the game gonna have humanoid-like then Character class is more suitable than regular Pawn.
Whether the game is gonna be Third Person or First Person, Character class is a must!

- Inherited Pawn: Such as Enemy and Player. Usually, player should be implemented first.
- Character Blueprint Setup: Create the Blueprint from the C++ Class.
- Animation Blueprint: Animation handler for the characters!
- Player Controller: To handle the player

## 3.2 Input
We gonna use Enhanced Input. Define the Input Action on the separated Content's folder.

It should be placed on one level with `Content/Blueprints` and `Content/Assets`

- Include the "EnhancedInput" module on the `Build.cs`
- Setup Enhanced Input mapping context onto subsystem at the PlayerController
- For setup input action, there are some consideration:
    - If its general (pause game with ESC), place at Player Controller
    - If its specified (WASD when on humanoid character), place on that specified class

Code for setup input mapping context onto subsystem at PlayerController:
![img.png](Images/00-subsystem.png)

## 3. Game Mode
After all of that, set the game mode and its properties properly.