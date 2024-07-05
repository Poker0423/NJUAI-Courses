CC=gcc-10
CFLAGS=-std=gnu11 -g -O3 -pthread -Wall -Werror -pedantic
# ASAN = Address SANitizer
CFLAGS_ASAN=-std=gnu11 -g -Og -pthread -fsanitize=address -Wall -Werror -pedantic
# TSAN = Thread SANitizer
CFLAGS_TSAN=-std=gnu11 -g -Og -pthread -fsanitize=thread -fsanitize=undefined -Wall -Werror -pedantic

all: life life-asan life-tsan

%-asan.o: %.c
	$(CC) -c $(CFLAGS_ASAN) -o $@ $<

%-tsan.o: %.c
	$(CC) -c $(CFLAGS_TSAN) -o $@ $<

life.o: life.c life.h
life-asan.o: life.c life.h
life-tsan.o: life.c life.h

life-parallel.o: life-parallel.c life.h
life-parallel-asan.o: life-parallel.c life.h
life-parallel-tsan.o: life-parallel.c life.h

life-serial.o: life-parallel.c life.h
life-serial-asan.o: life-parallel.c life.h
life-serial-tsan.o: life-parallel.c life.h

main.o: main.c life.h
main-asan.o: main.c life.h
main-tsan.o: main.c life.h

life: main.o life.o life-parallel.o life-serial.o
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

life-asan: main-asan.o life-asan.o life-parallel-asan.o life-serial-asan.o
	$(CC) $(CFLAGS_ASAN) -o $@ $^ -lpthread

life-tsan: main-tsan.o life-tsan.o life-parallel-tsan.o life-serial-tsan.o
	$(CC) $(CFLAGS_TSAN) -o $@ $^ -lpthread

clean:
	rm -f *.o

SUBMIT_FILENAME=life-submission-$(shell date +%Y%m%d%H%M%S).tar.gz

archive:
	tar -zcf $(SUBMIT_FILENAME) $(wildcard *.c *.h *.txt *.md *.pdf) Makefile 
	@echo "Created $(SUBMIT_FILENAME); please upload and submit this file."

submit: archive

.PHONY: all clean archive submit