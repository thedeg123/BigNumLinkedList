all: additup
additup: additup.c additup.h
	gcc additup.c -o additup
clean: 
	rm additup
