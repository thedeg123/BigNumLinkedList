all: additup
additup: additup.c additup.h
	gccx additup.c -o additup
clean: 
	rm additup
