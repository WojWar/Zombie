cmake_minimum_required(VERSION 3.16)


# set the project name
project(ZombieAttack LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# add the executable
add_executable(ZombieAttack src/main.cpp src/BgWalls.cpp src/Bullet.cpp src/Bullets.cpp src/Game.cpp src/GameMap.cpp src/Globals.cpp src/Matrix2d.cpp src/Player.cpp src/Zombie.cpp src/Zombies.cpp)

target_link_libraries(ZombieAttack PRIVATE sfml-graphics)
target_compile_features(ZombieAttack PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET ZombieAttack
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<BOOL:${ARCH_64BITS}>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:ZombieAttack>
        VERBATIM)
endif()

install(TARGETS ZombieAttack)