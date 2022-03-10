build:
	gcc start.c task1.c task2.c task3.c task4.c -Wall -o bmp
run:
	./bmp
clean:
	rm bmp 