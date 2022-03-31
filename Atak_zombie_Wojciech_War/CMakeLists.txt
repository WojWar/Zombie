cmake_minimum_required(VERSION 3.10)

# set the project name
project(ZombieAttack)

# Look for the SFML components we're interested in
find_package(SFML 2.4 COMPONENTS audio graphics window system REQUIRED)

# Define a list of our source files
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

# Define our target executable based on the source files above
add_executable(ZombieAttack ${SOURCES})

# Link our executable to SFML and its dependencies
target_link_libraries(ZombieAttack sfml-audio sfml-graphics sfml-window sfml-system)

# Set our source directory as the startup directory for debugging
set_target_properties(ZombieAttack PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})