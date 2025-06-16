#/bin/bash
g++ ./source/Entity.cpp source/WindowManager.cpp ./source/Block.cpp ./source/Player.cpp ./source/Projectile.cpp -c -fsanitize=address
g++ main.cpp Entity.o WindowManager.o Block.o Player.o Projectile.o -lX11 -fsanitize=address
mv *.o ./objects
