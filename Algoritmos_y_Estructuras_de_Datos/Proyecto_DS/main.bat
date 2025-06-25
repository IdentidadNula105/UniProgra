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

gcc -c libsimparbfun/simparbfun.c -Ilibcadespecial -Ilibis  -Ilibarbolbinario  -o libsimparbfun/simparbfun.o
ar rcs libsimparbfun/libsimparbfun.a libsimparbfun/simparbfun.o

gcc -c libderivarbfun/derivarbfun.c -Ilibnotainfpost -Ilibsimparbfun -Ilibcadespecial -Ilibis -Ilibarbolbinario -Ilibpiladinamica -o libderivarbfun/derivarbfun.o
ar rcs libderivarbfun/libderivarbfun.a libderivarbfun/derivarbfun.o

gcc main.c -Ilibderivarbfun -Ilibsimparbfun -Ilibnotainfpost -Ilibcadespecial -Ilibis -Ilibpiladinamica -Ilibarbolbinario -Llibderivarbfun -Llibsimparbfun -Llibnotainfpost -Llibcadespecial -Llibis -Llibpiladinamica -Llibarbolbinario -lderivarbfun  -lsimparbfun -lnotainfpost -lcadesp -lis -lpiladin -larbbin -o main.exe

main.exe