all:
	gcc -o t1 task1.c
clean: 
	rm -rf t1 A B C D *.txt *.gz
