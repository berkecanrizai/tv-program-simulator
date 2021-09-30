all: project2

project2:
	gcc project2.c -lpthread -o project2.out

clean:
	rm project2.out

