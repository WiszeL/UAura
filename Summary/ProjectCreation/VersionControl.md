# GIT IGNORE
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

# Ignore everything in the Content except Blueprint
# As it gonna take the Git LFS (kinda expensive for me)
!/Content/Blueprints/**

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

# GIT ATTRIBUTES
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

# INIT REPOSITORY
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

# COMMITING CHANGES
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