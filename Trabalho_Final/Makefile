CC_FILES=$(wildcard *.cc)
LDLIBS =  -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lm  -lpng
ODIR=.

make:
	g++ -g -Wextra -O2 -std=c++1z $(CC_FILES) -o s -g $(LDLIBS)
	./s

valgrind:
	g++ -g -Wextra -O2 -std=c++1z $(CC_FILES) -o s -g -v $(LDLIBS)
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./s

valg:
	g++ -g -Wextra -O2 -std=c++1z $(CC_FILES) -o s -g $(LDLIBS)
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./s

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ s
	clear
