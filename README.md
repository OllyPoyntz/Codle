# Codle
Simple Wordle clone written in C++ for a school project.

## Introduction
This project was assigned to me as a project in Computer Science, completed over a two-week holiday period. Whilst it was intended to be completed in Python, I decided to challenge myself by writing it entirely in C++. Note that I was forbidden from including any programming constructs more complicated than lists or string methods, preventing me from using OOP.

## Gameplay
The gameplay is exactly what you would expect. You have six attempts to guess a randomly selected five-letter word, and you should enter your guesses directly into your terminal. The official list of Wordle puzzles and valid words is used, minus profanity, etc.

Feedback is output in the form of letters:
- An `O` means a letter is correct and in the correct position.
- A `~` means a letter is correct but in the wrong position.
- An `X` means a letter is not present in the word or already marked as in the correct position.

On POSIX systems (e.g Linux, MacOS, Open/FreeBSD, Cygwin), ANSI terminal colour codes are used to simulate the colours of the original Wordle.

## Compilation
On POSIX systems, a [makefile](/makefile) is provided - use the command `make codle` to compile the executable using `g++`. 

For Windows, cross compilation with `make codle.exe` is recommended to build a Windows Portable Executable on a POSIX system using MinGW, but if you only have access to MSVC, use the command below from a developer console while in the project directory.
```
cl.exe codle.cpp /std:c++11 /EHsc /O2
```

## License
The word lists in [wordlists](/wordlists) are taken from [two](https://gist.github.com/dracos/dd0668f281e685bad51479e5acaadb93) [separate](https://gist.github.com/cfreshman/a03ef2cba789d8cf00c08f767e0fad7b) GitHub repositories, and slightly modified to remove any profanity or other unwanted words.

The C++ code itself is under the [permissive MIT license](/LICENSE).
