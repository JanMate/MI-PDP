cmake_minimum_required(VERSION 3.13)
project(mi_pdp)

set(CMAKE_CXX_STANDARD 14)

add_executable(mi_pdp main.cpp Factory/Factory.cpp Factory/Factory.h Object/Cell.cpp Object/Cell.h HelpfulObject/Position.cpp HelpfulObject/Position.h Object/Tile.cpp Object/Tile.h HelpfulObject/Direction.cpp HelpfulObject/Direction.h Object/FirstTile.cpp Object/FirstTile.h Object/SecondTile.cpp Object/SecondTile.h Object/SimpleTile.cpp Object/SimpleTile.h Logic/CalculationCoverageAlgorithm.cpp Logic/CalculationCoverageAlgorithm.h Input/InputLoader.cpp Input/InputLoader.h Object/DisabledTile.cpp Object/DisabledTile.h Object/Table.cpp Object/Table.h HelpfulObject/ObjectType.cpp HelpfulObject/ObjectType.h)