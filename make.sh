#/bin/bash
g++ ./source/Entity.cpp source/WindowManager.cpp ./source/Block.cpp -c -fsanitize=address
g++ main.cpp Entity.o WindowManager.o Block.o -lX11 -fsanitize=address
mv *.o ./objects
