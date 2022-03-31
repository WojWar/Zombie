cmake_minimum_required(VERSION 3.10)

project(ZombieAttack)

set(SOURCES
    main.cpp
	Parameters.cpp
	Globals.cpp
	Player.cpp
	Zombie.cpp
	Zombies.cpp
	Bullet.cpp
	Parameters.h
	Globals.h
	Player.h
	Zombie.h
	Zombies.h
	Bullet.h
)

add_executable(ZombieAttack ${SOURCES})

set(SFML_DIR SFML/lib/cmake/SFML)
find_package(SFML 2.5.1 COMPONENTS audio graphics window system REQUIRED)

target_link_libraries(ZombieAttack sfml-audio sfml-graphics sfml-window sfml-system)

