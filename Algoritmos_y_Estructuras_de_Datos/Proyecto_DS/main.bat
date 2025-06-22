gcc -c libarbolbinario/arbbin.c -o libarbolbinario/arbbin.o
ar rcs libarbolbinario/libarbbin.a libarbolbinario/arbbin.o

gcc -c libpiladinamica/piladin.c -o libpiladinamica/piladin.o
ar rcs libpiladinamica/libpiladin.a libpiladinamica/piladin.o

gcc -c libis/is.c -o libis/is.o
ar rcs libis/libis.a libis/is.o

gcc -c libcadespecial/cadesp.c -Ilibis -o libcadespecial/cadesp.o
ar rcs libcadespecial/libcadesp.a libcadespecial/cadesp.o

gcc -c libnotainfpost/notainfpost.c -Ilibcadespecial -Ilibis -Ilibpiladinamica  -o libnotainfpost/notainfpost.o
ar rcs libnotainfpost/libnotainfpost.a libnotainfpost/notainfpost.o

gcc -c libderivadorsimb/derivsimb.c -Ilibnotainfpost -Ilibcadespecial -Ilibis -Ilibarbolbinario -Ilibpiladinamica -o libderivadorsimb/derivsimb.o
ar rcs libderivadorsimb/libderivsimb.a libderivadorsimb/derivsimb.o

gcc main.c -Ilibderivadorsimb -Ilibnotainfpost -Ilibcadespecial -Ilibis -Ilibpiladinamica -Ilibarbolbinario -Llibderivadorsimb -Llibnotainfpost -Llibcadespecial -Llibis -Llibpiladinamica -Llibarbolbinario -lderivsimb -lnotainfpost -lcadesp -lis -lpiladin -larbbin -o main.exe

main.exe