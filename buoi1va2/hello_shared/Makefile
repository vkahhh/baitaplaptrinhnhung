all:
	gcc -c src/main.c -o bin/main.o -I./inc
	gcc -c -fPIC src/hello.c -o bin/shared/hello.o -I./inc
	gcc -c -fPIC src/hellomng.c -o bin/shared/hellomng.o -I./inc

	gcc -shared bin/shared/hello.o bin/shared/hellomng.o -o bin/shared/libshare.so

clean:
	rm -rf hello 
