CC_FILES=$(wildcard *.cc)

make:
	g++ -std=c++1z $(CC_FILES) -o s -g
	./s

valgrind:
	g++ -std=c++1z $(CC_FILES) -o s -v
	valgrind ./s --track-origins=yes

valg:
	g++ -std=c++1z $(CC_FILES) -o s
	valgrind ./s --track-origins=yes

clean:
	rm -f *.o s
	clear
