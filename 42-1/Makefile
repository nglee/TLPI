all:
	gcc -g -Wall -shared -o libfoo.so -fPIC foo.c
	gcc -g -Wall -shared -o libbar.so -I ../common -fPIC bar.c ../common/libtlpi.a -Wl,--rpath,'$$ORIGIN'
	gcc -g -Wall -o main -I../common main.c ../common/libtlpi.a -lpthread -ldl -Wl,--rpath,'$$ORIGIN'
