@echo off

set /p input=Commit name: 

git add *.cpp
git add *.h
git add *.md
git add *.vert
git add *.frag
git add LICENSE
git commit -m"%input%"
git push -u