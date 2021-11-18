

static:
	ar rcs lib/static/libhello.a obj/helloMng.o obj/helloo.o

link: 
	gcc obj/main.o -Llib/static -lhello -o bin/statically-linked
 
all: 
	gcc -c main.c -o obj/main.o -I./inc
	gcc -c src/helloo.c -o obj/helloo.o -I./inc
	gcc -c src/helloMng.c -o obj/helloMng.o -I./inc
	
clean:
	rm -rf obj/* bin/*
