all: sandbox.cpp sandboxso.c
	gcc -o sandbox.so -shared -fPIC sandboxso.c -ldl 
	g++ -o sandbox sandbox.cpp
sample: sample.c
	gcc sample.c -o sample1
	gcc sample.c -o sample2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64

