CC_FILES=$(wildcard *.cc)

make:
	g++ -g -Wextra -O2 -std=c++1z $(CC_FILES) -o s -g
	./s

valgrind:
	g++ -g -Wextra -O2 -std=c++1z $(CC_FILES) -o s -v
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./s

valg:
	g++ -g -Wextra -O2 -std=c++1z $(CC_FILES) -o s
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./s

clean:
	rm -f *.o s
	clear
