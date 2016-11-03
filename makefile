compile: dirInfo.o
	gcc -o dirInfo.out dirInfo.o

stat.o: dirInfo.c
	gcc -c dirInfo.c

run: dirInfo.out
	./dirInfo.out

clean:
	rm *.out
	rm *.o
