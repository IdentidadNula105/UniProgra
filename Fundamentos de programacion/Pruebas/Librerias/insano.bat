gcc -c insano.c -o insano.o
ar rcs libinsano.a insano.o
gcc elmain.c -L. -linsano -o elmain
elmain.exe