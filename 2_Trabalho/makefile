CC_FILES=$(wildcard *.cc)

make:
	g++ -std=c++1z $(CC_FILES) -o s -g
	./s

valgrind:
	g++ -std=c++1z $(CC_FILES) -o s -v
	valgrind ./s --track-origins=yes --leak-check=full --show-leak-kinds=all

valg:
	g++ -std=c++1z $(CC_FILES) -o s
	valgrind ./s --track-origins=yes --leak-check=full --show-leak-kinds=all

clean:
	rm -f *.o s
	clear
