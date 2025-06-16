#/bin/bash
g++ ./source/Entity.cpp source/WindowManager.cpp ./source/Block.cpp ./source/Player.cpp ./source/Projectile.cpp ./source/Alien.cpp ./source/GameManager.cpp -c -fsanitize=address
g++ main.cpp Entity.o WindowManager.o Block.o Player.o Projectile.o Alien.o GameManager.o -lX11 -fsanitize=address
mv *.o ./objects
