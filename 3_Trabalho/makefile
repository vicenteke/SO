CC_FILES=$(wildcard *.cc)

make:
	g++ $(CC_FILES) -o s -g
	./s

valgrind:
	g++ $(CC_FILES) -o s -v
	valgrind ./s --track-origins=yes

valg:
	g++ $(CC_FILES) -o s
	valgrind ./s --track-origins=yes

clean:
	rm -f *.o s
	clear
