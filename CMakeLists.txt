cmake_minimum_required(VERSION 3.22)
project(proyecto)

set(CMAKE_CXX_STANDARD 23)

add_executable(proyecto main.cpp pieces/Piece.h pieces/PieceFactory.h game/Engine.cpp game/Engine.h game/Board.cpp game/Board.h)
