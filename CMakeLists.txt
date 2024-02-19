cmake_minimum_required(VERSION 3.27)
project(Blackjack21 C)

set(CMAKE_C_STANDARD 23)

add_executable(Blackjack21 main.c
        headers/cardIneitor.h
        headers/playerIneitor.h
        headers/dealerIneitor.h)
