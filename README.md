# 12th-grade-project

This repo contains the source for the Game and Drawing Utility that I created as a Capstone project during the final year of my High School (12th Grade, in India). 

The game is a simple one - the bottom of the screen has the view of a city's landscape. The top portion of the screen has a space shuttle that goes from left to right, and randomly stops at a point and drops a bomb. The aim of the game is to shoot the bomb using the mouse pointer before it reaches the city at the bottom. 

The drawing utility is me trying to mimic MS Paint! This drawing utility is a very very basic version of MS Paint, that lets you draw on screen, paint circles/rectangles, etc and choose one of 16 colors. 

## Contents
The "TurboCPP-with-game-and-drawing-utility-exe" directory contains the Turbo C++ executable, along with C++ library modules (IOSTREAM.H, CONIO.H, etc.). It contains a directory named "work/", which contains the compiled version of the "game and drawing utility" that I developed. Run the GAME.exe file under work/ to play the game and/or use the drawing utility. 

## Prerequisites
1. Download and install [DOSBox](https://www.dosbox.com/download.php?main=1)
1. Clone this repository, and mount the "TurboCPP-with-game-and-drawing-utility-exe" as C:\

## How to run the game/drawing utility
1. Open DOSBox
1. cd work
1. GAME.exe

## How to edit and compile using Turbo C++
1. Open DOSBox
1. TC.EXE (this opens the TurboC++ IDE)
1. Open WORK/GAME.CPP to edit it in the IDE
1. Under Options/Directories, set "Include Directories" and "Library Directories" to C:\. Set "Output Directories" and "Source Directories" to C:\WORK
1. Use Menu options to compile/build/run
1. Make sure the path for the graphics library in the initgraph() function points to C:\ (without which, the graphics may not work and you may get a blank, black screen when the game is run)
