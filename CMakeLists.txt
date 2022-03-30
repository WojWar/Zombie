cmake_minimum_required(VERSION 3.10)

# set the project name
project(ZombieAttack)
add_subdirectory(Atak_zombie_Wojciech_War)
# add the executable
add_executable(ZombieAttack main.cpp Parameters.cpp Globals.cpp Player.cpp Zombie.cpp Zombies.cpp Bullet.cpp)