gcc main.c -o main.exe
gcc GeneradorDatos.c -o GeneradorDatos.exe
GeneradorDatos.exe > datos.txt
main.exe < datos.txt