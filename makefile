OPTS= -g -c -Wall -Werror
all: Stat clean
Stat: STAT_DRIVER.o Stat.o
	g++ -o Stat STAT_DRIVER.o Stat.o
STAT_DRIVER.o: STAT_DRIVER.cc
	g++ $(OPTS) STAT_DRIVER.cc
Stat.o: Stat.cc Stat.h
	g++ $(OPTS) Stat.cc
clean:
	rm -f *o
	rm -f *~
