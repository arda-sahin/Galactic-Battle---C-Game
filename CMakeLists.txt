cmake_minimum_required(VERSION 3.25)
project(a3)

set(CMAKE_CXX_STANDARD 17)

add_executable(a3 main.cpp Coordinate.cpp Coordinate.h BattleShip.cpp BattleShip.h StarDestroyer.cpp StarDestroyer.h MonCalamariCruiser.cpp XWingSquadron.cpp XWingSquadron.h MonCalamariCruiser.h TIEFighter.cpp TIEFighter.h Board.cpp Board.h Player.cpp Player.h Game.cpp Game.h GiftSystem.cpp GiftSystem.h)
