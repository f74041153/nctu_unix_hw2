all: sandbox.cpp sandboxso.c
	gcc -o sandbox.so -shared -fPIC sandboxso.c
	g++ -o sandbox sandbox.cpp -ldl

