CFLAGS = -Wall -Wextra -std=c99

all: project 

test: test.o test_tile.o test_color.o test_rule.o file.o rule.o tile.o color.o outils.o
	gcc $(CFLAGS) -o test test.o test_tile.o test_color.o test_rule.o file.o rule.o tile.o color.o outils.o && ./test

test.o: tst/test.c tst/test_color.h tst/test_tile.h tst/test_rule.h tst/outils.h
	gcc $(CFLAGS) -c tst/test.c

test_rule.o: tst/test_rule.c src/rule.h src/file.h tst/outils.h
	gcc $(CFLAGS) -c tst/test_rule.c

test_color.o: tst/test_color.c src/color.h tst/outils.h
	gcc $(CFLAGS) -c tst/test_color.c

test_tile.o: tst/test_tile.c src/tile.h tst/outils.h
	gcc $(CFLAGS) -c tst/test_tile.c

outils.o: tst/outils.c 
	gcc $(CFLAGS) -c tst/outils.c

project: project.o color.o tile.o file.o rule.o
	gcc $(CFLAGS) -g -o project project.o color.o tile.o file.o rule.o

project.o: src/project.c src/tile.h src/file.h src/rule.h
	gcc $(CFLAGS) -c src/project.c

rule.o: src/rule.c src/rule.h src/tile.h src/file.h
	gcc $(CFLAGS) -c src/rule.c

file.o: src/file.c src/file.h src/tile.h
	gcc $(CFLAGS) -c src/file.c

tile.o: src/tile.c src/color.h
	gcc $(CFLAGS) -c src/tile.c

color.o: src/color.c
	gcc $(CFLAGS) -c src/color.c

clean:
	rm -f  *.o 
