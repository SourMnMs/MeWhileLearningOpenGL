## What is this? ##

Uhhh there isn't much to say about this project right now.  
I'm making it for [Hack Club](https://hackclub.com/)'s Campfire Flagship event.

I'm working on it in an effort to better understand the nitty-gritty of graphical design (using OpenGL in C++).  
The end goal is to have a working program that can calculate the area of any given polygon using triangulation. It will have an interface for adding points and way to change the dimensions of the cartesian coordinate system.

## Be advised, **this currently only runs on Ubuntu**.

To compile it, you need:
 - libglfw3-dev - ```sudo apt-get install libglfw3-dev```
 - apple bottom jeans
 - boots with the fur (sold separately)
 - a will to live
 - to send me a box full of chicken noodle soup (the canned stuff is fine)

I'm no expert on Linux or compiling, but I compiled it using CMake with Ninja (for those wondering, this project was made in CLion). I don't know if compilers other than Ninja work or not.

## Checklist (mostly for myself):

- [x] Make it through [LearnOpenGL.com](http://LearnOpenGL.com)’s “Getting Started” tutorials
  - [x] Read through some of the other tutorials on there as well (not all of them because I’m making a 2D project)
- [ ] Make it easier to render shapes  
  - [x] Make generic shape class (and subclasses)
    - [x] Regular polygon of n sides
    - [ ] Triangle  
    - [ ] Rectangle  
  - [x] Make a handler to operate on all of its given shapes
    - [x] Buffer shapes
    - [x] Render shapes
    - [ ] Input buffer
- [ ] Make executable for other platforms
  - [ ] Windows
  - [ ] Fedora
  - [ ] Arch
- [ ] More stuff to come  
- [ ] Area Calculator
