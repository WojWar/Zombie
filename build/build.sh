cd artifacts
g++ -c ../../src/*.cpp
cd ../output
g++ ../artifacts/*.o -o ZombieAttack -lsfml-graphics -lsfml-window -lsfml-system
