#!/bin/bash

clang++ main.cpp -o simulasi \
  -I/opt/homebrew/include \
  -L/Users/yukebrillianth/Kuliah/STRUKDAT/fp/sfml-3.0.2/lib \
  -Wl,-rpath,/Users/yukebrillianth/Kuliah/STRUKDAT/fp/sfml-3.0.2/lib \
  -lsfml-graphics -lsfml-window -lsfml-system -std=c++17

./simulasi